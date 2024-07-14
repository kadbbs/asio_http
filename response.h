//
// Created by bbs on 24-7-13.
//

#ifndef ASIO_HTTP_RESPONSE_H
#define ASIO_HTTP_RESPONSE_H

#include <boost/json.hpp>
class response {

    std::string josn(const std::string path);
    std::string josn(    boost::json::object response_json);
    std::string text(const std::string path);
    std::string html(const std::string path);
    std::string xml(const std::string path);
    std::string file(const std::string path);
    void redirect(const std::string url);

};

//JsonResponse()


#endif //ASIO_HTTP_RESPONSE_H
