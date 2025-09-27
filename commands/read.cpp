#include "read.h"

int read_cmd(std::vector<std::string> params) {

    for (std::string line; std::getline(std::cin, line);) {
        std::cout << line << std::endl;
    }
    
    return 0;
}
