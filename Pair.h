#pragma once

#include <string>

using std::string;

template<typename T, typename U>
struct Pair {
private:
    string key;
    int value;
public:
    Pair(string key, int value) {
        this->key = key;
        this->value = value;
    }
};

