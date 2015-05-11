// Copyright 2015 Tim Catler
#include "./struct.hpp"

std::ostream& operator<<(std::ostream &os, BusTour &tour) {
    os << tour.Destination << '|' << tour.Type << '|' << tour.Free << std::endl;
    return os;
}
