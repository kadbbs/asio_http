//
// reply.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2021 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "reply.hpp"
#include <string>
#include <boost/json/serialize.hpp>
#include <fstream>


namespace http {
    namespace server {

        const std::string reply::beian="<p style=\"background:none;height: 5%;position: fixed;bottom: 0px;width: 100%;text-align: center;\n"
                                       "\"><a class=\"banquan\" style=\"color:#000;\"\n"
                                       "href=\"http://www.beian.gov.cn/portal/registerSystemInfo?recordcode=备案编号\"\n"
                                       "target=\"_blank\">陕ICP备2023005402号-1</a></p>";


        const std::string reply::pre="<!DOCTYPE html>\n"
                                     "<html lang=\"en\">\n"
                                     "<head>\n"
                                     "    <meta charset=\"UTF-8\">\n"
                                     "    <title>Title</title>\n"
                                     "</head>\n"
                                     "<body><pre>";

        const std::string reply::bak="</pre></body>\n"
                                     "\n"
                                     "\n"
                                     "<p style=\"background:none;height: 5%;position: fixed;bottom: 0px;width: 100%;text-align: center;\n"
                                     "\"><a class=\"banquan\" style=\"color:#000;\"\n"
                                     "                                                                                        href=\"http://www.beian.gov.cn/portal/registerSystemInfo?recordcode=备案编号\"\n"
                                     "                                                                                        target=\"_blank\">陕ICP备2023005402号-1</a></p>\n"
                                     "</html>";

        namespace status_strings {

            const std::string ok =
                    "HTTP/1.0 200 OK\r\n";
            const std::string created =
                    "HTTP/1.0 201 Created\r\n";
            const std::string accepted =
                    "HTTP/1.0 202 Accepted\r\n";
            const std::string no_content =
                    "HTTP/1.0 204 No Content\r\n";
            const std::string multiple_choices =
                    "HTTP/1.0 300 Multiple Choices\r\n";
            const std::string moved_permanently =
                    "HTTP/1.0 301 Moved Permanently\r\n";
            const std::string moved_temporarily =
                    "HTTP/1.0 302 Moved Temporarily\r\n";
            const std::string not_modified =
                    "HTTP/1.0 304 Not Modified\r\n";
            const std::string bad_request =
                    "HTTP/1.0 400 Bad Request\r\n";
            const std::string unauthorized =
                    "HTTP/1.0 401 Unauthorized\r\n";
            const std::string forbidden =
                    "HTTP/1.0 403 Forbidden\r\n";
            const std::string not_found =
                    "HTTP/1.0 404 Not Found\r\n";
            const std::string internal_server_error =
                    "HTTP/1.0 500 Internal Server Error\r\n";
            const std::string not_implemented =
                    "HTTP/1.0 501 Not Implemented\r\n";
            const std::string bad_gateway =
                    "HTTP/1.0 502 Bad Gateway\r\n";
            const std::string service_unavailable =
                    "HTTP/1.0 503 Service Unavailable\r\n";

            boost::asio::const_buffer to_buffer(reply::status_type status)
            {
                switch (status)
                {
                    case reply::ok:
                        return boost::asio::buffer(ok);
                    case reply::created:
                        return boost::asio::buffer(created);
                    case reply::accepted:
                        return boost::asio::buffer(accepted);
                    case reply::no_content:
                        return boost::asio::buffer(no_content);
                    case reply::multiple_choices:
                        return boost::asio::buffer(multiple_choices);
                    case reply::moved_permanently:
                        return boost::asio::buffer(moved_permanently);
                    case reply::moved_temporarily:
                        return boost::asio::buffer(moved_temporarily);
                    case reply::not_modified:
                        return boost::asio::buffer(not_modified);
                    case reply::bad_request:
                        return boost::asio::buffer(bad_request);
                    case reply::unauthorized:
                        return boost::asio::buffer(unauthorized);
                    case reply::forbidden:
                        return boost::asio::buffer(forbidden);
                    case reply::not_found:
                        return boost::asio::buffer(not_found);
                    case reply::internal_server_error:
                        return boost::asio::buffer(internal_server_error);
                    case reply::not_implemented:
                        return boost::asio::buffer(not_implemented);
                    case reply::bad_gateway:
                        return boost::asio::buffer(bad_gateway);
                    case reply::service_unavailable:
                        return boost::asio::buffer(service_unavailable);
                    default:
                        return boost::asio::buffer(internal_server_error);
                }
            }

        } // namespace status_strings

