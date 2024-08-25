cmake_minimum_required(VERSION 3.16)
project(asio_http)

set(CMAKE_CXX_STANDARD 17)
set(LIB avformat avcodec avutil swresample m rt pthread z boost_system Boost::json)

find_package(Boost REQUIRED COMPONENTS system json)

add_executable(asio_http src/main.cpp src/connection.cpp src/connection.hpp
        src/connection_manager.cpp src/server.cpp src/request_parser.cpp src/request_handler.cpp
        src/reply.cpp src/mime_types.cpp webapp/urls.h webapp/views.h webapp/views.cpp
        webapp/urls.cpp src/MultipartFormDataParser.cpp src/MultipartFormDataParser.h
        src/request.cpp src/h_context.cpp src/h_context.h src/utils.cpp src/utils.h)

add_executable(websocket src/websocket.cpp)
target_link_libraries(asio_http PUBLIC ${LIB})
target_link_libraries(websocket PUBLIC ${LIB})

#set(CMAKE_EXE_LINKER_FLAGS "-static")
