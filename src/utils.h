//
// Created by bbs on 24-7-15.
//

#ifndef ASIO_HTTP_UTILS_H
#define ASIO_HTTP_UTILS_H

#include <string>
#include <vector>
#include "../webapp/urls.h"

class utils {
public:
    static std::vector<std::string> split(const std::string& str, const std::vector<std::string>& delimiters);
    static void print_req(request& req);



};


#endif //ASIO_HTTP_UTILS_H
