#include <vector>
#include <string>
#include <iostream>
#include <sstream>

std::vector<std::string> split(const std::string& str, char delimiter);
std::vector<std::string> split2(const std::string& str, const std::string& delimiter);
bool startswith(const std::string& str, const std::string& prefix);
bool startswith(const std::string& str, char prefix);