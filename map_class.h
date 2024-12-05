//
// Created by MaryA on 12/4/2024.
//

#ifndef PROJECT3_MAP_CLASS_H
#define PROJECT3_MAP_CLASS_H
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <stdexcept>
using namespace std;

// Simplified HashMap for string keys and BTree values
class HashMap {
private:
    struct Entry {
        string key;
        BTree value;
        bool isOccupied;

        // Default constructor for an empty slot
        Entry() : isOccupied(false), value(0) {}

        // Constructor for a key-value pair
        Entry(const string& k, const BTree& v)
                : key(k), value(v), isOccupied(true) {}
    };

    std::vector<Entry> table;
    size_t tableSize;

    // Hash function
    size_t hash(const string& key) const {
        ::hash<string> hasher;
        return hasher(key) % tableSize;
    }

    // Find the index of a key or an available slot
    size_t findSlot(const string& key) const {
        size_t index = hash(key);
        size_t startIndex = index;

        while (table[index].isOccupied && table[index].key != key) {
            index = (index + 1) % tableSize; // Linear probing
            if (index == startIndex) {
                throw overflow_error("Hash table is full");
            }
        }
        return index;
    }

public:
    // Constructor with a fixed table size
    HashMap(size_t size) : table(size), tableSize(size) {}

    // Insert a key-value pair
    void insert(const string& key, const BTree& value) {
        size_t index = findSlot(key);

        if (!table[index].isOccupied) {
            table[index] = Entry(key, value); // Insert new entry
        } else if (table[index].key == key) {
            table[index].value = value; // Update existing value
        }
    }

    // Retrieve the value associated with a key
    BTree get(const string& key) const {
        size_t index = findSlot(key);

        if (table[index].isOccupied && table[index].key == key) {
            return table[index].value;
        } else {
            throw runtime_error("Key not found");
        }
    }

    // Key exists: checking to see if key exits
    bool key_exists(const string& key) const {
        cout << "Key exists?";
        size_t index = findSlot(key);
        if (table[index].isOccupied && table[index].key == key) {
            cout << "yes it does" << endl;
            return true;
        } else {
            cout << "false" << endl;
            return false;
        }
    }
};

#endif //PROJECT3_MAP_CLASS_H
