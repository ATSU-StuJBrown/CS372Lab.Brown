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
    using Edge = pair<N, N>;
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

    AdjListGraph(vector<N> newNodes, vector<Edge> newEdgeVec) : Graph<N>(newNodes, newEdgeVec)
    {
        for (const N& node : newNodes)
        {
            EdgeList nodeEdges;

            for (const Edge& e : newEdgeVec)
            {
                if (e.first == node)
                {
                    nodeEdges.push_back(e);
                }
            }
            vertexMap[node] = nodeEdges;
        }
    }

    ~AdjListGraph() = default;

    bool adjacent(N x, N y) const override
    {
        EdgeList edges = vertexMap.at(x);
        Edge searchEdge{x, y};

        auto pos = find_if(edges.begin(), edges.end(), [&](Edge const& b) {return (b.first == searchEdge.first && b.second == searchEdge.second);});
        return pos != edges.end();
    }

    vector<N> neighbors(N x) const override
    {
        vector<N> nodes;

        for (const auto& e : vertexMap.at(x))
        {
            nodes.push_back(e.second);
        }
        return nodes;
    }

    void addNode(N node) override
    {
        EdgeList newEdgeList{};
        vertexMap[node] = newEdgeList;
    }
    void addEdge(N x, N y) override
    {
        Edge forwardEdge{x, y};
        vertexMap[x].push_back(forwardEdge);
    }
    void deleteEdge(N x, N y) override
    {
        Edge forwardEdge{x, y};
        vertexMap[x].remove(forwardEdge);
    }

    map<N, N> dfs(N startNode, function<void(N)> visit) override
    {
        map<N, bool> visited;
        map<N, N> parents;
        stack<N> s;

        for (auto v : vertexMap)
        {
            visited[v.first] = false;
        }

        s.push(startNode);
        parents[startNode] = startNode;

        while (!s.empty())
        {
            N currentNode = s.top();
            s.pop();

            if (!visited[currentNode])
            {
                visit(currentNode);
                visited[currentNode] = true;
            }

            vector<N> neighVec = neighbors(currentNode);

            for (auto neighbor : neighVec)
            {
                if (!visited[neighbor])
                {
                    parents[neighbor] = currentNode;
                    s.push(neighbor);
                }
            }
        }
        return parents;
    }

    map<N, N> bfs(N startNode, function<void(N)> visit) override
    {
        map<N, bool> visited;
        map<N, N> parents;
        queue<N> q;

        for (auto v : vertexMap)
        {
            visited[v.first] = false;
        }

        q.push(startNode);
        parents[startNode] = startNode;

        while (!q.empty())
        {
            N currentNode = q.front();
            q.pop();

            if (!visited[currentNode])
            {
                visit(currentNode);
                visited[currentNode] = true;
            }

            vector<N> neighVec = neighbors(currentNode);

            for (auto neighbor : neighVec)
            {
                if (!visited[neighbor])
                {
                    parents[neighbor] = currentNode;
                    q.push(neighbor);
                }
            }
        }
        return parents;
    }
};