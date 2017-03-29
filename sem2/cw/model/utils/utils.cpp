// Copyright 2014 Tim Catler
#ifndef UTILS_CPP
#define UTILS_CPP

#include <vector>
#include <string>

#include "./utils.hpp"

std::vector<std::string> split(std::string input, char divider) {
    std::vector<std::string> output;
    output.push_back("");
    for (unsigned i = 0,
                  j = 0; i < input.size(); i++) {
        if (input[i] == divider) {
            output.push_back("");
            j++;
        } else {
            output[j] += input[i];
        }
    }
    return output;
}

bool isNumber(std::string input) {
    std::string numbers = "0123456789";
    for (unsigned i = 0; i < input.size(); ++i) {
        if (numbers.find(input[i]) == std::string::npos) return false;
    }
    return true;
}

#endif  // UTILS_CPP
