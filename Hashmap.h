#pragma once

#include <string>
#include <list>
#include <utility>
#include <exception>
#include <sstream>

#include "HashmapInterface.h"

using namespace std;
using Bucket = list<pair<string, int>>;

class Hashmap : public HashmapInterface {
private:
    int capacity;
    int _size;
    Bucket * pairs;

    int _hash(const string &key, int cap = 0) const {
        if (cap == 0) {
            cap = capacity;
        }
        char ch[key.length()];
        key.copy(ch, key.length());
        int i, sum;
        for (sum = 0, i = 0; i < key.length(); i++) {
            sum += ch[i];
        }
        return sum % cap;
    }

    void _insert(string key, int value) {
        int hashcode = _hash(key);
        int position = hashcode % capacity;
        auto &slot = pairs[position];
        if (_contains(key)) {
            remove(key);
        }
        slot.push_back(pair<string, int>(key, value));
    }

    double loadFactor() const {
        return static_cast<double>(_size) / capacity;
    }

    void _grow() {
        int newCapacity = capacity * GROW_FACTOR;
        Bucket * newPairs = new Bucket[newCapacity];
        for (int i = 0; i < capacity; i++) {
            auto &slot = pairs[i];
            for (auto &pair : slot) {
                int hashcode = _hash(pair.first, newCapacity);
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
        try {
            _get(key);
            return true;
        } catch (invalid_argument &e) {
            return false;
        }
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
        throw invalid_argument("Key not found");
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
        if (loadFactor() > MAX_LOAD_FACTOR) {
            _grow();
        }
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
        insert(key, 0);
        return pairs[position].back().second;
    }

    bool remove(const std::string &key) override {
        bool is_removed = _remove(key);
        if (is_removed) _size--;
        return is_removed;
    }

    void clear() override {
        delete[] pairs;
        pairs = new Bucket[capacity];
        _size = 0;
    }

    int numBuckets() const override {
        return capacity;
    }

    int size() const override {
        return _size;
    }

};