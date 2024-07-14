cmake_minimum_required(VERSION 3.24)
project(asio_http)

set(CMAKE_CXX_STANDARD 17)
set(LIB avformat avcodec avutil swresample m rt pthread z boost_system Boost::json)

find_package(Boost REQUIRED COMPONENTS system json)

add_executable(asio_http main.cpp connection.cpp connection.hpp
        connection_manager.cpp server.cpp request_parser.cpp request_handler.cpp
        reply.cpp mime_types.cpp webapp/urls.h webapp/views.h webapp/views.cpp
        webapp/urls.cpp  MultipartFormDataParser.cpp MultipartFormDataParser.h
        request.cpp h_context.cpp h_context.h)

add_executable(websocket websocket.cpp)
target_link_libraries(asio_http PUBLIC ${LIB})
target_link_libraries(websocket PUBLIC ${LIB})

#set(CMAKE_EXE_LINKER_FLAGS "-static")