        namespace misc_strings {

            const char name_value_separator[] = { ':', ' ' };
            const char crlf[] = { '\r', '\n' };

        } // namespace misc_strings

        std::vector<boost::asio::const_buffer> reply::to_buffers()
        {
            std::vector<boost::asio::const_buffer> buffers;
            buffers.push_back(status_strings::to_buffer(status));
            for (std::size_t i = 0; i < headers.size(); ++i)
            {
                header& h = headers[i];
                buffers.push_back(boost::asio::buffer(h.name));
                buffers.push_back(boost::asio::buffer(misc_strings::name_value_separator));
                buffers.push_back(boost::asio::buffer(h.value));
                buffers.push_back(boost::asio::buffer(misc_strings::crlf));
            }
            buffers.push_back(boost::asio::buffer(misc_strings::crlf));
            buffers.push_back(boost::asio::buffer(content));
            return buffers;
        }

        namespace stock_replies {

            const char ok[] = "";
            const char created[] =
                    "<html>"
                    "<head><title>Created</title></head>"
                    "<body><h1>201 Created</h1></body>"
                    "</html>";
            const char accepted[] =
                    "<html>"
                    "<head><title>Accepted</title></head>"
                    "<body><h1>202 Accepted</h1></body>"
                    "</html>";
            const char no_content[] =
                    "<html>"
                    "<head><title>No Content</title></head>"
                    "<body><h1>204 Content</h1></body>"
                    "</html>";
            const char multiple_choices[] =
                    "<html>"
                    "<head><title>Multiple Choices</title></head>"
                    "<body><h1>300 Multiple Choices</h1></body>"
                    "</html>";
            const char moved_permanently[] =
                    "<html>"
                    "<head><title>Moved Permanently</title></head>"
                    "<body><h1>301 Moved Permanently</h1></body>"
                    "</html>";
            const char moved_temporarily[] =
                    "<html>"
                    "<head><title>Moved Temporarily</title></head>"
                    "<body><h1>302 Moved Temporarily</h1></body>"
                    "</html>";
            const char not_modified[] =
                    "<html>"
                    "<head><title>Not Modified</title></head>"
                    "<body><h1>304 Not Modified</h1></body>"
                    "</html>";
            const char bad_request[] =
                    "<html>"
                    "<head><title>Bad Request</title></head>"
                    "<body><h1>400 Bad Request</h1></body>"
                    "</html>";
            const char unauthorized[] =
                    "<html>"
                    "<head><title>Unauthorized</title></head>"
                    "<body><h1>401 Unauthorized</h1></body>"
                    "</html>";
            const char forbidden[] =
                    "<html>"
                    "<head><title>Forbidden</title></head>"
                    "<body><h1>403 Forbidden</h1></body>"
                    "</html>";
            const char not_found[] =
                    "<html>"
                    "<head>"
                    "    <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />"
                    "<title>Not Found</title></head>"
                    "<body><h1>404 Not Found</h1></body>"
                    "<p style=\"background:none;height: 5%;position: fixed;bottom: 0px;width: 100%;text-align: center;\n"
                    "\"><a class=\"banquan\" style=\"color:#000;\"\n"
                    "        href=\"http://www.beian.gov.cn/portal/registerSystemInfo?recordcode=备案编号\"\n"
                    "        target=\"_blank\">陕ICP备2023005402号-1</a></p>"
                    "</html>";
            const char internal_server_error[] =
                    "<html>"
                    "<head><title>Internal Server Error</title></head>"
                    "<body><h1>500 Internal Server Error</h1></body>"
                    "</html>";
            const char not_implemented[] =
                    "<html>"
                    "<head><title>Not Implemented</title></head>"
                    "<body><h1>501 Not Implemented</h1></body>"
                    "</html>";
            const char bad_gateway[] =
                    "<html>"
                    "<head><title>Bad Gateway</title></head>"
                    "<body><h1>502 Bad Gateway</h1></body>"
                    "</html>";
            const char service_unavailable[] =
                    "<html>"
                    "<head><title>Service Unavailable</title></head>"
                    "<body><h1>503 Service Unavailable</h1></body>"
                    "</html>";

