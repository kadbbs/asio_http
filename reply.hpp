//
// reply.hpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2021 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_REPLY_HPP
#define HTTP_REPLY_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <iostream>
#include <boost/json/object.hpp>
#include "header.hpp"

namespace http {
    namespace server {



/// A reply to be sent to a client.
        struct reply
        {
            /// The status of the reply.
            enum status_type
            {
                ok = 200,
                created = 201,
                accepted = 202,
                no_content = 204,
                multiple_choices = 300,
                moved_permanently = 301,
                moved_temporarily = 302,
                not_modified = 304,
                bad_request = 400,
                unauthorized = 401,
                forbidden = 403,
                not_found = 404,
                internal_server_error = 500,
                not_implemented = 501,
                bad_gateway = 502,
                service_unavailable = 503
            } status;

            /// The headers to be included in the reply.
            std::vector<header> headers;

            /// The content to be sent in the reply.
            std::string content;
            static const std::string beian;

            static const std::string pre;
            static const std::string bak;

            /// Convert the reply into a vector of buffers. The buffers do not own the
            /// underlying memory blocks, therefore the reply object must remain valid and
            /// not be changed until the write operation has completed.
            std::vector<boost::asio::const_buffer> to_buffers();


            /// 根据用户的输入修改响应
            std::string josnfile(const std::string path);
            std::string josnobj(boost::json::object response_json);
            void josnstr(const std::string data);

            std::string text(const std::string path);
            std::string html(const std::string path);
            std::string xml(const std::string path);
            std::string file(const std::string path);
            void redirect(const std::string url);

            /// Get a stock reply.
            static reply stock_reply(status_type status);
            static void insert_string_at_reverse_position(std::string& original, const std::string& to_insert, size_t reverse_position) {
                if (reverse_position <= original.size()) {
                    size_t position = original.size() - reverse_position;
                    original.insert(position, to_insert);
                } else {
                    std::cerr << "Reverse position is out of bounds." << std::endl;
                }
            }
        };


    } // namespace server
} // namespace http

#endif // HTTP_REPLY_HPP