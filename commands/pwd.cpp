#include "pwd.h"
#include <cstdlib>

int pwd() {
    char* cwd = get_current_dir_name();
	std::cout<< cwd << std::endl;
	delete cwd;
	return 0;
}
