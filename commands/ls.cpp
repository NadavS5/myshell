#include "ls.h"

int ls(std::vector<std::string> params) {
    DIR* d;
    struct dirent *dir;

    std::vector<std::string> options;
    std::vector<std::string> dirs;

    for(int i =0; i < params.size(); i++) {
        auto p = params.at(i);
        
        if(startswith(p, '-')) {
           options.push_back(params.at(i));
        }
        else {
            if (!isAllWhitespace(params.at(i))) dirs.push_back(params.at(i));
        }
    }

    if (dirs.size() == 0) {
        dirs.push_back(".");
    }

    for (auto dirname : dirs) {
        std::cout <<"listing: "<< dirname << std::endl;
        d = opendir(dirname.c_str());
        if (d) {
            while ((dir = readdir(d)) != NULL) {
                std::cout << dir->d_name << std::endl;
            }
            closedir(d);
        }
    }
    
    return 0;;
}
