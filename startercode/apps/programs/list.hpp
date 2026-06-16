#pragma once
#include <functional>

template <typename T>
class List
{
private:
    struct Node
    {
        T data;
        Node* prev;
        Node* next;
    };

    Node* head;
    Node* tail;

    void deleteListContents()
    {
        Node* current = head;
        Node* temp = nullptr;

        while (current != nullptr)
        {
            temp = current->next;

            delete current;

            current = temp;
        }

        head = nullptr;
        tail = nullptr;
    }

    void copyFrom(const List& rhs)
    {
        Node* current = rhs.head;

        while (current != nullptr)
        {
            push_back(current->data);

            current = current->next;
        }
    }

public:
    List()
    {
        head = nullptr;
        tail = nullptr;
    }

    List(T newData)
    {
        head = nullptr;
        tail = nullptr;

        push_back(newData);
    }

    // COPY constructor
    List(const List& rhs)
    {
        head = nullptr;
        tail = nullptr;

        copyFrom(rhs);
    }

    // MOVE constructor
    List(List& rhs)
    {
        head = rhs.head;
        tail = rhs.tail;

        rhs.head = nullptr;
        rhs.tail = nullptr;
    }

    // COPY assignment
    List& operator=(const List& rhs)
    {
        if (this != &rhs)
        {
            deleteListContents();
            copyFrom(rhs);
        }
        return *this;
    }

    // MOVE assignment
    List& operator=(List& rhs)
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

    ~List()
    {
        deleteListContents();
    }

    bool empty()
    {
        return head == nullptr;
    }

    void push_front(T data)
    {
        Node* newNode = new Node;

        newNode->data = data;
        newNode->prev = nullptr;
        newNode->next = head;

        if (head != nullptr)
        {
            head->prev = newNode;
        }
        else
        {
            tail = newNode;
        }

        head = newNode;
    }

    void push_back(T data)
    {
        Node* newNode = new Node;

        newNode->data = data;
        newNode->next = nullptr;
        newNode->prev = tail;

        if (tail != nullptr)
        {
            tail->next = newNode;
        }
        else
        {
            head = newNode;
        }

        tail = newNode;
    }

    T front()
    {
        return head->data;
    }

    T back()
    {
        return tail->data;
    }

    void pop_front()
    {
        if (head == nullptr)
        {
            return;
        }

        Node* temp = head;
        head = head->next;

        if (head != nullptr)
        {
            head->prev = nullptr;
        }
        else
        {
            tail = nullptr;
        }

        delete temp;
    }

    void pop_back()
    {
        if (tail == nullptr)
        {
            return;
        }
        
        Node* temp = tail;
        tail = tail->prev;
        

        if (tail != nullptr)
        {
            tail->next = nullptr;
        }
        else
        {
            head = nullptr;
        }

        delete temp;
    }

    void traverse(std::function<void(T&)> doIt)
    {
        Node* current = head;

        while (current != nullptr)
        {
            doIt(current->data);

            current = current->next;
        }
    }
};