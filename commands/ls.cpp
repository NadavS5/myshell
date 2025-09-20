#include "ls.h"

int ls(std::vector<std::string> params) {
    DIR* d;
    struct dirent *dir;


    std::string dir_name = ".";
    

    for(auto p : params) {
        if(startswith(p, '-')) {
            std::cout << "option " << p << std::endl;
        } else {
            dir_name = p;
        }
    }

    
    d = opendir(dir_name.c_str());
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            std::cout << ("%s\n", dir->d_name) << std::endl;
        }
        closedir(d);
    }
    

    
    return 0;;
}
