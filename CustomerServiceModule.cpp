#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include "AVLTree.cpp"
#include "AVLGroupTree.cpp"
#include "User.cpp"
#include "PriorityQueue.cpp"
#include "HashTable_str.cpp"
#include "HashTable_int.cpp"
#include "HashTable_count.cpp"
#include "HashTable_type.cpp"
using namespace std;
class CustomerServiceModule
{
private:
    DLL<User> userList;
    AVL<int> UserIds;
    AVL<string> UserNames;
    AVL<string> UserEmails;
    AVLGroupTree<string> UserCountries;
    AVLGroupTree<string> UserTypes;
    PriorityQueue complains;

    HashTable_int UserIdHashing;
    HashTable UserNamesHashing;
    HashTable UserEmailHashing;
    HashTable_count UserCountryHashing;
    HashTable_type UserTypeHashing;

public:
    CustomerServiceModule()
    {
        int a = 31;
        UserNamesHashing.SetSize(a);
        UserEmailHashing.SetSize(a);
        UserIdHashing.SetSize(a);
        UserCountryHashing.SetSize(a);
        UserTypeHashing.SetSize(a);
    }
    void InsertUser(User *u)
    {
        node<User> *temp = new node<User>(u);
        node<User> *parent = 0;
        UserIds.Insert(u->userId, temp);
        UserNames.Insert(u->GetUserName(), temp);

        UserNamesHashing.Insert(u->GetUserName(), u->userId, u);
        UserEmailHashing.Insert(u->GetEmail(), u->userId, u);
        UserIdHashing.Insert(u->userId, u);
        UserCountryHashing.Insert(u->GetCountry(), u);
        UserTypeHashing.Insert(u->GetType(), u);

        UserEmails.Insert(u->GetEmail(), temp);
        UserCountries.Insert(u->GetCountry(), temp);
        UserTypes.Insert(u->GetType(), temp);
        parent = UserIds.FindParent(u->userId);
        if (!parent)
        {
            userList.AddToEnd(temp);
        }
        else if (temp->data->userId > parent->data->userId)
        {
            userList.InsertAfter(parent, temp);
        }
        else
        {
            userList.InsertBefore(parent, temp);
        }
    }
    // hash searching
    void SearchUserByName(string name)
    {
        User *temp = UserNamesHashing.Search(name);
        if (!temp)
        {
            cerr << "User Does not exist!" << endl;
        }
        else
        {
            cout << "User found with name -> " << temp->GetUserName() << endl;
            temp->print();
        }
    }
    void SearchUserByEmail(string email)
    {
        User *temp = UserEmailHashing.Search(email);
        if (!temp)
        {
            cerr << "User Does not exist!" << endl;
        }
        else
        {
            cout << "User found with email -> " << temp->GetEmail() << endl;
            temp->print();
        }
    }
    // trees searching
    void SearchUserByID(int id)
    {
        User *temp = UserIdHashing.Search(id);
        if (!temp)
        {
            cerr << "User Does not exist!" << endl;
        }
        else
        {
            cout << "User found with id -> " << temp->userId << endl;
            temp->print();
        }
    }
    void SearchUserByCountry(string Country)
    {
        UserCountryHashing.Search(Country);
    }
    void SearchUserByType(string Type)
    {
        UserTypeHashing.Search(Type);
    }
    void Print()
    {
        userList.Print();
    }
    void PrintIdTree()
    {
        UserIds.InOrderPrinting();
    }
    void PrintNameTree()
    {
        UserNames.InOrderPrinting();
    }
    void PrintCountryTree()
    {
        UserCountries.InOrderPrinting();
    }
    void PrintEmailTree()
    {
        UserEmails.InOrderPrinting();
    }
    void PrintTypeTree()
    {
        UserTypes.InOrderPrinting();
    }
    void DeleteUserById(int id)
    {
        node<User> *temp = UserIds.Search(id);
        if (!temp)
        {
            cerr << "\nUser does not exist!" << endl;
        }
        else
        {
            cout << "\nUser with id -> " << temp->data->userId << " Deleted!" << endl;
            userList.DeleteNode(temp);
            UserIds.Delete(id);
            UserIdHashing.Delete(id);
        }
    }
    void DeleteUserByName(string name)
    {
        node<User> *temp = UserNames.Search(name);
        if (!temp)
        {
            cerr << "\nUser does not exist!" << endl;
        }
        else
        {
            cout << "\nUser with id -> " << temp->data->GetUserName() << " Deleted!" << endl;
            userList.DeleteNode(temp);
            UserNames.Delete(name);
            UserNamesHashing.Delete(name);
        }
    }
    void DeleteUserByEmail(string email)
    {
        node<User> *temp = UserEmails.Search(email);
        if (!temp)
        {
            cerr << "\nUser does not exist!" << endl;
        }
        else
        {
            cout << "\nUser with id -> " << temp->data->GetEmail() << " Deleted!" << endl;
            userList.DeleteNode(temp);
            UserEmails.Delete(email);
        }
    }
    void DeleteUserByCountry(string country)
    {
        node<User> **temp = UserCountries.FindNode(country);
        if (!temp)
        {
            cerr << "\nUser does not exist" << endl;
        }
        else
        {
            int count = UserCountries.GetCurrentIndex(country);
            for (int i = 0; i < count; i++)
            {
                userList.DeleteNode(temp[i]);
            }
            UserCountries.Delete(country);
            UserCountryHashing.Delete(country);
        }
    }
    void DeleteUserByType(string Type)
    {
        node<User> **temp = UserTypes.FindNode(Type);
        if (!temp)
        {
            cerr << "\nUser does not exist" << endl;
        }
        else
        {
            int count = UserTypes.GetCurrentIndex(Type);
            for (int i = 0; i < count; i++)
            {
                userList.DeleteNode(temp[i]);
            }
            UserTypes.Delete(Type);
            UserTypeHashing.Delete(Type);
        }
    }

