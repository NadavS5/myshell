#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <stdio.h>

std::vector<std::string> commands;
char current_dir[1024];
void handle_input(std::string);
int main() {

	
	commands.push_back("pwd");
	commands.push_back("cd");
	
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

	std::string::size_type position = input.rfind("cd "); 
	if(position != std::string::npos) {
		
	std::string dest = input.substr(position + 3);

		std::cout << position << " params: " << input.substr(position + 3) << std::endl; 
		//std::cout << "cd used" << std::endl;
		if(chdir(dest.c_str()) != 0 ){
			std::cout << "cd error occured!" << std::endl;
		}

	}
}
