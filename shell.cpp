#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include "commands/cd.h"
#include "commands/pwd.h"
#include "commands/ls.h"

#include <errno.h>
#include <cstring>
std::vector<std::string> commands;
char current_dir[1024];
void handle_input(std::string);
int main() {

	commands.push_back("pwd");
	commands.push_back("cd");
	commands.push_back("ls");

	//std::cin >> input;
	while (!std::cin.eof()){
		getcwd(current_dir, sizeof(current_dir));
		std::cout<< current_dir << " & ";
		std::string input;
		std::getline(std::cin, input);

		handle_input(input);
	}
}

void handle_input(std::string input) {

	if(input.find("|") != std::string::npos) {
		std::cout << "pipe used" << std::endl;
	}
	std::vector<std::string> params;
	std::string::size_type position = input.rfind("cd ");
	if(position != std::string::npos) {

    	std::string dest = input.substr(position + 3);

    	params.emplace_back(input.substr(position + 3));
    	if(cd(params) == -1) {
            fprintf(stderr,"chdir failed: %s\n", strerror(errno));
        }
	}
	position = input.rfind("pwd");
	if(position != std::string::npos) {
    	if(pwd() == -1) {
            fprintf(stderr,"pwd failed: %s\n", strerror(errno));
        }
	}
	position = input.rfind("ls");
	if(position != std::string::npos) {
		params.emplace_back(input.substr(position + 3));
    	if(ls(params) == -1) {
            fprintf(stderr,"ls failed: %s\n", strerror(errno));
        }
	}

}
