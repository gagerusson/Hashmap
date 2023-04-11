// YOU MAY NOT MODIFY THIS DOCUMENT

#pragma once

#include <string>

const size_t INITIAL_BUCKETS = 10;
const size_t GROW_FACTOR = 2;
const double MAX_LOAD_FACTOR = 0.8;

class HashmapInterface {
public:
    virtual ~HashmapInterface() {}

    /*
     * Insert a key/value pair into the map
     *  If key is not in the map yet, add new key/value pair to map
     *  If key is already in the map, replace old value with new value
     */
    virtual void insert(std::string key, int value) = 0;

    /*
     * Test if the key exists in the map
     *  Return true if one of the nodes in the map has the given key, false otherwise
     */
    virtual bool contains(const std::string &key) const = 0;

    /*
     * Return the value associated with the given key in the map
     *  Throw invalid_argument exception if key is not in map
     */
    virtual int get(const std::string &key) const = 0;

    /*
     * Return a reference to a value associated with the given key in the map
     *  This will allow you use syntax such as map['pig'] to get the value
     *   for the given key
     *  This will also allow you use sytnax such as map['pig']=10 to set/update
     *   the value for the given key
     *  If the node with the given key is found in the map, return that node's value
     *  If the node with the given key is not found in the map, insert a new node with
     *   the given key and a value of 0 into the map, then return newNode->value
     */
    virtual int &operator[](const std::string &key) = 0;

    /*
     * Remove the node with given key from the map
     *  Return true if node is found and removed
     *  Return false if the key does not exist in the map
     */
    virtual bool remove(const std::string &key) = 0;

    /*
     * Reset map to empty
     */
    virtual void clear() = 0;

    /*
     * Return the size of the internal hash table.
     *
     * This is not the number of items in the map,
     * but is the length of the array used as the hash table.
     *
     * Normally you would not expose this information (the number of buckets being used)
     * in a public interface, but this information is needed for the project tests.
     */
    virtual int numBuckets() const = 0;

    /*
     * Return number of keys in map
     */
    virtual int size() const = 0;
};
