#include "GraphAlgorithms.hpp"
#include "AdjListGraph.hpp"
#include "AdjMatrixGraph.hpp"

#include <gtest/gtest.h>

#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

class GraphTest : public ::testing::Test
{
protected:
    AdjListGraph<int> testALG;
    AdjMatrixGraph<int> testAMG;

    void SetUp() override
    {
        for (int i = 0; i < 4; i++)
        {
            testALG.addNode(i);
            testAMG.addNode(i);
        }

        vector<pair<int,int>> edges =
        {
            {0,1},{0,2},{0,3},
            {1,0},{1,2},{1,3},
            {2,0},{2,1},{2,3},
            {3,0},{3,1},{3,2}
        };

        for (auto edge : edges)
        {
            testALG.addEdge(edge.first, edge.second);
            testAMG.addEdge(edge.first, edge.second);
        }

    }

};

TEST_F(GraphTest, BuildAL)
{
    EXPECT_TRUE(testALG.adjacent(0,1));
    EXPECT_TRUE(testALG.adjacent(2,3));
}

TEST_F(GraphTest, BuildAM)
{
    EXPECT_TRUE(testAMG.adjacent(0,1));
    EXPECT_TRUE(testAMG.adjacent(2,3));
}

TEST_F(GraphTest, NeighborsAL)
{
    vector<int> expected = {1,2,3};

    EXPECT_EQ(testALG.neighbors(0), expected);
}

TEST_F(GraphTest, NeighborsAM)
{
    vector<int> expected = {1,2,3};

    EXPECT_EQ(testAMG.neighbors(0), expected);
}

TEST_F(GraphTest, DFS)
{
    auto visit = [](int n)
    {
        cout << n << " ";
    };

    auto result = testALG.dfs(0,visit);

    EXPECT_TRUE(result.find(3) != result.end());
}

TEST_F(GraphTest, BFS)
{
    auto visit = [](int n)
    {
        cout << n << " ";
    };

    auto result = testALG.bfs(0,visit);

    EXPECT_TRUE(result.find(3) != result.end());
}

class PathTest : public ::testing::Test
{
protected:
    AdjListGraph<int> graph;

    void SetUp() override
    {
        for(int i = 0; i < 4; i++)
        {
            graph.addNode(i);
        }

        graph.addEdge(0,1);
        graph.addEdge(1,2);
        graph.addEdge(2,0);

        graph.addEdge(0,3);
        graph.addEdge(3,0);
    }
};

bool isValidTour(vector<int> path, Graph<int>& g)
{
    if(path.front() != path.back())
    {
        return false;
    }

    for(size_t i = 0; i < path.size()-1; i++)
    {
        if(!g.adjacent(path[i],path[i+1]))
        {
            return false;
        }
    }
    return true;
}

TEST_F(PathTest, ValidPath)
{
    vector<int> path = {0,1,2,0};

    EXPECT_TRUE(isValidTour(path,graph));
}

class CycleTest : public ::testing::Test
{
protected:
    AdjListGraph<int> graph;

    void SetUp() override
    {
        for(int i = 0; i < 4; i++)
        {
            graph.addNode(i);
        }

        graph.addEdge(0,1);
        graph.addEdge(1,2);
        graph.addEdge(2,0);

        graph.addEdge(0,3);
        graph.addEdge(3,0);
    }
};

TEST_F(CycleTest, ValidSimpleCycle)
{
    vector<int> path = {0,1,2,0};

    EXPECT_TRUE(isSimpleCycle(graph,path));
}

TEST_F(CycleTest, RepeatedNode)
{
    vector<int> path = {0,1,2,1,0};

    EXPECT_FALSE(isSimpleCycle(graph,path));
}

TEST_F(CycleTest, MissingEdge)
{
    vector<int> path = {0,2,1,0};

    EXPECT_FALSE(isSimpleCycle(graph,path));
}

TEST_F(CycleTest, NotClosed)
{
    vector<int> path = {0,1,2};

    EXPECT_FALSE(isSimpleCycle(graph,path));
}

class KevinBaconTest : public ::testing::Test
{
protected:
    AdjListGraph<string> social;

    void SetUp() override
    {
        vector<string> people =
        {
            "Me",
            "Alice",
            "Bob",
            "Carol",
            "Dave",
            "Eve",
            "Frank",
            "Grace",
            "Henry",
            "Ivy",
            "Jack",
            "Kelly",
            "Luke",
            "Mary",
            "Nancy",
            "Oscar",
            "Paul",
            "Quinn",
            "Rose",
            "Kevin Bacon"
        };

        for(auto person : people)
        {
            social.addNode(person);
        }

        social.addEdge("Me","Alice");
        social.addEdge("Alice","Me");

        social.addEdge("Alice","Bob");
        social.addEdge("Bob","Alice");

        social.addEdge("Bob","Carol");
        social.addEdge("Carol","Bob");

        social.addEdge("Carol","Kevin Bacon");
        social.addEdge("Kevin Bacon","Carol");
    }
};

TEST_F(KevinBaconTest, Connected)
{
    list<string> path;

    bool result = findKevinBacon(social, "Me", "Kevin Bacon", path);

    EXPECT_TRUE(result);

    EXPECT_EQ(path.front(),"Me");
    EXPECT_EQ(path.back(),"Kevin Bacon");
    EXPECT_EQ(path.size()-1,4);
}

TEST_F(KevinBaconTest, NotConnected)
{
    AdjListGraph<string> graph;

    graph.addNode("Me");
    graph.addNode("Kevin Bacon");

    list<string> path;

    EXPECT_FALSE(findKevinBacon(graph, "Me", "Kevin Bacon", path));
    EXPECT_TRUE(path.empty());
}

// Google Test Main
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}