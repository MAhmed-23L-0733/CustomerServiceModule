#include <iostream>
#include <vector>
#include <string>
#include "User.cpp"
using namespace std;
class HashTable_type
{
private:
    int size;
    vector<string> table;
    vector<User *> users;
    const int a = 33;

    int HashFunction(const string &key)
    {
        int hashCode = 0;
        for (size_t i = 0; i < key.length(); ++i)
        {
            hashCode = (hashCode * a + key[i]) % size;
        }
        return hashCode % size;
    }

public:
    void Delete(string key)
    {
        bool found = false;
        int index = 0;
        for (int i = 0; i < size; i++)
        {
            index = (HashFunction(key) + (i) * (i)) % size;
            if (table[index] == key)
            {
                delete users[index];
                users[index] = nullptr;
            }
            if (table[index] == "-1")
            {
                return;
            }
        }
        if (!found)
        {
            cerr << "\nUser does not exist!" << endl;
        }
    }
    void Search(string key)
    {
        bool found = false;
        int index = 0;
        for (int i = 0; i < size; i++)
        {
            index = (HashFunction(key) + (i) * (i)) % size;
            if (table[index] == key)
            {
                if (users[index] == 0)
                {
                    cerr << "User does not exist!" << endl;
                    return;
                }
                users[index]->print();
                found = true;
            }
            if (table[index] == "-1")
            {
                return;
            }
        }
        if (!found)
        {
            cerr << "\nUser does not exist!" << endl;
        }
    }
    HashTable_type(int size)
    {
        this->size = size;
        table.resize(size, "-1");
    }
    HashTable_type()
    {
    }
    void SetSize(int size)
    {
        this->size = size;
        table.resize(size, "-1");
        users.resize(size);
    }

    void Insert(const string key, User *u)
    {
        int index = HashFunction(key);
        if (table[index] == "-1")
        {
            table[index] = key;
            users[index] = u;
        }
        else
        {
            for (int i = 0; i < size; i++)
            {
                index = (HashFunction(key) + (i + 1) * (i + 1)) % size; // quadratic probing
                if (table[index] == "-1")
                {
                    table[index] = key;
                    users[index] = u;
                    return;
                }
            }
        }
        return;
    }

    void PrintTable()
    {
        for (int i = 0; i < size; ++i)
        {
            cout << table[i] << endl;
        }
    }
};
