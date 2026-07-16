#include "BSTTree.h"
#include "AVLTree.h"

#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <utility>

using namespace std;

// ***Used ChatGPT for error handling alongside labs***

Tree randTree(int amount)
{
    Tree tree;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1,1000000);

    while(tree.size() < amount)
    {
        tree.insert(dist(gen));
    }

    return tree;
}

AVLTree buildAVL(Tree& tree)
{
    AVLTree avl;

    tree.traverse([&](int value){avl.insert(value);});

    return avl;
}

pair<double,double> compareTrees(Tree& tree, AVLTree& avl)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1,1000000);

    double BSTTime = 0;
    double AVLTime = 0;

    for(int i = 0; i < 100; i++)
    {
        int number = dist(gen);

        // BST
        auto start = chrono::steady_clock::now();

        tree.member(number);

        auto end = chrono::steady_clock::now();

        BSTTime += chrono::duration<double,nano> (end-start).count();

        // AVL
        start = chrono::steady_clock::now();

        avl.search(number);

        end = chrono::steady_clock::now();
        AVLTime += chrono::duration<double,nano> (end-start).count();
    }

    return
    {
        BSTTime / 100.0,
        AVLTime / 100.0
    };

}

int main()
{
    vector<int> sizes = {100, 500, 1000, 2500, 5000, 10000};

    cout << "Size\tBST(ns)\tAVL(ns)" << endl;

    for(int size : sizes)
    {
        Tree BST = randTree(size);
        AVLTree AVL = buildAVL(BST);

        pair<double,double> result = compareTrees(BST, AVL);

        cout << size << "\t" << result.first << "\t" << result.second << endl;
    }

    cout << endl; return 0;
}