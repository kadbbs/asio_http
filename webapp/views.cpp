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

using namespace boost::json;

namespace net = boost::asio;
namespace json = boost::json;
using tcp = boost::asio::ip::tcp;
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

void print_req(request& req){
    std::cout << "render is run "<< std::endl;

    std::cout<<"req method is " << req.method<<"\n";
    std::cout<<"req uri is " << req.uri<<"\n";

    std::cout<<"req http_version_major is " << req.http_version_major<<"\n";

    std::cout<<"req http_version_minor is " << req.http_version_minor<<"\n";


    for (auto iter = req.headers.begin(); iter != req.headers.end(); iter++) {
        std::cout <<"header.name : "<< (*iter).name;
        std::cout <<"---->header.value : "<<(*iter).value << std::endl;

    }
    std::cout<<"req body boundary is " << req.boundary<<"\n";
    std::cout<<"req header str is "<< req.body_hstr<<"\n";


}

std::string  render(request& req) {

    print_req(req);
    json::object response_json;
    response_json["message"] = "Hello, world!";

    response_json["status"] = "success";
    response_json["mes"]={response_json["message"],response_json["status"]};

    std::string json_str = json::serialize(response_json);


    return json_str;

}

std::string savefile(request &req) {

    print_req(req);



//    if(req.headers[5].value.find("multipart/form-data")){
//        bfenge=req.headers[5].value.substr(sizeof("multipart/form-data; boundary="));
//    }
//    std::vector<string> vStr;
//    boost::split(vStr, content, boost::is_any_of(bfenge), boost::token_compress_on);
//
//    for(auto it=vStr[1].begin();it!=vStr[1].end();it++){
//
//    }
//    std::cout<<"req formdata : \n " <<"\n";
//
//    for(int i=0;i<1000;i++){
//            std::cout<<vStr[1][i];
//    }


//    std::regex pattern(R"(.*(%PDF.*)----.*)");
//    std::smatch match;
//
//    if (std::regex_search(content, match, pattern)) {
//        if (match.size() > 1) {
//            std::string result = match[1].str();
//            std::cout << "Extracted string: "  << std::endl;
//            std::cout << "result string size : " << result.size() << std::endl;
//
//            save_file(result, "./uploaded_file.pdf");
//
//        } else {
//            std::cout << "No match found." << std::endl;
//        }
//    } else {
//        std::cout << "No match found." << std::endl;
//    }




    std::string filetype;
    for (const auto &h: req.body_headers) {
        if (h.name == "Content-Type") {
            filetype = h.value;


        }
    }

        save_file(req.content, "./uploaded_file." + filetype);


        json::object response_json;
        response_json["filesave"] = "Ture";


        std::string json_str = json::serialize(response_json);


        return json_str;

}

//void test_fun() {
//    static int i = 0;
//    std::cout << "testPath is run count : " << i++ << std::endl;
//}
