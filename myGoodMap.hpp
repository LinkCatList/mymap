#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

const int N = 18732239;

class GoodHashTable {
private:
    int size;
    std::vector<std::map<int, std::string>> table;

    int hashFunction(int key) {
        return std::hash<int>{}(key) % size;
    }
public:
    GoodHashTable(int s) {
        this->size = s;
        table.resize(s);
    }

    void insert(int key, const std::string &value) {
        int index = hashFunction(key);
        table[index].insert(std::make_pair(key, value));
    }

    std::string search(int key) {
        int index = hashFunction(key);

        auto it = table[index].find(key);

        if (it != table[index].end()){
            return it->second;
        }
        
        return "not found";
    }

    void remove(int key) {
        int index = hashFunction(key);

        if(table[index].find(key) != table[index].end()){
            table[index].erase(key);
        }
    }
};