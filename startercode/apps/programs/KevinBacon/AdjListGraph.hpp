#include "Graph.hpp"

#pragma once

#include <map>
#include <list>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

template <class N>
class AdjListGraph : public Graph<N>
{
private:
    using Edge = pair<N,N>;
    using EdgeList = list<Edge>;

    map<N, EdgeList> vertexMap;

public:
    AdjListGraph() : Graph<N>() {}
    AdjListGraph(const AdjListGraph& other) : Graph<N>()
    {
        vertexMap = other.vertexMap;
    }

    AdjListGraph& operator=(const AdjListGraph& source)
    {
        vertexMap = source.vertexMap;
        return *this;
    }

    AdjListGraph(vector<N> newNodes, vector<Edge> newEdges) : Graph<N>(newNodes,newEdges)
    {
        for (const N& node : newNodes)
        {
            EdgeList edges;

            for (const Edge& e : newEdges)
            {
                if (e.first == node)
                {
                    edges.push_back(e);
                }
            }
            vertexMap[node] = edges;
        }
    }

    virtual ~AdjListGraph() = default;

    bool adjacent(N x, N y) const override
    {
        EdgeList edges = vertexMap.at(x);

        Edge search{x,y};

        for (const Edge& e : edges)
        {
            if (e.first == search.first && e.second == search.second)
            {
                return true;
            }
        }
        return false;
    }

    vector<N> neighbors(N x) const override
    {
        vector<N> nodes;

        for (const auto& edge : vertexMap.at(x))
        {
            nodes.push_back(edge.second);
        }
        return nodes;
    }

    void addNode(N node) override
    {
        EdgeList empty;

        vertexMap[node] = empty;
    }

    void addEdge(N x, N y) override
    {
        Edge newEdge{x,y};

        vertexMap[x].push_back(newEdge);
    }

    void deleteEdge(N x, N y) override
    {
        Edge remove{x,y};

        vertexMap[x].remove(remove);
    }

    map<N,N> dfs(N startNode, function<void(N)> visit) override
    {
        map<N,bool> visited;
        map<N,N> parents;

        for (auto node : vertexMap)
        {
            visited[node.first] = false;
        }

        stack<N> s;

        s.push(startNode);

        parents[startNode] = startNode;
        visited[startNode] = true;

        while (!s.empty())
        {
            N current = s.top();
            s.pop();

            visit(current);

            for (N neighbor : neighbors(current))
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    parents[neighbor] = current;

                    s.push(neighbor);
                }
            }
        }
        return parents;
    }

    map<N,N> bfs(N startNode, function<void(N)> visit) override
    {
        map<N,bool> visited;
        map<N,N> parents;

        for (auto node : vertexMap)
        {
            visited[node.first] = false;
        }

        queue<N> q;

        q.push(startNode);

        visited[startNode] = true;
        parents[startNode] = startNode;

        while (!q.empty())
        {
            N current = q.front();
            q.pop();

            visit(current);

            for (N neighbor : neighbors(current))
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    parents[neighbor] = current;

                    q.push(neighbor);
                }
            }
        }
        return parents;
    }
};