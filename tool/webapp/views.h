#ifndef ASIO_HTTP_VIEWS_H
#define ASIO_HTTP_VIEWS_H

#include <iostream>
#include <vector>
#include <string>
#include <boost/asio.hpp>
#include "../src/request.hpp"
#include "../src/connection.hpp"
#include "../src/h_context.h"
using request=http::server::request;
using h_context=http::server::h_context;

// 函数声明
void example(h_context &c);





#endif // ASIO_HTTP_VIEWS_H
