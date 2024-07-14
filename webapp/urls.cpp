//
// Created by bbs on 24-7-12.
//

#include "urls.h"
#include "views.h"
#include "../h_context.h"
using request=http::server::request;
using h_context=http::server::h_context;


//std::map<std::string, std::function<void()>> url_map = {
//        {"/main.cpp", test_fun},
//};

//std::map<std::string, std::function<std::string (request&)>> urlpatterns = {
//        {"/main.cpp", render},
//        {"/upload", savefile},
//};


std::map<std::string, std::function<void (h_context &)>> urlpatterns={
        {"/main.cpp", render},
        {"/upload", savefile},
};
