//
// Created by bbs on 24-7-15.
//

#include "utils.h"

std::vector<std::string> utils::split(const std::string &str, const std::vector<std::string> &delimiters) {
    std::vector<std::string> tokens;
    std::string::size_type start = 0;
    auto find_next_delim = [&str, &delimiters](std::string::size_type start) {
        std::string::size_type min_pos = std::string::npos;
        std::string::size_type pos;
        for (const auto& delim : delimiters) {
            pos = str.find(delim, start);
            if (pos != std::string::npos && (min_pos == std::string::npos || pos < min_pos)) {
                min_pos = pos;
            }
        }
        return min_pos;
    };

    while (start < str.length()) {
        std::string::size_type end = find_next_delim(start);
        if (end != std::string::npos) {
            if (end != start) { // avoid empty token
                tokens.push_back(str.substr(start, end - start));
            }
            start = end + 1;
        } else {
            tokens.push_back(str.substr(start));
            break;
        }
    }

    return tokens;
}

void utils::print_req(request &req) {
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
