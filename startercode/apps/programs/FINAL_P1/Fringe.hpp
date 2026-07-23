#include "Tree.hpp"
#include "List.hpp"

#pragma once

template<typename T>
List<T> fringe(const Tree<T>& tree)
{
    List<T> leaves;

    if (tree.isEmpty())
    {
        return leaves;
    }

    if (tree.isLeaf())
    {
        leaves.push_back(tree.root());
    }
    else
    {
        List<T> leftLeaves = fringe(tree.left());
        List<T> rightLeaves = fringe(tree.right());

        auto left = leftLeaves.begin();

        while (left != leftLeaves.end())
        {
            leaves.push_back(*left);
            ++left;
        }

        auto right = rightLeaves.begin();

        while (right != rightLeaves.end())
        {
            leaves.push_back(*right);
            ++right;
        }
    }

    return leaves;
}

template<typename T>
bool hasSameFringe(const Tree<T>& tree1, const Tree<T>& tree2)
{
    List<T> f1 = fringe(tree1);
    List<T> f2 = fringe(tree2);

    auto a = f1.begin();
    auto b = f2.begin();

    while (a != f1.end() && b != f2.end())
    {
        if (*a != *b)
        {
            return false;
        }
        ++a;
        ++b;
    }
    return a == f1.end() && b == f2.end();
}