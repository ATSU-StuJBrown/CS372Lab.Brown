#pragma once

#include <map>
#include <vector>
#include <utility>
#include <functional>

using namespace std;

template <class N>
class Graph
{
public:
    using Edge = pair<N, N>;

    Graph() = default;
    Graph(vector<N> nodes, vector<Edge> edges) {};

    virtual ~Graph() = default;

    virtual bool adjacent(N x, N y) const = 0;

    virtual vector<N> neighbors(N x) const = 0;

    virtual void addNode(N x) = 0;
    virtual void addEdge(N x, N y) = 0;
    virtual void deleteEdge(N x, N y) = 0;

    // Depth-first Search Traversal
    virtual map<N, N> dfs (N startNode, function<void(N)> visit) = 0;
    // Breadth-first Search Traversal
    virtual map<N, N> bfs (N startNode, function<void(N)> visit) = 0;
};