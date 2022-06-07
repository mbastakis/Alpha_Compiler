#ifndef HELPER_HPP
#define HELPER_HPP

#include <string>
#include <cmath>
#include <algorithm>
#include <iostream>

void red() {
    std::cout << "\033[0;31m";
}

void yellowc() {
    std::cout << "\033[33m";
}

void reset() {
    std::cout << "\033[01;37m";
}

std::string loadBinaryString(FILE* file) {
    std::string buffer{};
    unsigned int i = 0;

    char c;
    do {
        fread(&c, sizeof(char), 1, file);
        buffer.append(&c);
    } while (c != '\0');

    return buffer;
}

std::string modify_number(double number) {
    if (floor(number) == ceil(number))
        return std::to_string((int)number);
    else return std::to_string(number);
}

std::string remove_extra_zero(std::string number) {
    if (number.find(".") == std::string::npos)
        return number;
    reverse(number.begin(), number.end());
    int i;
    for (i = 0; i < number.size(); i++) {
        if (number[i] != '0') break;
    }
    number = number.substr(i, number.size());
    reverse(number.begin(), number.end());
    return number;
}

#endif