            std::string to_string(reply::status_type status)
            {
                switch (status)
                {
                    case reply::ok:
                        return ok;
                    case reply::created:
                        return created;
                    case reply::accepted:
                        return accepted;
                    case reply::no_content:
                        return no_content;
                    case reply::multiple_choices:
                        return multiple_choices;
                    case reply::moved_permanently:
                        return moved_permanently;
                    case reply::moved_temporarily:
                        return moved_temporarily;
                    case reply::not_modified:
                        return not_modified;
                    case reply::bad_request:
                        return bad_request;
                    case reply::unauthorized:
                        return unauthorized;
                    case reply::forbidden:
                        return forbidden;
                    case reply::not_found:
                        return not_found;
                    case reply::internal_server_error:
                        return internal_server_error;
                    case reply::not_implemented:
                        return not_implemented;
                    case reply::bad_gateway:
                        return bad_gateway;
                    case reply::service_unavailable:
                        return service_unavailable;
                    default:
                        return internal_server_error;
                }
            }

        } // namespace stock_replies

        reply reply::stock_reply(reply::status_type status)
        {
            reply rep;
            rep.status = status;
            rep.content = stock_replies::to_string(status);
            rep.headers.resize(2);
            rep.headers[0].name = "Content-Length";
            rep.headers[0].value = std::to_string(rep.content.size());
            rep.headers[1].name = "Content-Type";
            rep.headers[1].value = "text/html;charset=UTF-8\\r\\n";
            return rep;
        }

        void reply::rep(reply &rep) {


        }



        void reply::josnfile(const std::string path) {

        }

        void reply::josnobj(boost::json::object response_json) {
            status=ok;
            content=boost::json::serialize(response_json);
            headers[0].name = "Content-Length";
            headers[0].value = std::to_string(content.size());

            headers[1].name = "Content-Type";
            headers[1].value="application/json";

        }

        void reply::josnstr(const std::string data) {

            status=ok;
            content=data;
            headers[0].name = "Content-Length";
            headers[0].value = std::to_string(content.size());

            headers[1].name = "Content-Type";
            headers[1].value="application/json";


        }

        std::string reply::textfile(const std::string path) {
            std::ifstream inputfile(path, std::ios::binary | std::ios::ate);
            if (!inputfile) {
                // 如果文件打开失败，抛出一个运行时错误
                throw std::runtime_error("Failed to open file");
            }
            contentlength = inputfile.tellg();
            // 将文件读指针移动到文件的开头
            inputfile.seekg(0, std::ios::beg);
            content.resize(contentlength);
            // 读取文件内容到缓冲区
            if (!inputfile.read(&content[0], contentlength)) {
                // 如果读取失败，抛出一个运行时错误
                throw std::runtime_error("Failed to read file");
            }

            // 查找最后一个斜杠的位置
            size_t pos = path.find_last_of('/');

            // 提取斜杠后的部分
            std::string file_name;
            if (pos != std::string::npos) {
                file_name = path.substr(pos + 1);
            } else {
                file_name = path; // 如果没有斜杠，整个字符串就是文件名
            }
            const std::string htmlfrontstr=R"(<!DOCTYPE html>
                                            <html lang="en">
                                            <head>
                                            <meta charset="UTF-8">
                                            <title>Title</title>
                                            </head>
                                            <body><pre>)";
            const std::string htmlendstr="</pre></body> </html>";
            content=htmlfrontstr+content+htmlendstr;

            headers[0].name = "Content-Length";
            headers[0].value = std::to_string(content.size());
            headers[1].name = "Content-Type";
            headers[1].value = "text/html;charset=UTF-8\\r\\n";

            return "";
        }

        std::string reply::textstr(const std::string data) {
            content=data;
            const std::string htmlfrontstr=R"(<!DOCTYPE html>
                                            <html lang="en">
                                            <head>
                                            <meta charset="UTF-8">
                                            <title>Title</title>
                                            </head>
                                            <body><pre>)";
            const std::string htmlendstr="</pre></body> </html>";
            content=htmlfrontstr+content+htmlendstr;

            headers[0].name = "Content-Length";
            headers[0].value = std::to_string(content.size());
            headers[1].name = "Content-Type";
            headers[1].value = "text/html;charset=UTF-8\\r\\n";

