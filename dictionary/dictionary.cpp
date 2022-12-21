#include "dictionary.h"
#include <iostream>
#include <chrono>

Dictionary::Dictionary(int num_of_buckets, HashFunction hash) :
    table(num_of_buckets), hash_function(hash) {
}

Dictionary::~Dictionary() {
}

void Dictionary::set(const std::string& key, const std::string& value) {
    std::cout << "Key: " << key << "; Value: " << value << std::endl; 
    auto t1 = std::chrono::high_resolution_clock::now();
    int index = hash_function(key) % table.size();
    bool found = false;
    std::pair<std::string, std::string> p(key, value);
    for (auto& bucket : table[index])
        if (bucket.first == key) {
            bucket.second.replace(bucket.second.begin(), bucket.second.end(), value);
            found = true;
        }
    if (!found)
        table[index].push_back(p);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration<double>(t2 - t1).count();
    std::cout << "Set operation: " << time << " sec." << std::endl;
    std::cout << std::endl;
}

std::string Dictionary::get(const std::string& key) const {
    std::cout << "Key: " << key << ";" << std::endl; 
    auto t1 = std::chrono::high_resolution_clock::now();
    int index = hash_function(key) % table.size();
    if (table[index].size() != 0)
        for (const auto& bucket : table[index])
            if (bucket.first == key)
            {
                auto t2 = std::chrono::high_resolution_clock::now();
                auto time = std::chrono::duration<double>(t2 - t1).count();
                std::cout << "Get operation: " << time << std::endl;
                std::cout << std::endl;
                return bucket.second;
            }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration<double>(t2 - t1).count();
    std::cout << "Get operation: " << time << std::endl;
    std::cout << std::endl;
    return "";
}

int Dictionary::size() const {
    int size = 0;
    for (const auto& bucket : table){
        size += bucket.size();
    }
    return size;
}
