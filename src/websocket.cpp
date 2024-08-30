//
// Created by bbs on 24-7-9.
//
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <functional>
#include <openssl/sha.h>
#include <boost/beast/core/detail/base64.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <functional>
#include <openssl/sha.h>
#include <boost/beast/core/detail/base64.hpp>

namespace asio = boost::asio;
using asio::ip::tcp;

std::string base64_encode(const std::string& input) {
    return boost::beast::detail::base64_encode(input);
}

std::string sha1_hash(const std::string& input) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);
    return std::string(reinterpret_cast<char*>(hash), SHA_DIGEST_LENGTH);
}

std::string create_websocket_accept(const std::string& key) {
    const std::string GUID = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    return base64_encode(sha1_hash(key + GUID));
}

void do_session(tcp::socket socket) {
    try {
        asio::streambuf buffer;
        asio::read_until(socket, buffer, "\r\n\r\n");

        std::istream request_stream(&buffer);
        std::string request_line;
        std::getline(request_stream, request_line);
        std::string header;
        std::string websocket_key;

        while (std::getline(request_stream, header) && header != "\r") {
            if (header.substr(0, 19) == "Sec-WebSocket-Key: ") {
                websocket_key = header.substr(19);
                websocket_key.pop_back(); // Remove trailing \r
            }
        }

        if (websocket_key.empty()) {
            std::cerr << "WebSocket key not found" << std::endl;
            return;
        }

        std::string websocket_accept = create_websocket_accept(websocket_key);

        std::ostringstream response;
        response << "HTTP/1.1 101 Switching Protocols\r\n";
        response << "Upgrade: websocket\r\n";
        response << "Connection: Upgrade\r\n";
        response << "Sec-WebSocket-Accept: " << websocket_accept << "\r\n";
        response << "\r\n";

        asio::write(socket, asio::buffer(response.str()));

        for (;;) {
            asio::streambuf message;
            asio::read(socket, message, asio::transfer_at_least(2));

            std::istream message_stream(&message);
            uint8_t first_byte;
            uint8_t second_byte;
            message_stream.read(reinterpret_cast<char*>(&first_byte), 1);
            message_stream.read(reinterpret_cast<char*>(&second_byte), 1);

            bool fin = first_byte & 0x80;
            uint8_t opcode = first_byte & 0x0F;
            bool mask = second_byte & 0x80;
            uint64_t payload_length = second_byte & 0x7F;

            if (payload_length == 126) {
                uint16_t extended_payload_length;
                message_stream.read(reinterpret_cast<char*>(&extended_payload_length), 2);
                payload_length = ntohs(extended_payload_length);
            } else if (payload_length == 127) {
                uint64_t extended_payload_length;
                message_stream.read(reinterpret_cast<char*>(&extended_payload_length), 8);
                payload_length = ntohll(extended_payload_length);
            }

            std::vector<uint8_t> masking_key(4);
            if (mask) {
                message_stream.read(reinterpret_cast<char*>(masking_key.data()), 4);
            }

            std::vector<uint8_t> payload(payload_length);
            message_stream.read(reinterpret_cast<char*>(payload.data()), payload_length);

            if (mask) {
                for (size_t i = 0; i < payload_length; ++i) {
                    payload[i] ^= masking_key[i % 4];
                }
            }

            if (opcode == 0x8) { // Close frame
                break;
            } else if (opcode == 0x1) { // Text frame
                std::string message(payload.begin(), payload.end());
                std::cout << "Received: " << message << std::endl;

                std::vector<uint8_t> response_frame;
                response_frame.push_back(0x81); // FIN + Text frame
                if (payload_length <= 125) {
                    response_frame.push_back(static_cast<uint8_t>(payload_length));
                } else if (payload_length <= 65535) {
                    response_frame.push_back(126);
                    uint16_t len = htons(static_cast<uint16_t>(payload_length));
                    response_frame.insert(response_frame.end(), reinterpret_cast<uint8_t*>(&len), reinterpret_cast<uint8_t*>(&len) + 2);
                } else {
                    response_frame.push_back(127);
                    uint64_t len = htobe64(payload_length);
                    response_frame.insert(response_frame.end(), reinterpret_cast<uint8_t*>(&len), reinterpret_cast<uint8_t*>(&len) + 8);
                }
                response_frame.insert(response_frame.end(), payload.begin(), payload.end());

                asio::write(socket, asio::buffer(response_frame));
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    try {
        asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));

        for (;;) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            std::thread(&do_session, std::move(socket)).detach();
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
