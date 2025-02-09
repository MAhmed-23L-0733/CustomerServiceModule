#pragma once
#include <iostream>
#include <vector>
#include "User.cpp"
using namespace std;
class HashTable_int
{
private:
    int size;
    vector<int> table;
    vector<User *> users;
    const int a = 33;

    int HashFunction(const int &key)
    {
        // universal hash function / pseudo-random
        return ((5 * key + 7) % 17) % size;
    }
    int SecondHashFunction(const int &key)
    {
        return 17 - (key % 17);
    }

public:
    User *Search(int key)
    {
        int index = HashFunction(key);
        if (table[index] == key)
        {
            return users[index];
        }
        else
        {
            for (int i = 0; i < size; i++)
            {
                index = (HashFunction(key) + ((i + 1) * SecondHashFunction(key))) % size;
                if (table[index] == key)
                {
                    if (users[index] == 0)
                    {
                        return 0;
                    }
                    return users[index];
                }
            }
            return 0;
        }
    }
    HashTable_int(int size)
    {
        this->size = size;
        table.resize(size, -1);
    }
    HashTable_int()
    {
    }
    void SetSize(int size)
    {
        this->size = size;
        table.resize(size, -1);
        users.resize(size);
    }

    void Insert(const int key, User *u)
    {
        int index = HashFunction(key);
        if (table[index] == -1)
        {
            table[index] = key;
            users[index] = u;
        }
        else
        {
            for (int i = 0; i < size; i++)
            {
                index = (HashFunction(key) + ((i + 1) * SecondHashFunction(key))) % size;
                if (table[index] == -1)
                {
                    table[index] = key;
                    users[index] = u;
                    return;
                }
            }
        }
        return;
    }
    void Delete(int key)
    {
        int index = HashFunction(key);
        if (table[index] == key)
        {
            delete users[index];
            users[index] = nullptr;
        }
        else
        {
            for (int i = 0; i < size; i++)
            {
                index = (HashFunction(key) + ((i + 1) * SecondHashFunction(key))) % size;
                if (table[index] == key)
                {
                    delete users[index];
                    users[index] = nullptr;
                }
            }
        }
    }
    void PrintTable()
    {
        for (int i = 0; i < size; ++i)
        {
            cout << table[i] << endl;
        }
    }
};
