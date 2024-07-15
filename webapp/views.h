#ifndef ASIO_HTTP_VIEWS_H
#define ASIO_HTTP_VIEWS_H

#include <iostream>
#include <vector>
#include <string>
#include <boost/asio.hpp>
#include "../request.hpp"
#include "../connection.hpp"
#include "../h_context.h"
using request=http::server::request;

using h_context=http::server::h_context;

// 函数声明

void render(h_context &c);

void savefile(h_context &c);

//std::string render(request &req);
//
//std::string savefile(request &req);



#endif // ASIO_HTTP_VIEWS_H
