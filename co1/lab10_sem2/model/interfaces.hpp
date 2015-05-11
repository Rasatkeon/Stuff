// Copyright 2015 Tim Catler
#ifndef INTERFACES_H
#define INTERFACES_H

#include <string>

using string = std::string;

class IFile {
 public:
    virtual void Write(const string &path) = 0;
    virtual void Read(const string &path) = 0;
};

#endif  // INTERFACES_H
