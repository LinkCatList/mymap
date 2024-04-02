#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <chrono>
#include <unordered_map>
#include "myGoodMap.hpp"
#include "myBadMap.hpp"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist(1, 100);
const int sz = 1000;
std::string generateRandomString(int len) {
    static const char alphanum[] = "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    std::string randomString;
    for (int i = 0; i < len; i++) {
        randomString += alphanum[rd() % (sizeof(alphanum) - 1)];
    }
    return randomString;
}
std::tuple<double, double, double> test1(std::vector<std::pair<int, std::string>> &test){
    GoodHashTable ht1(101);
    double timerInsert = 0, timerSearch = 0, timerRemove = 0;
    // --------------------------------------------------------------

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < sz; ++i) {
        int key = test[i].first;
        std::string value = test[i].second;
        ht1.insert(key, value);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    timerInsert = duration.count();

    // --------------------------------------------------------------

    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < sz; ++i) {
        int key = test[i].first;
        ht1.search(key);
    }
    
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;

    timerSearch = duration.count();

    // --------------------------------------------------------------

    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < sz; ++i) {
        int key = test[i].first;
        ht1.remove(key);
    }
    
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;

    timerRemove = duration.count();
    // --------------------------------------------------------------

    return {timerInsert, timerSearch, timerRemove};
}

std::tuple<double, double, double> test2(std::vector<std::pair<int, std::string>> &test){
    BadHashTable ht1(101);
    double timerInsert = 0, timerSearch = 0, timerRemove = 0;
    // --------------------------------------------------------------

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < sz; ++i) {
        int key = test[i].first;
        std::string value = test[i].second;
        ht1.insert(key, value);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    timerInsert = duration.count();

    // --------------------------------------------------------------

    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < sz; ++i) {
        int key = test[i].first;
        ht1.search(key);
    }
    
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;

    timerSearch = duration.count();

    // --------------------------------------------------------------

    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < sz; ++i) {
        int key = test[i].first;
        ht1.remove(key);
    }
    
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;

    timerRemove = duration.count();
    // --------------------------------------------------------------

    return {timerInsert, timerSearch, timerRemove};
}

std::tuple<double, double, double> test3(std::vector<std::pair<int, std::string>> &test){
    std::unordered_map<int, std::string>ht1;
    double timerInsert = 0, timerSearch = 0, timerRemove = 0;
    // --------------------------------------------------------------

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < sz; ++i) {
        int key = test[i].first;
        std::string value = test[i].second;
        ht1[key] = value;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    timerInsert = duration.count();

    // --------------------------------------------------------------

    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < sz; ++i) {
        int key = test[i].first;
        auto it = ht1.find(key);
    }
    
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;

    timerSearch = duration.count();

    // --------------------------------------------------------------

    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < sz; ++i) {
        int key = test[i].first;
        ht1.erase(key);
    }
    
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;

    timerRemove = duration.count();
    // --------------------------------------------------------------

    return {timerInsert, timerSearch, timerRemove};
}
int32_t main() {
    std::cout << std::fixed << std::setprecision(10);

    double averageInsertGood = 0, averageSearchGood = 0, averageRemoveGood = 0;
    double averageInsertBad = 0, averageSearchBad = 0, averageRemoveBad = 0;
    double averageInsertStd= 0, averageSearchStd = 0, averageRemoveStd = 0;

    for (int q = 0; q<50000; q++) {
        std::vector<std::pair<int, std::string>> test;

        for (int i = 0; i < sz; ++i) {
            std::string value = generateRandomString(8);
            int key = dist(gen);
            test.push_back({key, value});
        }

        auto t1 = test1(test);
        auto t2 = test2(test);
        auto t3 = test3(test);

        averageInsertGood += std::get<0>(t1);
        averageSearchGood += std::get<1>(t1);
        averageRemoveGood += std::get<2>(t1);

        averageInsertBad += std::get<0>(t2);
        averageSearchBad += std::get<1>(t2);
        averageRemoveBad += std::get<2>(t2);

        averageInsertStd += std::get<0>(t3);
        averageSearchStd += std::get<1>(t3);
        averageRemoveStd += std::get<2>(t3);


    }

    std::cout << "Average goodMap: \n";
    std::cout << "Average insert: " << averageInsertGood / 1000 << "\n";
    std::cout << "Average search: " << averageSearchGood / 1000 << "\n";
    std::cout << "Average remove: " << averageRemoveGood / 1000 << "\n";

    std::cout << "Average badMap: \n";
    std::cout << "Average insert: " << averageInsertBad / 1000 << "\n";
    std::cout << "Average search: " << averageSearchBad / 1000 << "\n";
    std::cout << "Average remove: " << averageRemoveBad / 1000 << "\n";

    std::cout << "Average StdMap: \n";
    std::cout << "Average insert: " << averageInsertStd / 1000 << "\n";
    std::cout << "Average search: " << averageSearchStd / 1000 << "\n";
    std::cout << "Average remove: " << averageRemoveStd / 1000 << "\n";

    return 0;
}