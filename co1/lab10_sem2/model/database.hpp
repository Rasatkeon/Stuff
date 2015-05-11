// Copyright 2015 Tim Catler
#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <fstream>

#include "./classes.hpp"
#include "./struct.hpp"
#include "./interfaces.hpp"
#include "./utils/search.hpp"

class Database : public IFile, public List<BusTour> {
 public:
    void Write(const std::string &path) {
        std::fstream baseFile(path, std::fstream::trunc | std::fstream::out);
        auto curr = Begin();

        while (curr != nullptr) {
            baseFile << curr->Data();
            curr = curr->Next();
        }

        baseFile.close();
    }

    void Read(const std::string &path) {
        std::fstream baseFile(path, std::fstream::in);
        std::string buff;

        while (baseFile.good()) {
            getline(baseFile, buff);
            Append(BusTour::parse(buff));
        }
        baseFile.close();
    }

    List<BusTour>* Search(BusTour query) {
        List<BusTour>* result = new List<BusTour>();
        auto curr = Begin();

        while (curr != nullptr) {
            if (Compare(curr->Data(), query) >= 50)
                result->Append(curr->Data());
            curr = curr->Next();
        }
        return result;
    }

    void Initialize(const std::string &path) {
        this->path = path;
        Read(this->path);
    }

    Database() : List() {}

 private:
    std::string path;
};

#endif  // DATABASE_H
