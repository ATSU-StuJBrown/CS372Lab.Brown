#pragma once
#include "list.hpp"
#include <functional>

template <typename T>
class CircularList : public List<T>
{
public:
    using List<T>::List;

    void traverseCircular(std::function<void(T&)> doIt, int start = 0)
    {
        T* arr[1000];

        int count = 0;

        this->traverse([&](T& data)
        {
            arr[count++] = &data;
        });

        if (count == 0)
        {
            return;
        }

        int index = start % count;

        for (int i = 0; i < count; i++)
        {
            doIt(*arr[index]);
            
            index = (index + 1) % count;
        }
    }
};