#pragma once

#include <algorithm>

class AVLTree
{
private:
    struct Node
    {
        int key;

        int height;

        Node* left;
        Node* right;


        Node(int value)
        {
            key = value;

            height = 1;

            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;

    int height(Node* node)
    {
        if(node == nullptr)
        {
            return 0;
        }

        return node->height;
    }

    int balance(Node* node)
    {
        if(node == nullptr)
        {
            return 0;
        }

        return height(node->left) - height(node->right);
    }

    Node* rotateRight(Node* y)
    {
        Node* x = y->left;
        Node* temp = x->right;

        x->right = y;
        y->left = temp;

        y->height = 1 + std::max(height(y->left), height(y->right));
        x->height = 1 + std::max(height(x->left), height(x->right));

        return x;
    }

    Node* rotateLeft(Node* x)
    {
        Node* y = x->right;
        Node* temp = y->left;

        y->left = x;
        x->right = temp;

        x->height = 1 + std::max(height(x->left), height(x->right));
        y->height = 1 + std::max(height(y->left),  height(y->right));

        return y;
    }

    Node* insert(Node* node, int key)
    {

        if(node == nullptr)
        {
            return new Node(key);
        }

        if(key < node->key)
        {
            node->left = insert(node->left, key);
        }
        else if(key > node->key)
        {
            node->right = insert(node->right, key);
        }
        else
        {
            return node;
        }

        node->height = 1 + std::max(height(node->left), height(node->right));

        int balanceValue = balance(node);

        // Left Left
        if(balanceValue > 1 && key < node->left->key)
        {
            return rotateRight(node);
        }

        // Right Right
        if(balanceValue < -1 && key > node->right->key)
        {
            return rotateLeft(node);
        }

        // Left Right
        if(balanceValue > 1 && key > node->left->key)
        {
            node->left = rotateLeft(node->left);

            return rotateRight(node);
        }

        // Right Left
        if(balanceValue < -1 && key < node->right->key)
        {
            node->right = rotateRight(node->right);

            return rotateLeft(node);
        }

        return node;
    }

    bool search(Node* node, int key)
    {
        if(node == nullptr)
        {
            return false;
        }

        if(node->key == key)
        {
            return true;
        }

        if(key < node->key)
        {
            return search(node->left, key);
        }

        return search(node->right, key);
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
    AVLTree()
    {
        root = nullptr;
    }

    // Move constructor
    AVLTree(AVLTree&& other)
    {
        root = other.root;

        other.root = nullptr;
    }

    ~AVLTree()
    {
        destroy(root);
    }

    void insert(int key)
    {
        root = insert(root, key);
    }

    bool search(int key)
    {
        return search(root, key);
    }

};