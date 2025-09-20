#include "cd.h"

int cd(std::vector<std::string> params) {

    if (params.size() == 0) {
        std::cout << "usage: cd <dir>" << std::endl;
        return 0;
    }
    std::cout << "changind dir to: " + params.at(0) << std::endl;

    if(chdir(params.at(0).c_str()) != 0 ){
		std::cerr << "cd error occured!" << std::endl;
		return -1;
	}

    return 0;
}
