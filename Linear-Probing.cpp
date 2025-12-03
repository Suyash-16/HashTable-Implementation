#include <iostream>
#include <string>
using namespace std;

class HashTable
{
private:
    static const int hashGroups = 10;

    struct HashNode
    {
        int key;
        string value;
        bool occupied;
        bool deleted;
    };

    HashNode table[hashGroups];

public:
    HashTable();
    int hashFunction(int key);
    bool isEmpty() const;
    // Linear Probing
    void insertItem(int key, string value);
    string searchTable(int key);
    void removeItem(int key);
    void printTable();
};

HashTable::HashTable()
{
    for (int i = 0; i < hashGroups; i++)
    {
        table[i].occupied = false;
        table[i].deleted = false;
    }
}

int HashTable::hashFunction(int key)
{
    return key % hashGroups;
}

bool HashTable::isEmpty() const
{
    for (int i = 0; i < hashGroups; i++)
    {
        if (table[i].occupied)
            return false;
    }
    return true;
}

void HashTable::insertItem(int key, string value)
{
    int index = hashFunction(key);
    int startIndex = index;

    do
    {
        // Insert if slot is empty
        if (!table[index].occupied || table[index].deleted)
        {
            table[index].key = key;
            table[index].value = value;
            table[index].occupied = true;
            table[index].deleted = false;
            return;
        }

        // Update existing key
        if (table[index].occupied && table[index].key == key)
        {
            table[index].value = value;
            return;
        }

        // Linear probing
        index = (index + 1) % hashGroups;

    } while (index != startIndex);

    cout << "[ERROR] Hash table full. Cannot insert key " << key << endl;
}

string HashTable::searchTable(int key)
{
    int index = hashFunction(key);
    int startIndex = index;

    do
    {
        if (!table[index].occupied && !table[index].deleted)
            return "Key not found";

        if (table[index].occupied && table[index].key == key)
            return table[index].value;

        index = (index + 1) % hashGroups;

    } while (index != startIndex);

    return "Key not found";
}

void HashTable::removeItem(int key)
{
    int index = hashFunction(key);
    int startIndex = index;

    do
    {
        if (!table[index].occupied && !table[index].deleted)
        {
            cout << "[WARNING] Key not found. Cannot delete.\n";
            return;
        }

        if (table[index].occupied && table[index].key == key)
        {
            table[index].occupied = false;
            table[index].deleted = true; // deletion
            cout << "[INFO] Key deleted.\n";
            return;
        }

        index = (index + 1) % hashGroups;

    } while (index != startIndex);

    cout << "[WARNING] Key not found. Cannot delete.\n";
}

void HashTable::printTable()
{
    cout << "\n------- HASH TABLE (Linear Probing) -------\n";
    for (int i = 0; i < hashGroups; i++)
    {
        cout << "Index " << i << ": ";
        if (table[i].occupied)
            cout << "Key = " << table[i].key << ", Value = " << table[i].value;
        else if (table[i].deleted)
            cout << "<DELETED>";
        else
            cout << "EMPTY";
        cout << endl;
    }
    cout << "--------------------------------------------\n";
}

// MAIN FUNCTION

int main()
{
    HashTable HT;

    cout << "Inserting values...\n";
    HT.insertItem(12, "Suyash");
    HT.insertItem(22, "Vedant");
    HT.insertItem(32, "Shaury");
    HT.insertItem(42, "Amrit");
    HT.insertItem(52, "Abhishek");
    HT.insertItem(62, "Dinesh");
    HT.insertItem(72, "Prakhar");

    HT.printTable();

    cout << "\nSearching for key 22: ";
    cout << HT.searchTable(22) << endl;

    cout << "\nSearching for key 99: ";
    cout << HT.searchTable(99) << endl;

    cout << "\nDeleting key 32...\n";
    HT.removeItem(32);

    HT.printTable();

    cout << "\nTrying to delete non-existing key 999...\n";
    HT.removeItem(999);

    HT.printTable();

    return 0;
}
