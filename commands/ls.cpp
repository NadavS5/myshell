#include "ls.h"

int ls(std::vector<std::string> params) {
    DIR* d;
    struct dirent *dir;
    if (params.size()>0) {
        d = opendir(params.at(0).c_str());
        if (d) {
            while ((dir = readdir(d)) != NULL) {
                std::cout << ("%s\n", dir->d_name) << std::endl;
            }
            closedir(d);
        }
    }

    
    return 0;;
}
