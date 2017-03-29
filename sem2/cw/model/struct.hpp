// Copyright 2015 Tim Catler
#ifndef STRUCT_H
#define STRUCT_H

#include <string>
#include <iostream>

#include "./utils/utils.hpp"

using string = std::string;

struct BusTour {
    string Destination;
    string Type;
    unsigned Free;

    BusTour() {
        Destination = "";
        Type = "";
        Free = 0;
    }

    static BusTour parse(string input) {
        auto buff = split(input, '|');
        if (buff.size() > 3) return BusTour();
        if (!isNumber(buff[2].data())) return BusTour();

        BusTour result;
        result.Destination = buff[0];
        result.Type = buff[1];
        result.Free = atoi(buff[2].data());
        return result;
    }

    static void print(const BusTour &tour) {
        std::cout << "Destination is " << tour.Destination << std::endl;
        std::cout << "Bus type is " << tour.Type << std::endl;
        std::cout << "Number of tickets to purchase: " << tour.Free
                  << std::endl;
    }
};

std::ostream& operator<<(std::ostream &os, BusTour &tour);

#endif  // STRUCT_H
