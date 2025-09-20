#include "ls.h"

int ls(std::vector<std::string> params) {
    DIR* d;
    struct dirent *dir;
    if (params.size()>0) {
        d = opendir(params.at(0).c_str());
    }


    return 0;;
}
