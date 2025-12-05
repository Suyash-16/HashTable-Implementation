#include <iostream>
#include <string>
using namespace std;

class QuadraticHashTable
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
    QuadraticHashTable();
    int hashFunction(int key);
    bool isEmpty() const;

    void insertItem(int key, string value);
    string searchTable(int key);
    void removeItem(int key);
    void printTable();
};

QuadraticHashTable::QuadraticHashTable()
{
    for (int i = 0; i < hashGroups; i++)
    {
        table[i].occupied = false;
        table[i].deleted = false;
    }
}

int QuadraticHashTable::hashFunction(int key)
{
    return key % hashGroups;
}

bool QuadraticHashTable::isEmpty() const
{
    for (int i = 0; i < hashGroups; i++)
    {
        if (table[i].occupied)
            return false;
    }
    return true;
}

// QUADRATIC PROBING

void QuadraticHashTable::insertItem(int key, string value)
{
    int index = hashFunction(key);

    for (int i = 0; i < hashGroups; i++)
    {
        int newIndex = (index + i * i) % hashGroups;

        if (!table[newIndex].occupied || table[newIndex].deleted)
        {
            table[newIndex].key = key;
            table[newIndex].value = value;
            table[newIndex].occupied = true;
            table[newIndex].deleted = false;
            return;
        }

        if (table[newIndex].occupied && table[newIndex].key == key)
        {
            table[newIndex].value = value;
            return;
        }
    }

    cout << "[ERROR] Hash table full. Cannot insert key " << key << endl;
}

string QuadraticHashTable::searchTable(int key)
{
    int index = hashFunction(key);

    for (int i = 0; i < hashGroups; i++)
    {
        int newIndex = (index + i * i) % hashGroups;

        if (!table[newIndex].occupied && !table[newIndex].deleted)
            return "Key not found";

        if (table[newIndex].occupied && table[newIndex].key == key)
            return table[newIndex].value;
    }

    return "Key not found";
}

void QuadraticHashTable::removeItem(int key)
{
    int index = hashFunction(key);

    for (int i = 0; i < hashGroups; i++)
    {
        int newIndex = (index + i * i) % hashGroups;

        if (!table[newIndex].occupied && !table[newIndex].deleted)
        {
            cout << "[WARNING] Key not found. Cannot delete." << endl;
            return;
        }

        if (table[newIndex].occupied && table[newIndex].key == key)
        {
            table[newIndex].occupied = false;
            table[newIndex].deleted = true;
            cout << "[INFO] Key deleted." << endl;
            return;
        }
    }

    cout << "[WARNING] Key not found. Cannot delete." << endl;
}

void QuadraticHashTable::printTable()
{
    cout << endl << "------- HASH TABLE (Quadratic Probing) -------" << endl;
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
    cout << "----------------------------------------------" << endl;
}

int main()
{
    QuadraticHashTable QHT;

    cout << "Inserting values (Quadratic)..." << endl;
    QHT.insertItem(12, "Suyash");
    QHT.insertItem(22, "Vedant");
    QHT.insertItem(32, "Shaury");
    QHT.insertItem(42, "Amrit");
    QHT.insertItem(52, "Abhishek");
    QHT.insertItem(62, "Dinesh");
    QHT.insertItem(72, "Prakhar");

    QHT.printTable();

    //Search
    cout << endl << "Searching key 22: ";
    cout << QHT.searchTable(22) << endl;
    
    // Deletion
    cout << endl << "Deleting key 32..." << endl;
    QHT.removeItem(32);

    QHT.printTable();

    return 0;
}
