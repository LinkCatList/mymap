#include <algorithm>
#include <iostream>
#include <vector>
#include <list>


class BadHashTable {
private:
    int size;
    std::vector<std::list<std::pair<int, std::string>>> table;

    int hashFunction(int key) {
        return std::hash<int>{}(key) % size;
    }
public:
    BadHashTable(int s) {
        this->size = s;
        table.resize(s);
    }

    void insert(int key, const std::string &value) {
        int index = hashFunction(key);
        table[index].push_back(std::make_pair(key, value));
    }

    std::string search(int key) {
        int index = hashFunction(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        return "not found";
    }

    void remove(int key) {
        int index = hashFunction(key);
        table[index].remove_if([key](const std::pair<int, std::string>& pair) {
            return pair.first == key;
        });
    }
};