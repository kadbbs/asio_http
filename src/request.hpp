//
// request.hpp
// ~~~~~~~~~~~
//
// Copyright (c) 2003-2021 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include "header.hpp"

namespace http {
    namespace server {

/// A request received from a client.
        struct request
        {
//            request();
            std::string method;
            std::string uri;
            int http_version_major;
            int http_version_minor;
            std::vector<header> headers;
            std::unordered_map<std::string,std::string> map_headers;
            std::string body;
            int content_length;
            std::string boundary;
            std::string content;
            std::vector<header> body_headers;
            std::vector<std::string> body_vhs;
            std::string body_hstr;


            std::string get_boundary() ;
            std::string extract_content();
            void vtomap();


        };



    } // namespace server
} // namespace http

#endif // HTTP_REQUEST_HPP