#include <iostream>
#include <iomanip>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;

template <typename T>
class Vector
{
protected:
    T* arr;
    int vCapacity;
    int length;

    virtual void expand(int newCapacity)
    {
        if (newCapacity > vCapacity)
        {
            T* temp = new T[newCapacity];

            for (int i = 0; i < length; i++)
            {
                temp[i] = arr[i];
            }

            delete[] arr;

            arr = temp;
            vCapacity = newCapacity;
        }
    }

public:
    Vector()
    {
        arr = new T[1];
        vCapacity = 1;
        length = 0;
    }

    virtual ~Vector()
    {
        delete[] arr;
    }

    virtual void push_back(T data)
    {
        if (length == vCapacity)
        {
            expand(2 * vCapacity);
        }

        arr[length] = data;

        length++;
    }

    class iterator
    {
    private:
        T* pointer;
        int index;

    public:
        iterator(T* p = nullptr, int i = 0)
        {
            pointer = p;
            index = i;
        }

        T& operator*()
        {
            return pointer[index];
        }

        iterator& operator++()
        {
            index++;

            return *this;
        }

        bool operator==(const iterator& rhs) const
        {
            return pointer == rhs.pointer && index == rhs.index;
        }

        bool operator!=(const iterator& rhs) const
        {
            return !(*this == rhs);
        }
    };

    iterator begin()
    {
        return iterator(arr, 0);
    }

    iterator end()
    {
        return iterator(arr, length);
    }
};