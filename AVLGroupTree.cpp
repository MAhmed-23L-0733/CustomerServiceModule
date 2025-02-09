#pragma once
#include <iostream>
#include "DLL.cpp"
#include "User.cpp"
using namespace std;
template <class T>
class AVLGroupTree
{
private:
    struct AVLNode
    {
        T data;
        int height;
        AVLNode *left;
        AVLNode *right;
        node<User> **userPtr;
        int currIndex;

        AVLNode()
        {
            data = 0;
            height = 0;
            left = 0;
            right = 0;
            userPtr = 0;
            currIndex = 0;
        }
        AVLNode(T val)
        {
            data = val;
            height = 0;
            left = 0;
            right = 0;
            userPtr = 0;
            currIndex = 0;
        }
        void InsertNode(node<User> *n)
        {
            node<User> **temp = new node<User> *[currIndex + 1];
            int i = 0;
            for (i = 0; i < currIndex; i++)
            {
                temp[i] = userPtr[i];
            }
            temp[i] = n;
            userPtr = temp;
            currIndex++;
        }
        void PrintUsers()
        {
            if (userPtr[0] == 0)
            {
                return;
            }
            for (int i = 0; i < currIndex; i++)
            {
                userPtr[i]->data->print();
            }
        }
    };
    AVLNode *root;

public:
    void PrintUsers(T val)
    {
        AVLNode *temp = Search(val);
        if (!temp)
        {
            cerr << "User not found!" << endl;
        }
        else
        {
            temp->PrintUsers();
        }
    }
    AVLGroupTree()
    {
        root = nullptr;
    }
    int CalculateHeight()
    {
        return CalculateHeight(root);
    }
    int CalculateHeight(AVLNode *temp)
    {
        if (temp == nullptr)
        {
            return -1;
        }
        int leftHeight = CalculateHeight(temp->left);
        int rightHeight = CalculateHeight(temp->right);
        return 1 + max(leftHeight, rightHeight);
    }
    void RRotate() // ll rotation
    {
        RRotate(root);
    }
    void RRotate(AVLNode *&x)
    {
        AVLNode *orphan = x->left->right;
        AVLNode *y = x->left;
        y->right = x;
        x->left = orphan;
        x->height = CalculateHeight(x);
        y->height = CalculateHeight(y);
        x = y;
    }
    void LRotate()
    {
        LRotate(root);
    }
    void LRotate(AVLNode *&x)
    {
        AVLNode *orphan = x->right->left;
        AVLNode *y = x->right;
        y->left = x;
        x->right = orphan;
        x->height = CalculateHeight(x);
        y->height = CalculateHeight(y);
        x = y;
    }
    void DoubleLRRotate()
    {
        DoubleLRRotate(root);
    }
    void DoubleLRRotate(AVLNode *x)
    {
        LRotate(x->left);
        RRotate(x);
    }
    void DoubleRLRotate()
    {
        DoubleRLRotate(root);
    }
    void DoubleRLRotate(AVLNode *x)
    {
        RRotate(x->right);
        LRotate(x);
    }
    void Insert(T val, node<User> *n = 0)
    {
        if (IsInTree(val))
        {
            AVLNode *temp = Search(val);
            temp->InsertNode(n);
        }
        else
            return Insert(root, val, n);
    }
    void Insert(AVLNode *&temp, T val, node<User> *n)
    {
        if (temp == nullptr)
        {
            temp = new AVLNode(val);
            temp->InsertNode(n);
        }
        else if (temp->data > val)
        {
            Insert(temp->left, val, n);
        }
        else
        {
            Insert(temp->right, val, n);
        }
        BalanceNode(temp);
    }
    void BalanceNode(AVLNode *&x)
    {
        if (!x)
        {
            return;
        }
        if (CalculateHeight(x->left) - CalculateHeight(x->right) > 1)
        {
            if (CalculateHeight(x->left->left) >= CalculateHeight(x->left->right))
            {
                RRotate(x);
            }
            else
            {
                LRotate(x->left);
                RRotate(x);
            }
        }
        else if (CalculateHeight(x->right) - CalculateHeight(x->left) > 1)
        {
            if (CalculateHeight(x->right->right) >= CalculateHeight(x->right->left))
            {
                LRotate(x);
            }
            else
            {
                RRotate(x->right);
                LRotate(x);
            }
        }
        x->height = 1 + max(CalculateHeight(x->left), CalculateHeight(x->right));
    }
    void Delete(T val)
    {
        return Delete(root, val);
    }
    void Delete(AVLNode *&temp, T val)
    {
        if (temp == nullptr)
        {
            return;
        }
        if (temp->data > val)
        {
            Delete(temp->left, val);
        }
        else if (temp->data < val)
        {
            Delete(temp->right, val);
        }
        else if (temp->right != nullptr && temp->left != nullptr)
        {
            AVLNode *current = temp->left;
            while (current->right != nullptr)
            {
                current = current->right;
            }
            temp->data = current->data;
            Delete(temp->left, current->data);
        }
        else
        {
            AVLNode *oldnode = temp;
            if (temp->left != nullptr)
            {
                temp = temp->left;
            }
            else if (temp->right != nullptr)
            {
                temp = temp->right;
            }
            else
            {
                temp = nullptr;
            }
            delete oldnode;
        }
        BalanceNode(temp);
    }
    void InOrderPrinting()
    {
        return InOrderPrinting(root);
    }
    void InOrderPrinting(AVLNode *temp)
    {
        if (temp)
        {
            InOrderPrinting(temp->left);
            temp->PrintUsers();
            InOrderPrinting(temp->right);
        }
    }
    bool IsInTree(T val)
    {
        return IsInTree(root, val);
    }
    bool IsInTree(AVLNode *&temp, T val)
    {
        if (temp == nullptr)
        {
            return false;
        }
        if (temp->data == val)
        {
            return true;
        }
        return IsInTree(temp->left, val) || IsInTree(temp->right, val);
    }
    AVLNode *Search(T val, node<User> *n = 0)
    {
        return Search(root, val, n);
    }
    AVLNode *Search(AVLNode *&temp, T val, node<User> *n)
    {
        if (temp)
        {
            if (temp->data == val)
            {
                return temp;
            }
            else if (temp->data > val)
            {
                return Search(temp->left, val, n);
            }
            else
            {
                return Search(temp->right, val, n);
            }
        }
        else
        {
            return 0;
        }
    }
    node<User> **FindNode(T val, node<User> *n = 0)
    {
        return FindNode(root, val, n);
    }
    node<User> **FindNode(AVLNode *&temp, T val, node<User> *n)
    {
        if (temp)
        {
            if (temp->data == val)
            {
                return temp->userPtr;
            }
            else if (temp->data > val)
            {
                return FindNode(temp->left, val, n);
            }
            else
            {
                return FindNode(temp->right, val, n);
            }
        }
        else
        {
            return 0;
        }
    }
    int GetCurrentIndex(T val)
    {
        AVLNode *temp = Search(val);
        return temp->currIndex;
    }
    node<User> *FindParent(T key)
    {
        return FindParent(root, key);
    }
    node<User> *FindParent(AVLNode *&temp, T key)
    {
        if (temp == nullptr || temp->data == key)
        {
            return nullptr;
        }
        if ((temp->left && temp->left->data == key) || (temp->right && temp->right->data == key))
        {
            return temp->userPtr;
        }
        if (key < temp->data)
        {
            return FindParent(temp->left, key);
        }
        else
        {
            return FindParent(temp->right, key);
        }
    }
};