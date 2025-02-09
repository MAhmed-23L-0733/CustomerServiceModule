#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "User.cpp"
using namespace std;
class HashTable
{
private:
    struct Node
    {
        string key;
        int value;
        User *u;
        Node *next;

        Node(string k, int v, User *u)
        {
            key = k;
            value = v;
            this->u = u;
            next = nullptr;
        }
        string GetKey()
        {
            return key;
        }
    };

    int size;
    vector<Node *> table;
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
    User *Search(string key)
    {
        int index = HashFunction(key);
        if (table[index] == 0)
        {
            return 0;
        }
        else
        {
            Node *temp = table[index];
            while (temp != 0)
            {
                if (temp->GetKey() == key)
                {
                    if (temp->u == 0)
                    {
                        return 0;
                    }
                    return temp->u;
                }
                temp = temp->next;
            }
            return 0;
        }
    }
    HashTable(int size)
    {
        this->size = size;
        table.resize(size, nullptr);
    }
    HashTable()
    {
    }
    void SetSize(int size)
    {
        this->size = size;
        table.resize(size, nullptr);
    }
    ~HashTable()
    {
        for (int i = 0; i < size; ++i)
        {
            Node *current = table[i];
            while (current)
            {
                Node *toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
    }

    void Insert(const string key, int value, User *u)
    {
        int index = HashFunction(key);
        Node *newNode = new Node(key, value, u);

        newNode->next = table[index];
        table[index] = newNode;
    }

    void PrintTable()
    {
        for (int i = 0; i < size; ++i)
        {
            cout << "[" << i << "]: ";
            Node *current = table[i];
            while (current)
            {
                cout << "(" << current->key << ", " << current->value << ") -> ";
                current = current->next;
            }
            cout << "nullptr" << endl;
        }
    }
    void Delete(string key)
    {
        int index = HashFunction(key);
        if (table[index] == 0)
        {
            return;
        }
        else
        {
            Node *temp = table[index];
            while (temp != 0)
            {
                if (temp->GetKey() == key)
                {
                    delete temp->u;
                    temp->u = nullptr;
                    return;
                }
                temp = temp->next;
            }
        }
    }
};
