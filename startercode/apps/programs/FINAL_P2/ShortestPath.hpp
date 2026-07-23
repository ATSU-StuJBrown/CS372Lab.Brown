#include "Graph.hpp"
#include "Queue.hpp"

#pragma once

#include <map>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class ShortestPath
{
public:

    vector<int> shortestPath(Graph<T>& aGraph, int start, int destination) const
    {
        if (start < 0 || destination < 0)
        {
            throw out_of_range("Vertex out of range");
        }

        try
        {
            aGraph.neighbors(start);
            aGraph.neighbors(destination);
        }
        catch (const out_of_range&)
        {
            throw out_of_range("Vertex out of range");
        }

        if (start == destination)
        {
            return vector<int>{start};
        }

        map<int, bool> visited;
        map<int, int> predecessor;
        Queue<int> q;

        visited[start] = true;
        predecessor[start] = start;

        q.push(start);

        bool found = false;

        while (!q.empty())
        {
            int current = q.front();

            q.pop();

            vector<T> neighbors = aGraph.neighbors(current);

            for (T neighbor : neighbors)
            {
                int next = static_cast<int>(neighbor);

                if (!visited[next])
                {
                    visited[next] = true;
                    predecessor[next] = current;

                    if (next == destination)
                    {
                        found = true;
                        break;
                    }
                    q.push(next);
                }
            }

            if (found)
            {
                break;
            }
        }

        // No Path Found
        if (!found)
        {
            return vector<int>();
        }

        // Reconstruct Path
        vector<int> path;

        int current = destination;

        while (current != start)
        {
            path.push_back(current);
            current = predecessor[current];
        }
        path.push_back(start);

        // Reverse Path Order
        vector<int> result;

        for (int i = static_cast<int>(path.size()) - 1; i >= 0; i--)
        {
            result.push_back(path[i]);
        }
        return result;
    }
};