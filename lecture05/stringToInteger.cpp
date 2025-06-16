//
// Created by BenHao on 2025/6/16.
//

#include <iostream>
#include <string>
#include <sstream>

int stringToInteger(const std::string& str) {
    std::istringstream iss(str);
    int value;
    iss >> value;

    if (iss.fail() || !iss.eof()) {
        throw std::runtime_error("Invalid input: unable to convert string to integer.");
    }
    return value;
}

int main() {
    std::string input;
    std::cout << "Enter a string to convert to an integer: ";
    std::getline(std::cin, input);

    int result = stringToInteger(input);
    std::cout << "The integer value is: " << result << std::endl;
    std::cout << "Half of the integer value is: " << result / 2 << std::endl;
    return 0;
}
