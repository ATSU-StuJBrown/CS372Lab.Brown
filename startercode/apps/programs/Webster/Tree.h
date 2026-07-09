#pragma once
#include <functional>

template<typename T>
class Tree
{
private:

    struct Node
    {
        T data;
        Node* left;
        Node* right;

        Node(const T& value)
        {
            data = value;

            left = nullptr;
            right = nullptr;
        }
    };

    Node* rootNode;

    //------------------------------------------------
    Node* copy(Node* node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        Node* newNode = new Node(node->data);

        newNode->left = copy(node->left);
        newNode->right = copy(node->right);

        return newNode;
    }

    //------------------------------------------------
    void destroy(Node* node)
    {
        if (node == nullptr)
        {
            return;
        }

        destroy(node->left);
        destroy(node->right);

        delete node;
    }

    //------------------------------------------------
    Node* insert(Node* node, const T& value)
    {
        if (node == nullptr)
        {
            return new Node(value);
        }

        if (value < node->data)
        {
            node->left = insert(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = insert(node->right, value);
        }

        return node;
    }

    //------------------------------------------------
    Node* findKey(Node* node, int key) const
    {
        if(node == nullptr)
        {
            return nullptr;
        }

        if(node->data.first == key)
        {
            return node;
        }

        if(key < node->data.first)
        {
            return findKey(node->left,key);
        }

        return findKey(node->right,key);
    }

    //------------------------------------------------
    Node* smallest(Node* node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }

        return node;
    }

    //------------------------------------------------
    Node* eraseKey(Node* node,int key)
    {
        if(node == nullptr)
        {
            return nullptr;
        }

        if(key < node->data.first)
        {
            node->left = eraseKey(node->left,key);
        }
        else if(key > node->data.first)
        {
            node->right = eraseKey(node->right,key);
        }
        else
        {
            if(node->left == nullptr)
            {
                Node* temp = node->right;

                delete node;
                return temp;
            }


            if(node->right == nullptr)
            {
                Node* temp = node->left;

                delete node;
                return temp;
            }


            Node* temp = smallest(node->right);

            node->data = temp->data;

            node->right = eraseKey(node->right, temp->data.first);
        }

        return node;
    }

    //------------------------------------------------
    void inorder(Node* node, std::function<void(const T&)> visit) const
    {
        if(node == nullptr)
        {
            return;
        }

        inorder(node->left,visit);

        visit(node->data);

        inorder(node->right,visit);
    }

public:

    //------------------------------------------------
    Tree()
    {
        rootNode = nullptr;
    }

    //------------------------------------------------
    Tree(const Tree& rhs)
    {
        rootNode = copy(rhs.rootNode);
    }

    //------------------------------------------------
    Tree& operator=(const Tree& rhs)
    {
        if (this != &rhs)
        {
            destroy(rootNode);

            rootNode = copy(rhs.rootNode);
        }

        return *this;
    }

    //------------------------------------------------
    ~Tree()
    {
        destroy(rootNode);
    }

    //------------------------------------------------
    bool isEmpty() const
    {
        return rootNode == nullptr;
    }

    //------------------------------------------------
    void insert(const T& value)
    {
        rootNode = insert(rootNode, value);
    }

    //------------------------------------------------
    T* findKey(int key)
    {
        Node* result = findKey(rootNode,key);

        if(result == nullptr)
        {
            return nullptr;
        }

        return &result->data;
    }

    bool memberKey(int key)
    {
        return findKey(key) != nullptr;
    }

    void eraseKey(int key)
    {
        rootNode = eraseKey(rootNode,key);
    }

    //------------------------------------------------
    void clear()
    {
        destroy(rootNode);

        rootNode = nullptr;
    }

    //------------------------------------------------
    void traverse(std::function<void(const T&)> visit) const
    {
        inorder(rootNode, visit);
    }
};