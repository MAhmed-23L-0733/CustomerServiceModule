#pragma once
#include <iostream>
#include <vector>
#include "User.cpp"
#include "AVLTree.cpp"
#include "AVLGroupTree.cpp"
using namespace std;
class PriorityQueue;
class Complaint
{
private:
    static int complaintCounter;
    int complaintId;
    int userId;
    int userPriority;
    string description;

public:
    friend class PriorityQueue;
    Complaint(int userid, int type, string desc)
    {
        complaintId = complaintCounter + 1;
        complaintCounter++;
        userId = userid;
        description = desc;
        userPriority = type;
    }
};
int Complaint::complaintCounter = 0;
class PriorityQueue
{
private:
    vector<pair<int, Complaint *>> heap;
    AVL<int> userComplaintIds;
    AVLGroupTree<int> countryGroup;

public:
    void HeapUp(int index)
    {
        if (index == 0)
            return;
        int parentIndex = (index - 1) / 2;
        if (heap[index].second->userPriority > heap[parentIndex].second->userPriority)
        {
            swap(heap[index], heap[parentIndex]);
            HeapUp(parentIndex);
        }
        else if (heap[index].second->userPriority == heap[parentIndex].second->userPriority)
        {
            if (heap[index].second->complaintId < heap[parentIndex].second->complaintId)
            {
                swap(heap[index], heap[parentIndex]);
                HeapUp(parentIndex);
            }
        }
        if (index == (parentIndex * 2 + 2))
        {
            int leftSibling = parentIndex * 2 + 1;
            if (heap[index].second->userPriority > heap[leftSibling].second->userPriority)
            {
                swap(heap[index], heap[leftSibling]);
                HeapUp(leftSibling);
            }
            else if (heap[index].second->userPriority == heap[leftSibling].second->userPriority)
            {
                if (heap[index].second->complaintId < heap[leftSibling].second->complaintId)
                {
                    swap(heap[index], heap[leftSibling]);
                    HeapUp(leftSibling);
                }
            }
        }
        if (index == (parentIndex * 2 + 1))
        {
            int rightSibling = parentIndex * 2 + 2;
            if (rightSibling >= heap.size())
                return;
            if (heap[index].second->userPriority < heap[rightSibling].second->userPriority)
            {
                swap(heap[index], heap[rightSibling]);
                HeapUp(rightSibling);
            }
            else if (heap[index].second->userPriority == heap[rightSibling].second->userPriority)
            {
                if (heap[index].second->complaintId > heap[rightSibling].second->complaintId)
                {
                    swap(heap[index], heap[rightSibling]);
                    HeapUp(rightSibling);
                }
            }
            int PriorIndex = index - 1;
            if (PriorIndex < 0)
                return;
            if (heap[index].second->userPriority > heap[PriorIndex].second->userPriority)
            {
                swap(heap[index], heap[PriorIndex]);
                HeapUp(PriorIndex);
            }
            else if (heap[index].second->userPriority == heap[PriorIndex].second->userPriority)
            {
                if (heap[index].second->complaintId < heap[PriorIndex].second->complaintId)
                {
                    swap(heap[index], heap[PriorIndex]);
                    HeapUp(PriorIndex);
                }
            }
        }
    }
    void HeapDown(int index)
    {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largest = index;
        if (leftChild < heap.size() && heap[leftChild].second->userPriority > heap[largest].second->userPriority)
        {
            largest = leftChild;
        }
        if (rightChild < heap.size() && heap[rightChild].second->userPriority > heap[largest].second->userPriority)
        {
            largest = rightChild;
        }
        if (largest != index)
        {
            swap(heap[index], heap[largest]);
            HeapDown(largest);
        }
    }
    void RegisterComplaint(Complaint *c)
    {
        heap.push_back(make_pair(c->userId, c));
        HeapUp(heap.size() - 1);
    }
    void Print()
    {
        for (int i = 0; i < heap.size(); i++)
        {
            cout << "User id -> " << heap[i].first << endl;
            cout << "User Priority -> " << heap[i].second->userPriority << endl;
            cout << "Complaint Id -> " << heap[i].second->complaintId << endl;
            cout << "Complain -> " << heap[i].second->description << endl
                 << endl;
        }
    }
    void ServiceComplaint()
    {
        if (heap.empty())
            throw out_of_range("Heap is empty");
        heap[0] = heap.back();
        heap.pop_back();
        HeapDown(0);
        cout << "\nComplaint has been Serviced Successfully!" << endl;
    }
    void DisplayComplaintsByUserId(int id)
    {
        for (int i = 0; i < heap.size(); i++)
        {
            if (heap[i].second->userId == id)
            {
                cout << "User id -> " << heap[i].first << endl;
                cout << "User Priority -> " << heap[i].second->userPriority << endl;
                cout << "Complaint Id -> " << heap[i].second->complaintId << endl;
                cout << "Complain -> " << heap[i].second->description << endl
                     << endl;
            }
        }
    }
    void DisplayComplainsByCountry(node<User> **n, int count)
    {
        for (int i = 0; i < count; i++)
        {
            DisplayComplaintsByUserId(n[i]->data->userId);
        }
    }
    bool isEmpty()
    {
        return heap.empty();
    }
    int size()
    {
        return heap.size();
    }
};
