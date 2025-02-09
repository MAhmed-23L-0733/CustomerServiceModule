#pragma once
#include <iostream>
using namespace std;
template <class T>
struct node
{
    T *data;
    node *next;
    node *prev;
    node()
    {
        next = 0;
        prev = 0;
    }
    node(T *data)
    {
        this->data = data;
    }
};
template <class T>
class DLL
{
private:
    node<T> *head;
    node<T> *tail;

public:
    // operator overloaders
    friend ostream &operator<<(ostream &cout, DLL &DLL)
    {
        DLL.Print();
        return cout;
    }
    // methods
    DLL()
    {
        head = new node<T>(0);
        tail = new node<T>(0);
        head->next = tail;
        tail->prev = head;
    }
    void SwapNodes(node<T> *&ptr1, node<T> *&ptr2)
    {
        node<T> *ptr1Next = ptr1->next;
        node<T> *ptr1prev = ptr1->prev;
        if (ptr1->next == ptr2)
        {
            ptr1->next = ptr2->next;
            ptr1->prev = ptr2;
            ptr2->next = ptr1;
            ptr2->prev = ptr1prev;
            ptr1prev->next = ptr2;
            ptr1->next->prev = ptr1;
        }
        else
        {
            ptr1->next = ptr2->next;
            ptr1->prev = ptr2->prev;
            ptr2->next->prev = ptr1;
            ptr2->prev->next = ptr1;
            ptr2->next = ptr1Next;
            ptr2->prev = ptr1prev;
            ptr1Next->prev = ptr2;
            ptr1prev->next = ptr2;
        }
    }
    void AddToStart(const T &value)
    {
        node<T> *temp = head->next;
        head->next = new node(value);
        head->next->next = temp;
        temp->prev = head->next;
        head->next->prev = head;
    }
    void AddToEnd(const T &value)
    {
        node<T> *temp = tail->prev;
        tail->prev = new node(value);
        tail->prev->next = tail;
        tail->prev->prev = temp;
        temp->next = tail->prev;
    }
    void AddToEnd(node<T> *n)
    {
        node<T> *temp = tail->prev;
        tail->prev = n;
        tail->prev->next = tail;
        tail->prev->prev = temp;
        temp->next = tail->prev;
    }
    void Print()
    {
        node<T> *i = head->next;
        while (i != tail)
        {
            i->data->print();
            i = i->next;
        }
    }
    void DeleteNode(node<T> *n)
    {
        node<T> *temp = n->next;
        node<T> *temp2 = n->prev;
        delete n;
        temp->prev = temp2;
        temp2->next = temp;
    }
    void InsertAfter(node<T> *after, node<T> *source)
    {
        source->next = after->next;
        source->next->prev = source;
        after->next = source;
        source->prev = after;
    }
    void InsertBefore(node<T> *before, node<T> *source)
    {
        source->prev = before->prev;
        source->prev->next = source;
        before->prev = source;
        source->next = before;
    }
};