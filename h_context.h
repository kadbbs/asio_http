//
// Created by bbs on 24-7-15.
//

#ifndef ASIO_HTTP_H_CONTEXT_H
#define ASIO_HTTP_H_CONTEXT_H

#include "request.hpp"
#include "reply.hpp"
namespace http {
    namespace server {
        struct h_context {

            h_context(request request,reply reply);


            request request_;
            reply reply_;

        };
    }}

#endif //ASIO_HTTP_H_CONTEXT_H
