#pragma once
#include <stdexcept>
#include <utility>

#include "Pair.h"
#include "Tree.h"
#include "List.h"

template<typename Key, typename Value>
class Dictionary
{
private:

    Tree<Pair<Key,Value>> tree;

    int numItems;

    List<Key> keyList;
    List<Value> valueList;

public:
    Dictionary()
    {
        numItems = 0;
    }

    Dictionary(const Dictionary& rhs) : tree(rhs.tree), numItems(rhs.numItems), keyList(rhs.keyList), valueList(rhs.valueList)
    {}
    Dictionary(Dictionary&& rhs) : tree(std::move(rhs.tree)), numItems(rhs.numItems), keyList(std::move(rhs.keyList)), valueList(std::move(rhs.valueList))
    {
        rhs.numItems = 0;
    }

    Dictionary& operator=(const Dictionary& rhs)
    {
        if(this != &rhs)
        {
            tree = rhs.tree;
            numItems = rhs.numItems;
            keyList = rhs.keyList;
            valueList = rhs.valueList;
        }

        return *this;
    }

    Dictionary& operator=(Dictionary&& rhs)
    {
        if(this != &rhs)
        {
            tree = std::move(rhs.tree);

            numItems = rhs.numItems;

            keyList = std::move(rhs.keyList);
            valueList = std::move(rhs.valueList);

            rhs.numItems = 0;
        }

        return *this;
    }

    ~Dictionary()
    {
        clear();
    }

    //------------------------------------------------
    // insert()
    void insert(const Key& key, const Value& value)
    {
        if(!tree.memberKey(key))
        {
            Pair<Key,Value> p(key,value);

            tree.insert(p);
            numItems++;
        }
    }

    // operator[]
    Value& operator[](const Key& key)
    {
        Pair<Key,Value>* found = tree.findKey(key);

        if(found == nullptr)
        {
            insert(key,Value());

            found = tree.findKey(key);
        }

        return found->second;
    }

    // at()
    Value& at(const Key& key)
    {
        Pair<Key,Value>* found = tree.findKey(key);

        if(found == nullptr)
        {
            throw std::out_of_range("Key Not Found");
        }

        return found->second;
    }

    // erase()
    void erase(const Key& key)
    {
        if(tree.memberKey(key))
        {
            tree.eraseKey(key);
            numItems--;
        }
    }

    // clear()
    void clear()
    {
        tree.clear();
        numItems = 0;
    }

    // isEmpty()
    bool isEmpty() const
    {
        return numItems == 0;
    }

    // size()
    int size() const
    {
        return numItems;
    }

    // keys()
    List<Key> keys() const
    {
        List<Key> result;

        tree.traverse(
            [&](const Pair<Key,Value>& p)
            {
                result.push_back(p.first);
            });

        return result;
    }

    // values()
    List<Value> values() const
    {
        List<Value> result;

        tree.traverse(
            [&](const Pair<Key,Value>& p)
            {
                result.push_back(p.second);
            });

        return result;
    }
};