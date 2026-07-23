#include "AdjListGraph.hpp"
#include "ShortestPath.hpp"

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    AdjListGraph<int> graph;

    graph.addNode(0);
    graph.addNode(1);
    graph.addNode(2);
    graph.addNode(3);
    graph.addNode(4);

    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);

    ShortestPath<int> pathFinder;

    try
    {
        vector<int> path = pathFinder.shortestPath(graph, 0, 4);

        if (path.empty())
        {
            cout << "No Path Exists." << endl;
        }
        else
        {
            cout << "Shortest Path: ";

            for (int vertex : path)
            {
                cout << vertex << " ";
            }
            cout << endl;
        }
    }
    catch (const out_of_range& e)
    {
        cout << "Error: " << e.what() << endl;
    }

    cout << endl; return 0;
}