#pragma once

#include <string>
#include <list>
#include <utility>
#include <exception>

#include "HashmapInterface.h"
#include "Pair.h"

using namespace std;
using Bucket = list<pair<string, int>>;

class Hashmap : public HashmapInterface {
private:
    int capacity;
    int _size;
    Bucket * pairs;

    int _hash(const string &key) const {
        unsigned char *ptr = (unsigned char *) &key;
        int sum = 0;
        for (int i = 0; i < sizeof(key); i++) {
            sum += ptr[i];
        }
        return sum;
    }

    void _insert(std::string key, int value) {
        int hashcode = _hash(key);
        int position = hashcode % capacity;
        auto &slot = pairs[position];
        slot.push_back(pair<string, int>(key, value));
    }

    void _grow() {
        int newCapacity = capacity * GROW_FACTOR;
        Bucket * newPairs = new Bucket[newCapacity];
        for (int i = 0; i < capacity; i++) {
            auto &slot = pairs[i];
            for (auto &pair : slot) {
                int hashcode = _hash(pair.first);
                int position = hashcode % newCapacity;
                auto &newSlot = newPairs[position];
                newSlot.push_back(pair);
            }
        }
        delete[] pairs;
        pairs = newPairs;
        capacity = newCapacity;
    }

    bool _contains(const std::string &key) const {
        if (get(key) == -1) {
            return false;
        }
        return true;
    }

    int _get(const std::string &key) const {
        int hashcode = _hash(key);
        int position = hashcode % capacity;
        auto &slot = pairs[position];
        for (auto &pair : slot) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        return -1;
    }

    bool _remove(const std::string &key) {
        int hashcode = _hash(key);
        int position = hashcode % capacity;
        auto &slot = pairs[position];
        for (auto &pair : slot) {
            if (pair.first == key) {
                pair.first = "";
                pair.second = 0;
                return true;
            }
        }
        return false;
    }

public:
    Hashmap() {
        capacity = INITIAL_BUCKETS;
        _size = 0;
        pairs = new Bucket[capacity];
    }

    ~Hashmap() override {
        clear();
    }

    int hash(const string &key) const {
        return _hash(key);
    }

    void insert(std::string key, int value) override {
        _insert(key, value);
        _size++;
    }

    bool contains(const std::string &key) const override {
        return _contains(key);
    }

    int get(const std::string &key) const override {
        return _get(key);
    }

    int &operator[](const std::string& key) override {
        int hashcode = _hash(key);
        int position = hashcode % capacity;
        auto &slot = pairs[position];
        for (auto &pair : slot) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        _insert(key, 0);
        return slot.back().second;
    }

    bool remove(const std::string &key) override {
        return _remove(key);
        _size--;
    }

    void clear() override {
        delete [] pairs;
    }

    int numBuckets() const override {
        return capacity;
    }

    int size() const override {
        return _size;
    }
};