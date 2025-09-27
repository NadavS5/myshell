#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include "commands/cd.h"
#include "commands/pwd.h"
#include "commands/ls.h"
#include "commands/read.h"
#include "utils/StringUtils.h"
#include <errno.h>
#include <cstring>
#include <fcntl.h>
#include <sys/wait.h>
#include <algorithm> // Required for std::find

std::vector<std::string> commands;
char current_dir[1024];
void handle_input(std::string);

int main() {

	commands.push_back("pwd");
	commands.push_back("cd");
	commands.push_back("ls");
	commands.push_back("read");

	
	while (!std::cin.eof()){
		getcwd(current_dir, sizeof(current_dir));
		std::cout<< current_dir << " & ";
		std::string input;
		std::getline(std::cin, input);

		handle_input(input);
	}
}
void execute_command(std::string input) {
	ltrim(input);
	std::vector<std::string> params = split(input, ' ');
	std::cout << "executing2 " << input << std::endl;

	if (auto it_found = std::find(commands.begin(), commands.end(), params.at(0)); it_found != commands.end()) { 
		if(input.find(' ') != std::string::npos) {
			
			params.erase(params.begin());
		}
		

		std::string::size_type position = input.rfind("cd", 0);
		if(position != std::string::npos) {
			std::string dest = input.substr(position + 3);

			if(cd(params) == -1) {
				fprintf(stderr,"chdir failed: %s\n", strerror(errno));
			}
		}
		
		position = input.rfind("pwd", 0);
		if(position != std::string::npos) {
			if(pwd() == -1) {
				fprintf(stderr,"pwd failed: %s\n", strerror(errno));
			}
		}

		position = input.rfind("ls", 0);
		if(position != std::string::npos) {
			if(ls(params) == -1) {
				fprintf(stderr,"ls failed: %s\n", strerror(errno));
			}
		}
		position = input.rfind("read", 0);
		if(position != std::string::npos) {
			if(read_cmd(params) == -1) {
				fprintf(stderr,"read failed: %s\n", strerror(errno));
			}
		}
	}		
	else {
		std::cout << "system used" << std::endl;
		system(input.c_str());
	}
}

void handle_input(std::string input) {
	input += " ";
	auto parts = split(input, '|' );

	if(auto delim = input.find("|"); delim != std::string::npos) {
		std::cout << "pipe used" << std::endl;
		
		
		int fd[2];
		if (pipe(fd) == -1) {
			perror("pipe failed");
        	exit(1);
		}
		
		pid_t pid1 = fork();
		//Child 1 execute:
		if(pid1 == 0) {
			std::string cmd = input.substr(0,delim);
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			
			handle_input(cmd);
			exit(0);
		}
		pid_t pid2 = fork();
		if(pid2 == 0) {
			std::string cmd = input.substr(delim + 1);

			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			handle_input(cmd);
			exit(0);
		}
		
		close(fd[1]);
		close(fd[0]);

		waitpid(pid1, NULL, 0);
    	waitpid(pid2, NULL, 0);
			
		
	}

	else if(input.find(">>") != std::string::npos) {
		std::cout << "redirect used" << std::endl;
		auto delim = std::string(">>");
		auto parts = split2(input, delim);
		if (parts.size() > 2) {
			std::cerr << "redirect can be used once!" << std::endl;
			std::cout << parts.size() << std::endl;
		}
		int fd = open(parts.at(1).c_str(), O_WRONLY | O_CREAT | O_APPEND , 0644);
		
		int saved_stdout = dup(STDOUT_FILENO);
		dup2(fd, STDOUT_FILENO);
		
		execute_command(parts.at(0));
		close(fd);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
		
	}

	else if(input.find(">") != std::string::npos) {
		std::cout << "redirect append used" << std::endl;
		auto parts = split(input, '>' );
		if (parts.size() > 2) {
			std::cerr << "redirect can be used once!" << std::endl;\
			std::cout << parts.size() << std::endl;
		}

		int fd = open(parts.at(1).c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);

		int saved_stdout = dup(STDOUT_FILENO);
		dup2(fd, STDOUT_FILENO);
		
		execute_command(parts.at(0));
		close(fd);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	
		
	else {
		execute_command(input);
	}
	
	
}
