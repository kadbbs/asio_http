#ifndef ASIO_HTTP_URLS_H
#define ASIO_HTTP_URLS_H

#include <vector>
#include <string>
#include <map>
#include <functional>
#include "views.h"
#include "../request.hpp"
#include "../h_context.h"
using request=http::server::request;
using h_context=http::server::h_context;


// 外部声明全局变量
//        extern std::map<std::string, std::function<void()>> url_map;
//        extern std::map<std::string, std::function<std::string (request &)>> urlpatterns;
        extern std::map<std::string, std::function<std::string (h_context &)>> urlpatterns;

#endif // ASIO_HTTP_URLS_H
