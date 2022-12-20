#include "dictionary.h"

Dictionary::Dictionary(int num_of_buckets, HashFunction hash) :
    table(num_of_buckets), hash_function(hash) {
}

Dictionary::~Dictionary() {
}

void Dictionary::set(const std::string& key, const std::string& value) {
    int index = hash_function(key) % table.size();
    bool fl = false;
    std::pair<std::string, std::string> p(key, value);
    for (auto& bucket : table[index])
        if (bucket.first == key) {
            bucket.second.replace(bucket.second.begin(), bucket.second.end(), value);
            fl = true;
        }
    if (!fl)
        table[index].push_back(p);
}

std::string Dictionary::get(const std::string& key) const {
    int index = hash_function(key) % table.size();
    if (table[index].size() != 0)
        for (const auto& bucket : table[index])
            if (bucket.first == key)
                return bucket.second;
    return "";
}

int Dictionary::size() const {
    int size = 0;
    for (const auto& bucket : table){
        size += bucket.size();
    }
    return size;
}
