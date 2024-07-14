#ifndef ASIO_HTTP_VIEWS_H
#define ASIO_HTTP_VIEWS_H

#include <iostream>
#include <vector>
#include <string>
#include <boost/asio.hpp>
#include "../request.hpp"
#include "../connection.hpp"
using request=http::server::request;

// 函数声明
std::string render(request &req);

std::string savefile(request &req);



#endif // ASIO_HTTP_VIEWS_H
