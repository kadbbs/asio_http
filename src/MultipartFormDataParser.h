//
// Created by bbs on 24-7-13.
//

#ifndef ASIO_HTTP_MULTIPARTFORMDATAPARSER_H
#define ASIO_HTTP_MULTIPARTFORMDATAPARSER_H


#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>

class MultipartFormDataParser {
public:
    MultipartFormDataParser(const std::string& boundary)
            : boundary(boundary), state(State::START) {}

    void feed(const std::string& data) {
        buffer += data;
        parse();
    }

private:
    enum class State {
        START,
        HEADERS,
        BODY,
        END
    };

    std::string boundary;
    std::string buffer;
    State state;
    std::map<std::string, std::string> headers;
    std::string part_data;

    void parse() {
        size_t pos = 0;
        while (state != State::END) {
            switch (state) {
                case State::START:
                    pos = buffer.find("--" + boundary);
                    if (pos != std::string::npos) {
                        buffer.erase(0, pos + boundary.size() + 2);
                        state = State::HEADERS;
                    }
                    break;
                case State::HEADERS:
                    pos = buffer.find("\r\n\r\n");
                    if (pos != std::string::npos) {
                        parse_headers(buffer.substr(0, pos));
                        buffer.erase(0, pos + 4);
                        state = State::BODY;
                    }
                    break;
                case State::BODY:
                    pos = buffer.find("--" + boundary);
                    if (pos != std::string::npos) {
                        part_data = buffer.substr(0, pos - 2);
                        buffer.erase(0, pos + boundary.size() + 2);
                        process_part();
                        state = State::HEADERS;
                    } else {
                        state = State::END;
                    }
                    break;
                case State::END:
                    break;
            }
        }
    }

    void parse_headers(const std::string& data) {
        std::istringstream stream(data);
        std::string line;
        headers.clear();
        while (std::getline(stream, line)) {
            if (line.back() == '\r') {
                line.pop_back();
            }
            size_t pos = line.find(": ");
            if (pos != std::string::npos) {
                headers[line.substr(0, pos)] = line.substr(pos + 2);
            }
        }
    }

    void process_part() {
        auto it = headers.find("Content-Disposition");
        if (it != headers.end()) {
            std::string disposition = it->second;
            if (disposition.find("filename=") != std::string::npos) {
                std::string filename = disposition.substr(disposition.find("filename=") + 10);
                filename.pop_back(); // Remove the trailing quotation mark
                save_file(filename, part_data);
            }
        }
    }

    void save_file(const std::string& filename, const std::string& data) {
        std::ofstream file(filename, std::ios::binary);
        if (file.is_open()) {
            file.write(data.c_str(), data.size());
            file.close();
            std::cout << "Saved file: " << filename << std::endl;
        } else {
            std::cerr << "Failed to save file: " << filename << std::endl;
        }
    }
};



#endif //ASIO_HTTP_MULTIPARTFORMDATAPARSER_H
