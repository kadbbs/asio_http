#ifndef ASIO_HTTP_URLS_H
#define ASIO_HTTP_URLS_H

#include <vector>
#include <string>
#include <map>
#include <functional>
#include "views.h"
#include "../request.hpp"
using request=http::server::request;


// 外部声明全局变量
//        extern std::map<std::string, std::function<void()>> url_map;
        extern std::map<std::string, std::function<std::string (request &)>> urlpatterns;

#endif // ASIO_HTTP_URLS_H
