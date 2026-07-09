#pragma once
#include <iostream>
#include <utility>
using namespace std;

template<typename T>
class List
{
private:

    struct Node
    {
        T data;
        Node* next;

        Node(const T& value)
        {
            data = value;
            next = nullptr;
        }
    };

    Node* head;
    Node* tail;


    // Helper Funct
    void deleteListContents()
    {
        Node* current = head;

        while (current != nullptr)
        {
            Node* temp = current->next;
            delete current;
            current = temp;
        }

        head = nullptr;
        tail = nullptr;
    }


public:

    // Default Const
    List()
    {
        head = nullptr;
        tail = nullptr;
    }

    // Copy Const
    List(const List& rhs)
    {
        head = nullptr;
        tail = nullptr;

        Node* current = rhs.head;

        while (current != nullptr)
        {
            push_back(current->data);
            current = current->next;
        }
    }


    // Copy Asg Operator
    List& operator=(const List& rhs)
    {
        if (this != &rhs)
        {
            deleteListContents();

            Node* current = rhs.head;

            while (current != nullptr)
            {
                push_back(current->data);
                current = current->next;
            }
        }
        
        return *this;
    }


    // Move Const
    List(List&& rhs)
    {
        head = rhs.head;
        tail = rhs.tail;

        rhs.head = nullptr;
        rhs.tail = nullptr;
    }

    // Move Asg Operator
    List& operator=(List&& rhs)
    {
        if (this != &rhs)
        {
            deleteListContents();

            head = rhs.head;
            tail = rhs.tail;

            rhs.head = nullptr;
            rhs.tail = nullptr;
        }

        return *this;
    }

    // Destructor
    ~List()
    {
        deleteListContents();
    }

    //------------------------------------------------
    void push_back(const T& value)
    {
        Node* newNode = new Node(value);

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    //------------------------------------------------
    void clear()
    {
        deleteListContents();
    }

    //------------------------------------------------
    bool empty() const
    {
        return head == nullptr;
    }

    //------------------------------------------------
    void print() const
    {
        Node* current = head;

        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }

        cout << endl;
    }
};