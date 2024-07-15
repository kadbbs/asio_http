//
// Created by bbs on 24-7-14.
//


#include <iostream>
#include "request.hpp"
#include "utils.h"
//http::server::request::request():method(nullptr),uri(nullptr),http_version_major(-1),http_version_minor(-1),body(nullptr),boundary(nullptr),content(nullptr) {
//
//
//}


std::string http::server::request::get_boundary() {
    for (const auto& h : headers) {
        if (h.name == "Content-Type") {
            std::string::size_type pos = h.value.find("boundary=");
            if (pos != std::string::npos) {
                return boundary=h.value.substr(pos + 9);
            }
        }else if(h.name=="Content-Length"){
            content_length=std::atoi(h.value.c_str());
        }
    }
    return "";
}

#if 0
std::string http::server::request::extract_content() {
    std::string::size_type pos = body.find("--" + boundary);
    pos = body.find("\r\n\r\n", pos) + 4;
    std::string::size_type end = body.find("--" + boundary, pos);
    return content=body.substr(pos, end - pos - 2);
}
#endif


std::string http::server::request::extract_content() {
    std::string::size_type pos = body.find("--" + boundary);
    if (pos == std::string::npos) {
        std::cerr << "Error: Boundary start not found" << std::endl;
        return "";
    }

    pos = body.find("\r\n", pos) + 2; // Skip the boundary line
    std::string::size_type headers_end = body.find("\r\n\r\n", pos);
    if (headers_end == std::string::npos) {
        std::cerr << "Error: Headers not properly terminated" << std::endl;
        return "";
    }
    body_hstr=body.substr(pos, headers_end - pos);

    std::vector<std::string> delimiters = {";", "\r\n"};



    body_vhs=utils::split(body_hstr,delimiters);

    std::string headers = body_hstr;
    pos = headers_end + 4; // Skip the headers and the terminating \r\n\r\n

    // Parse headers
    std::string::size_type disposition_pos = headers.find("Content-Disposition:");
    if (disposition_pos != std::string::npos) {
        std::string::size_type disposition_end = headers.find("\r\n", disposition_pos);
        header h;
        h.name="Content-Disposition";
        h.value =headers.substr(disposition_pos + 20, disposition_end - disposition_pos - 20);
        body_headers.push_back(h);

        //        content_disposition = headers.substr(disposition_pos + 20, disposition_end - disposition_pos - 20);
    }

//    std::string::size_type filename=headers.find()

    std::string::size_type type_pos = headers.find("Content-Type:");
    if (type_pos != std::string::npos) {

        std::string::size_type type_end = headers.find("\r\n", type_pos);

        header h;
        h.name="Content-Type:";
        h.value =headers.substr(type_pos + 13, type_end - type_pos - 13);
        body_headers.push_back(h);
//        content_type = headers.substr(type_pos + 13, type_end - type_pos - 13);
    }

    std::string::size_type end = body.find("--" + boundary, pos);
    if (end == std::string::npos) {
        std::cerr << "Error: Boundary end not found" << std::endl;
        return "";
    }

    return content = body.substr(pos, end - pos - 2); // -2 to remove the trailing \r\n
}
