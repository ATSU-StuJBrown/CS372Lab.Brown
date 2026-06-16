#pragma once
#include "list.hpp"

template <typename Thing>
class Bag
{
private:
    List<Thing> data;

public:
    Bag()
    {
        // List is automatically constructed here?
    }

    void insert(Thing aThing)
    {
        data.push_back(aThing);
    }

    Thing pop()
    {
        Thing value = data.front();

        data.pop_front();

        return value;
    }

    int size()
    {
        int count = 0;

        data.traverse([&](Thing&)
        {
            count++;
        });

        return count;
    }

    int count()
    {
        return size();
    }
};