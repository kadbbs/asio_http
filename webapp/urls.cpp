//
// Created by bbs on 24-7-12.
//

#include "urls.h"
#include "views.h"
using request=http::server::request;


//std::map<std::string, std::function<void()>> url_map = {
//        {"/main.cpp", test_fun},
//};

std::map<std::string, std::function<std::string (request&)>> urlpatterns = {
        {"/main.cpp", render},
        {"/upload", savefile},
};
