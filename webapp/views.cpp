//
// Created by bbs on 24-7-12.
//
#include "views.h"
#include <iostream>
#include <regex>
#include <string>
#include <boost/json.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "../utils.h"

using namespace boost::json;

namespace net = boost::asio;
namespace json = boost::json;
using tcp = boost::asio::ip::tcp;

std::string extract_filename(const std::string& str) {
    std::string::size_type start = str.find('"');
    std::string::size_type end = str.find('"', start + 1);

    if (start != std::string::npos && end != std::string::npos) {
        return str.substr(start + 1, end - start - 1);
    }
    return ""; // 返回空字符串表示未找到
}

//std::string get_boundary(const http::server::request& req) {
//    for (const auto& h : req.headers) {
//        if (h.name == "Content-Type") {
//            std::string::size_type pos = h.value.find("boundary=");
//            if (pos != std::string::npos) {
//                return h.value.substr(pos + 9);
//            }
//        }
//    }
//    return "";
//}
//
//std::string extract_content(const http::server::request& req, const std::string& boundary) {
//    std::string::size_type pos = req.body.find("--" + boundary);
//    pos = req.body.find("\r\n\r\n", pos) + 4;
//    std::string::size_type end = req.body.find("--" + boundary, pos);
//    return req.body.substr(pos, end - pos - 2);
//}

//void save_file(const std::string& content, const std::string& filename) {
//    std::ofstream ofs(filename, std::ios::binary);
//    ofs.write(content.c_str(), content.size());
//    ofs.close();
//}

void save_file(const std::string& content, const std::string& filename)
{
    std::ofstream ofs(filename, std::ios::binary);
    if (ofs)
    {
        ofs.write(content.c_str(), content.size());
        ofs.close();
        std::cout << "File saved successfully: " << filename << std::endl;
    }
    else
    {
        std::cerr << "Error saving file: " << filename << std::endl;
    }
}



//std::string  render(request& req) {
//
//    print_req(req);
//    json::object response_json;
//    response_json["message"] = "Hello, world!";
//
//    response_json["status"] = "success";
//    response_json["mes"]={response_json["message"],response_json["status"]};
//
//    std::string json_str = json::serialize(response_json);
//
//
//    return json_str;
//
//}
//
//std::string savefile(request &req) {
//
//    print_req(req);
//    std::string filetype;
//
//
//        save_file(req.content, "./uploaded_file." + filetype);
//
//        json::object response_json;
//        response_json["filesave"] = "Ture";
//        std::string json_str = json::serialize(response_json);
//
//        return json_str;
//}



void remaincpp(h_context &c){
    utils::print_req(c.request_);
//    json::object response_json;
//    response_json["main.cpp"] = "Ture";
//    std::string json_str = json::serialize(response_json);
//
//
//    c.reply_.josnstr(json_str);

    c.reply_.file("/home/bbs/code/cpp/asio_http/webapp/views.cpp");


}

void savefile(h_context &c) {
        utils::print_req(c.request_);
        std::string filename;



        for(auto it:c.request_.body_vhs){
            if(std::string::npos!=it.find("filename=")){
                filename = extract_filename(it);
            }
        }

        save_file(c.request_.content, filename);

        json::object response_json;
        response_json["h"] = "Ture";
        std::string json_str = json::serialize(response_json);


        c.reply_.josnstr(json_str);


}