    void AddUser()
    {
        int id;
        string name, email, country, type;
        cout << "Enter ID -> ";
        cin >> id;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cerr << "Enter a valid ID -> ";
            cin >> id;
        }
        cout << "Enter Name -> ";
        cin.clear();
        cin.ignore();
        getline(cin, name);
        cout << "Enter Email -> ";
        cin >> email;
        cout << "Enter Country -> ";
        cin >> country;
        cout << "Enter Type -> ";
        cin >> type;
        User *u = new User(id, name, email, country, type);
        InsertUser(u);
    }
    void ServiceComplaint()
    {
        complains.ServiceComplaint();
    }
    void PrintMenu()
    {
        HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
        cout << "\n\t\t\t--> Welcome to Customer Service Module <--" << endl;
        cout << "\nMenu\n";
        cout << "1.  Insert User" << endl;
        SetConsoleTextAttribute(hc, 0x03);
        cout << "2.  Print all users" << endl;
        cout << "3.  Print ID Tree" << endl;
        cout << "4.  Print Name Tree" << endl;
        cout << "5.  Print Email Tree" << endl;
        cout << "6.  Print Country Tree" << endl;
        cout << "7.  Print Type Tree" << endl;
        SetConsoleTextAttribute(hc, 0x0A);
        cout << "8.  Search user by ID" << endl;
        cout << "9.  Search user by Name" << endl;
        cout << "10. Search user by Email" << endl;
        cout << "11. Search user by Country" << endl;
        cout << "12. Search user by Type" << endl;
        SetConsoleTextAttribute(hc, 0x04);
        cout << "13. Delete user by ID" << endl;
        cout << "14. Delete user by Name" << endl;
        cout << "15. Delete user by Email" << endl;
        cout << "16. Delete users by Country" << endl;
        cout << "17. Delete users by Type" << endl;
        SetConsoleTextAttribute(hc, 0x0E);
        cout << "18. Print Complains" << endl;
        cout << "19. Service Complaint" << endl;
        cout << "20. Complains By User Id" << endl;
        cout << "21. Complains By User Countries" << endl;
        SetConsoleTextAttribute(hc, 0x07);
        cout << "22. Exit" << endl;
    }
    void PrintComplains()
    {
        complains.Print();
    }
    void DisplayComplaintsByUserId(int id)
    {
        complains.DisplayComplaintsByUserId(id);
    }
    void DisplayComplaintsByUserCountry(string country)
    {
        node<User> **temp = UserCountries.FindNode(country);
        if (!temp)
        {
            cerr << "\nUser does not exist" << endl;
        }
        else
        {
            int count = UserCountries.GetCurrentIndex(country);
            complains.DisplayComplainsByCountry(temp, count);
        }
    }
    void run()
    {
        // test Inputs
        User *u1 = new User(57, "Aisha Khan", "aisha.khan@gmail.com", "Pakistan", "Gold");
        User *u2 = new User(23, "Raj Patel", "raj.patel@yahoo.com", "India", "Silver");
        User *u3 = new User(85, "Emily Chen", "emily.chen@hotmail.com", "Mexico", "Platinum");
        User *u4 = new User(41, "John Smith", "john.smith@outlook.com", "UK", "Silver");
        User *u5 = new User(76, "Fatima Ali", "fatima.ali@gmail.com", "Egypt", "Gold");
        User *u6 = new User(10, "Carlos Gomez", "carlos.gomez@yahoo.com", "Mexico", "Regular");
        User *u7 = new User(92, "Sara Johnson", "sara.johnson@hotmail.com", "UK", "Platinum");
        User *u8 = new User(34, "Omar Farooq", "omar.farooq@outlook.com", "Pakistan", "New");
        User *u9 = new User(68, "Nina Patel", "nina.patel@gmail.com", "Australia", "Regular");
        User *u10 = new User(49, "Liam Brown", "liam.brown@yahoo.com", "UK", "New");
        Complaint c1(u1->userId, u1->GetPriority(), "Bijli ni Andi");
        Complaint c2(u2->userId, u2->GetPriority(), "Asy bay k sy ba.....che");
        Complaint c3(u3->userId, u3->GetPriority(), "What the hell is this service");
        Complaint c4(u4->userId, u4->GetPriority(), "Hello 911");
        Complaint c5(u5->userId, u5->GetPriority(), "Hello I am under the water, please help me");
        Complaint c6(u6->userId, u6->GetPriority(), "This is shitty service");
        Complaint c7(u7->userId, u7->GetPriority(), "Flex chala do bhai");
        Complaint c8(u8->userId, u8->GetPriority(), "Men watta chuk k marna");
        Complaint c9(u9->userId, u9->GetPriority(), "Baba sain kam nai karna to bta do humain");
        Complaint c10(u10->userId, u10->GetPriority(), "Mobile Nikal");
        this->InsertUser(u1);
        this->InsertUser(u2);
        this->InsertUser(u3);
        this->InsertUser(u4);
        this->InsertUser(u5);
        this->InsertUser(u6);
        this->InsertUser(u7);
        this->InsertUser(u8);
        this->InsertUser(u9);
        this->InsertUser(u10);
        complains.RegisterComplaint(&c1);
        complains.RegisterComplaint(&c2);
        complains.RegisterComplaint(&c3);
        complains.RegisterComplaint(&c4);
        complains.RegisterComplaint(&c5);
        complains.RegisterComplaint(&c6);
        complains.RegisterComplaint(&c7);
        complains.RegisterComplaint(&c8);
        complains.RegisterComplaint(&c9);
        complains.RegisterComplaint(&c10);
        int choice;
        string stringBuffer;
        int intBuffer;
        while (true)
        {
            PrintMenu();
            cout << "\nEnter Choice -> ";
            cin >> choice;
            cout << endl;
            while (cin.fail())
            {
                cin.clear();
                cin.ignore();
                cerr << "\nEnter a valid Command -> ";
                cin >> choice;
            }
            switch (choice)
            {
            case 1:
                AddUser();
                break;
            case 2:
                Print();
                break;
            case 3:
                PrintIdTree();
                break;
            case 4:
                PrintNameTree();
                break;
            case 5:
                PrintEmailTree();
                break;
            case 6:
                PrintCountryTree();
                break;
            case 7:
                PrintTypeTree();
                break;
            case 8:
                cout << "Enter ID -> ";
                cin >> intBuffer;
                while (cin.fail())
                {
                    cin.clear();
                    cin.ignore();
                    cerr << "Enter a valid ID -> ";
                    cin >> intBuffer;
                }
                SearchUserByID(intBuffer);
                break;
            case 9:
                cout << "Enter full name -> ";
                cin.clear();
                cin.ignore();
                getline(cin, stringBuffer);
                SearchUserByName(stringBuffer);
                break;
            case 10:
                cout << "Enter email  -> ";
                cin >> stringBuffer;
                SearchUserByEmail(stringBuffer);
                break;
            case 11:
                cout << "Enter country  -> ";
                cin >> stringBuffer;
                SearchUserByCountry(stringBuffer);
                break;
            case 12:
                cout << "Enter type -> ";
                cin >> stringBuffer;
                SearchUserByType(stringBuffer);
                break;
            case 13:
                cout << "Enter User ID -> ";
                cin >> intBuffer;
                DeleteUserById(intBuffer);
                break;
            case 14:
                cout << "Enter User Name -> ";
                cin.clear();
                cin.ignore();
                getline(cin, stringBuffer);
                DeleteUserByName(stringBuffer);
                break;
            case 15:
                cout << "Enter User Email -> ";
                cin >> stringBuffer;
                DeleteUserByEmail(stringBuffer);
                break;
            case 16:
                cout << "Enter Country -> ";
                cin >> stringBuffer;
                DeleteUserByCountry(stringBuffer);
                break;
            case 17:
                cout << "Enter Type -> ";
                cin >> stringBuffer;
                DeleteUserByType(stringBuffer);
                break;
            case 18:
                PrintComplains();
                break;
            case 19:
                ServiceComplaint();
                break;
            case 20:
                cout << "Enter User Id -> ";
                cin >> intBuffer;
                while (cin.fail())
                {
                    cin.clear();
                    cin.ignore();
                    cerr << "Enter a valid Id -> ";
                    cin >> intBuffer;
                }
                DisplayComplaintsByUserId(intBuffer);
                break;
            case 21:
                cout << "Enter Country -> ";
                cin >> stringBuffer;
                DisplayComplaintsByUserCountry(stringBuffer);
                break;
            case 22:
                char ans;
                cout << "Are you sure you want to exit? (y/n) -> ";
                ans = getch();
                if (ans == 'y')
                {
                    cout << "\nExiting..." << endl;
                    exit(0);
                }
                cout << endl;
                break;
            default:
                cerr << "Please make a valid choice!" << endl;
                break;
            }
        }
    }
};