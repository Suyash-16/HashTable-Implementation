#include <iostream>
#include <list>
#include <string>
using namespace std;

class HashTable {
private:
    static const int hashGroups = 10;
    list<pair<int, string>> table[hashGroups];  
    // table[0], table[1], ..., table[9]

public:
    bool isEmpty() const;
    int hashFunction(int key);
    void insertItem(int key, string value);
    void removeItem(int key);
    string searchTable(int key);
    void printTable();
};

bool HashTable::isEmpty() const {
    int sum = 0;
    for (int i = 0; i < hashGroups; i++) {
        sum += table[i].size();
    }

    if (!sum) return true;
    return false;
}

int HashTable::hashFunction(int key) {
    return key % hashGroups;
}

void HashTable::insertItem(int key, string value) {
    int hashValue = hashFunction(key);
    auto& cell = table[hashValue];
    auto bItr = begin(cell);
    bool keyExists = false;

    for (; bItr != end(cell); bItr++) {
        if (bItr->first == key) {
            keyExists = true;
            bItr->second = value;
            cout << "[WARNING] Key exists. Value replaced." << endl;
            break;
        }
    }

    if (!keyExists) {
        cell.emplace_back(key, value);
    }
}

void HashTable::removeItem(int key) {
    int hashValue = hashFunction(key);
    auto& cell = table[hashValue];
    auto bItr = begin(cell);
    bool keyExists = false;

    for (; bItr != end(cell); bItr++) {
        if (bItr->first == key) {
            keyExists = true;
            bItr = cell.erase(bItr);
            cout << "[INFO] Pair removed." << endl;
            break;
        }
    }

    if (!keyExists) {
        cout << "[WARNING] Key not found. Pair not removed." << endl;
    }
}

string HashTable::searchTable(int key) {
    int hashValue = hashFunction(key);
    auto& cell = table[hashValue];
    auto bItr = begin(cell);

    for (; bItr != end(cell); bItr++) {
        if (bItr->first == key) {
            return bItr->second;
        }
    }

    return "Key not found";
}

void HashTable::printTable() {
    for (int i = 0; i < hashGroups; i++) {
        if (table[i].size() == 0) continue;

        auto bItr = table[i].begin();
        for (; bItr != table[i].end(); bItr++) {
            cout << "[INFO] Key: " << bItr->first
                 << " Value: " << bItr->second << endl;
        }
    }
}


int main() {
    HashTable HT;

    cout << "Inserting key-value pairs...\n";
    HT.insertItem(101, "Suyash");
    HT.insertItem(202, "Vedant");
    HT.insertItem(303, "Shaury");
    HT.insertItem(404, "Amrit");
    HT.insertItem(505, "Abhishek");
    HT.insertItem(606, "Dinesh");
    HT.insertItem(707, "Prakhar");

    cout << "\nPrinting table:\n";
    HT.printTable();

    cout << "\nSearching for key 202:\n";
    cout << HT.searchTable(202) << endl;   // returns Vedant

    cout << "\nRemoving key 303:\n";
    HT.removeItem(303);   // Remove Shaury

    cout << "\nPrinting table after removing 303:\n";
    HT.printTable();

    cout << "\nTrying to remove non-existent key 999:\n";
    HT.removeItem(999);

    return 0;  
}

