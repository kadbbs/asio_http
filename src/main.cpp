//
// main.cpp
// ~~~~~~~~
//
// Copyright (c) 2003-2021 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "server.hpp"
//#include <boost/version.hpp>

int main(int argc, char* argv[])
{

    std::cout << "Boost version: "
              << BOOST_VERSION / 100000 << "."   // Major version
              << BOOST_VERSION / 100 % 1000 << "." // Minor version
              << BOOST_VERSION % 100 << std::endl; // Patch level
    std::cout << "Boost library version: " << BOOST_LIB_VERSION << std::endl;
    try
    {
        // Check command line arguments.
        if (argc != 4)
        {
            std::cerr << "Usage: http_server <address> <port> <doc_root>\n";
            std::cerr << "  For IPv4, try:\n";
            std::cerr << "    receiver 0.0.0.0 80 .\n";
            std::cerr << "  For IPv6, try:\n";
            std::cerr << "    receiver 0::0 80 .\n";
            return 1;
        }

        // Initialise the server.
        http::server::server s(argv[1], argv[2], argv[3]);

        // Run the server until stopped.
        s.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "exception: " << e.what() << "\n";
    }

    return 0;
}
