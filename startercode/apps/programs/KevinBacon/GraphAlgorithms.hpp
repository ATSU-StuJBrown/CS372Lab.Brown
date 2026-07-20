#include "Graph.hpp"

#pragma once

#include <iostream>
#include <map>
#include <set>
#include <list>
#include <queue>
#include <string>
#include <vector>
#include <functional>

using namespace std;

template <class N>
bool isSimpleCycle(Graph<N>& g, const vector<N>& path)
{
    if (path.size() < 3)
    {
        return false;
    }

    if (path.front() != path.back())
    {
        return false;
    }

    set<N> visited;

    for (size_t i = 0; i < path.size() - 1; i++)
    {
        if (!g.adjacent(path[i], path[i + 1]))
        {
            return false;
        }

        if (i != path.size() - 1)
        {
            if (visited.count(path[i]))
            {
                return false;
            }

            visited.insert(path[i]);
        }
    }
    return true;
}

template <class N>
bool findKevinBacon(Graph<N>& g, const N& me, const N& kevin, list<N>& path)
{
    path.clear();

    auto visit = [](N)
    {
        // ...
    };

    map<N,N> parents = g.bfs(me, visit);

    if (parents.find(kevin) == parents.end())
    {
        return false;
    }

    N current = kevin;

    while (current != me)
    {
        path.push_front(current);
        current = parents[current];
    }

    path.push_front(me);

    return true;
}