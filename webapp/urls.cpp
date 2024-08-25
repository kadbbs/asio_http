//
// Created by bbs on 24-7-12.
//

#include "urls.h"
#include "views.h"
#include "../src/h_context.h"
std::map<std::string, std::function<void (h_context &)>> urlpatterns={
        {"/main.cpp", remaincpp},
        {"/upload", savefile},
        {"/",indexpage},
};
