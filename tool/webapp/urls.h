#ifndef ASIO_HTTP_URLS_H
#define ASIO_HTTP_URLS_H

#include <vector>
#include <string>
#include <map>
#include <functional>
#include "views.h"
#include "../src/request.hpp"
#include "../src/h_context.h"
using request=http::server::request;
using h_context=http::server::h_context;

extern std::map<std::string, std::function<void (h_context &)>> urlpatterns;

#endif // ASIO_HTTP_URLS_H
