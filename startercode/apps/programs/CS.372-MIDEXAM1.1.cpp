#include <functional>
using namespace std;

template <typename T>
class List
{
private:
    class Node
    {
    public:
        T data;
        Node* prev;
        Node* next;

        bool deleted = false;
    };

    Node* head = nullptr;
    Node* tail = nullptr;

    int count = 0;
    int delete_count = 0;

    void delete_all()
    {
        Node* curr = head;

        while (curr != nullptr)
        {
            Node* next = curr->next;

            if (curr->deleted)
            {
                if (curr->prev)
                {
                    curr->prev->next = curr->next;
                }
                else
                {
                    head = curr->next;
                }

                if (curr->next)
                {
                    curr->next->prev = curr->prev;
                }
                else
                {
                    tail = curr->prev;
                }

                delete curr;
                delete_count--;
            }

            curr = next;
        }
    }

public:
    void push_back(T value)
    {
        Node* n = new Node();

        n->data = value;
        n->prev = tail;

        if (tail)
        {
            tail->next = n;
        }
        else
        {
            head = n;
        }

        tail = n;
        count++;
    }

    // lazy delete front
    void pop_front()
    {
        Node* curr = head;

        while (curr && curr->deleted)
        {
            curr = curr->next;
        }

        if (!curr)
        {
            return;
        }

        curr->deleted = true;

        count--;
        delete_count++;

        if (head == curr)
        {
            head = curr->next;
        }

        if (delete_count == count)
        {
            delete_all();
        }
    }

    void traverse(function<void(T&)> f)
    {
        Node* curr = head;

        while (curr)
        {
            if (!curr->deleted)
            {
                f(curr->data);
            }

            curr = curr->next;
        }
    }
};