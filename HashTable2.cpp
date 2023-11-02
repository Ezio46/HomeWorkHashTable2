#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int TABLE_SIZE = 100;

class HashTable {
private:
    struct Entry {
        string key;
        int value;
        bool deleted;

        Entry() : deleted(false) {}
    };

    vector<Entry> table;

    int hash(const string& key) {
        int hash = 0;
        for (char c : key) {
            hash += c;
        }
        return hash % TABLE_SIZE;
    }

    int quadraticProbe(int index, int i) {
        return (index + i * i) % TABLE_SIZE;
    }

public:
    HashTable() : table(TABLE_SIZE) {}

    void insert(const string& key, int value) {
        int index = hash(key);

        for (int i = 0; i < TABLE_SIZE; i++) {
            int probeIndex = quadraticProbe(index, i);

            if (table[probeIndex].key.empty() || table[probeIndex].deleted) {
                table[probeIndex].key = key;
                table[probeIndex].value = value;
                table[probeIndex].deleted = false;
                return;
            }
        }

    }

    int get(const string& key) {
        int index = hash(key);

        for (int i = 0; i < TABLE_SIZE; i++) {
            int probeIndex = quadraticProbe(index, i);

            if (table[probeIndex].key == key && !table[probeIndex].deleted) {
                return table[probeIndex].value;
            }
        }

        return -1;
    }

    void remove(const string& key) {
        int index = hash(key);

        for (int i = 0; i < TABLE_SIZE; i++) {
            int probeIndex = quadraticProbe(index, i);

            if (table[probeIndex].key == key) {
                table[probeIndex].deleted = true;
                return;
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
