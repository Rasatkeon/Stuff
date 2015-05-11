// Copyright 2015 Tim Catler
#ifndef SEARCH_CPP
#define SEARCH_CPP

#include "./search.hpp"

template <typename T>
unsigned Compare(const T &left, const T &right) {
    if (left == right)
        return 100;
    else
        return 0;
}

unsigned Compare(const BusTour &left, const BusTour &right) {
    unsigned result = 0;
    if (left.Destination == right.Destination) result += 50;
    if (left.Type == right.Type) result += 25;
    if (left.Free > 0 || right.Free > 0) result += 25;
    return result;
}

#endif  // SEARCH_CPP
