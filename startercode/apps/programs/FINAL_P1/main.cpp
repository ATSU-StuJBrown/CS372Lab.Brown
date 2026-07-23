#include "Tree.hpp"
#include "List.hpp"
#include "Fringe.hpp"

#include <iostream>

using namespace std;

int main()
{
    Tree<int> tree1;
    tree1 = tree1.insert(5);
    tree1 = tree1.insert(3);
    tree1 = tree1.insert(8);
    tree1 = tree1.insert(2);
    tree1 = tree1.insert(9);

    Tree<int> tree2;
    tree2 = tree2.insert(8);
    tree2 = tree2.insert(5);
    tree2 = tree2.insert(3);
    tree2 = tree2.insert(2);
    tree2 = tree2.insert(9);

    cout << "Tree 1:    5\n";
    cout << "          / \\\n";
    cout << "         3   8\n";
    cout << "        /     \\\n";
    cout << "       2       9\n";

    cout << "\nTree 2:    8\n";
    cout << "          /\n";
    cout << "         5\n";
    cout << "        /\n";
    cout << "       3\n";
    cout << "      / \\\n";
    cout << "     2   9\n";

    cout << "Do the trees share the same fringe? ";

    if (hasSameFringe(tree1, tree2))
    {
        cout << "Yes!" << endl;
    }
    else
    {
        cout << "No!" << endl;
    }

    cout << endl; return 0;
}