            return "";
        }

        std::string reply::htmlfile(const std::string path) {
            std::ifstream inputfile(path, std::ios::binary | std::ios::ate);
            if (!inputfile) {
                // 如果文件打开失败，抛出一个运行时错误
                throw std::runtime_error("Failed to open file");
            }
            contentlength = inputfile.tellg();
            // 将文件读指针移动到文件的开头
            inputfile.seekg(0, std::ios::beg);
            content.resize(contentlength);
            // 读取文件内容到缓冲区
            if (!inputfile.read(&content[0], contentlength)) {
                // 如果读取失败，抛出一个运行时错误
                throw std::runtime_error("Failed to read file");
            }

            headers[0].name = "Content-Length";
            headers[0].value = std::to_string(content.size());

            // headers[1].name = "Content-Type";
            // headers[1].value="application/json";
            headers[1].name = "Content-Type";
            headers[1].value = "text/html;charset=UTF-8\\r\\n";
            return "";
        }


        std::string reply::htmlstr(const std::string data) {
            content=data;
            headers[0].name = "Content-Length";
            headers[0].value = std::to_string(content.size());

            // headers[1].name = "Content-Type";
            // headers[1].value="application/json";
            headers[1].name = "Content-Type";
            headers[1].value = "text/html;charset=UTF-8\\r\\n";
            return "";
        }

        std::string reply::xmlfile(const std::string path) {
            return std::string();
        }

        std::string reply::xmlstr(const std::string data) {
            content=data;
            headers[0].name = "Content-Length";
            headers[0].value = std::to_string(content.size());

            // headers[1].name = "Content-Type";
            // headers[1].value="application/json";
            headers[1].name = "Content-Type";
            headers[1].value = "text/html;charset=UTF-8\\r\\n";
            return "";
        }

        std::string reply::file(const std::string path) {

            std::ifstream inputfile(path, std::ios::binary | std::ios::ate);
            if (!inputfile) {
                // 如果文件打开失败，抛出一个运行时错误
                throw std::runtime_error("Failed to open file");
            }
            contentlength = inputfile.tellg();
            // 将文件读指针移动到文件的开头
            inputfile.seekg(0, std::ios::beg);
            content.resize(contentlength);
            // 读取文件内容到缓冲区
            if (!inputfile.read(&content[0], contentlength)) {
                // 如果读取失败，抛出一个运行时错误
                throw std::runtime_error("Failed to read file");
            }

            // 查找最后一个斜杠的位置
            size_t pos = path.find_last_of('/');

            // 提取斜杠后的部分
            std::string file_name;
            if (pos != std::string::npos) {
                file_name = path.substr(pos + 1);
            } else {
                file_name = path; // 如果没有斜杠，整个字符串就是文件名
            }

            status=ok;
            headers[0].name = "Content-Length";
            headers[0].value = std::to_string(contentlength);

            headers[1].name = "Content-Type";
            headers[1].value="application/octet-stream";

            header tmp;
            tmp.name="Content-Disposition";
            tmp.value="attachmentattachment; filename=\""+file_name+"\"";
            headers.push_back(tmp);


            return "";
        }

        void reply::redirect(const std::string url) {

        }

        void reply::josnfile(const std::string path, std::vector<header> headers, reply::status_type status) {

        }

        void reply::josnobj(boost::json::object response_json, std::vector<header> headers, reply::status_type status) {

        }

        void reply::josnstr(const std::string data, std::vector<header> headers, reply::status_type status) {

        }

        std::string reply::textfile(const std::string path, std::vector<header> headers, reply::status_type status) {
            return std::string();
        }

        std::string reply::textstr(const std::string data, std::vector<header> headers, reply::status_type status) {
            return std::string();
        }

        std::string reply::htmlfile(const std::string path, std::vector<header> headers, reply::status_type status) {
            return std::string();
        }

        std::string reply::htmlstr(const std::string data, std::vector<header> headers, reply::status_type status) {
            return std::string();
        }

        std::string reply::xmlfile(const std::string path, std::vector<header> headers, reply::status_type status) {
            return std::string();
        }

        std::string reply::xmlstr(const std::string path, std::vector<header> headers, reply::status_type status) {
            return std::string();
        }


    } // namespace server
} // namespace http