#pragma once

#include <functional>

class Tree
{
private:

    struct Node
    {
        int data;

        Node* left;
        Node* right;

        Node(int value)
        {
            data = value;

            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;

    Node* insert(Node* node, int value)
    {
        if(node == nullptr)
        {
            return new Node(value);
        }

        if(value < node->data)
        {
            node->left = insert(node->left, value);
        }
        else if(value > node->data)
        {
            node->right = insert(node->right, value);
        }

        return node;
    }

    bool member(Node* node, int value)
    {
        if(node == nullptr)
        {
            return false;
        }

        if(node->data == value)
        {
            return true;
        }

        if(value < node->data)
        {
            return member(node->left, value);
        }

        return member(node->right, value);
    }

    void inorder(Node* node, std::function<void(int)> visit)
    {
        if(node == nullptr)
        {
            return;
        }

        inorder(node->left, visit);

        visit(node->data);

        inorder(node->right, visit);
    }

    int size(Node* node)
    {
        if(node == nullptr)
        {
            return 0;
        }

        return 1 + size(node->left) + size(node->right);
    }

    void destroy(Node* node)
    {
        if(node == nullptr)
        {
            return;
        }

        destroy(node->left);

        destroy(node->right);

        delete node;
    }

public:

    Tree()
    {
        root = nullptr;
    }

    // Move constructor
    Tree(Tree&& other)
    {
        root = other.root;

        other.root = nullptr;
    }

    ~Tree()
    {
        destroy(root);
    }

    void insert(int value)
    {
        root = insert(root, value);
    }

    bool member(int value)
    {
        return member(root, value);
    }

    int size()
    {
        return size(root);
    }

    void traverse(std::function<void(int)> visit)
    {
        inorder(root, visit);
    }
};