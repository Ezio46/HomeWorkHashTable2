#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

const int TABLE_SIZE = 100;

// Хеш-функции Пирсона
unsigned int pearsonHash(const string& key) {
    const unsigned char* data = reinterpret_cast<const unsigned char*>(key.c_str());
    unsigned int hash = 0;

    for (size_t i = 0; i < key.length(); ++i) {
        hash = 59 * hash + data[i];
    }

    return hash % TABLE_SIZE;
}

class HashTable {
private:
    vector<list<pair<string, int>>> table;

public:
    HashTable() : table(TABLE_SIZE) {}

    void insert(const string& key, int value) {
        unsigned int index = pearsonHash(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        table[index].push_back(make_pair(key, value));
    }

    int get(const string& key) {
        unsigned int index = pearsonHash(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        return -1;
    }

    void remove(const string& key) {
        unsigned int index = pearsonHash(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it);
                break;
            }
        }
    }
};

int main() {

    HashTable hashTable;

    hashTable.insert("cat", 1);
    hashTable.insert("hat", 15);
    hashTable.insert("kit", 6);

    cout << "Value of cat: " << hashTable.get("cat") << endl;
    cout << "Value of hat: " << hashTable.get("hat") << endl;
    cout << "Value of kit: " << hashTable.get("kit") << endl;

    hashTable.remove("cat");
    cout << "Value of cat after remove: " << hashTable.get("cat") << endl;

    return 0;
}
