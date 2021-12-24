/*
Author: Jake Mathai
Purpose: LRU implementation
*/

#include <iostream>
#include <unordered_map>
#include <list>
#include <Python.h>

template <class Key, class Value>
class LRU {
    public:
        typedef typename std::list<Value>::iterator ValueIter;
        
        LRU<Key, Value>(unsigned long long _max_size);
        Value get(Key key);
        void set(Key key, Value value);
        void remove(Key key);
        unsigned long long max_size;
        std::list<Value> items;
        std::unordered_map<Key, ValueIter> table;
};

template <class Key, class Value>
LRU<Key, Value>::LRU(unsigned long long _max_size) {
    max_size = _max_size;
}

template <class Key, class Value>
Value LRU<Key, Value>::get(Key key) {
    auto table_iterator = table.find(key);
    if (table_iterator == table.end())
        return nullptr;
    return *(table_iterator -> second);
}

template <class Key, class Value>
void LRU<Key, Value>::set(Key key, Value value) {
    if (items.size() >= max_size)
        items.pop_back();
    items.push_front(value);
    table[key] = items.begin();
}

template <class Key, class Value>
void LRU<Key, Value>::remove(Key key) {
    auto table_iterator = table.find(key);
    if (table_iterator != table.end())
        return;
    items.erase(table_iterator -> second);
    table.erase(table_iterator);
}

extern "C" {
    LRU<PyObject*, PyObject*>* create(unsigned long long max_size) { 
        return new LRU<PyObject*, PyObject*>(max_size);
    }
    PyObject* get(LRU<PyObject*, PyObject*>* cache, PyObject* key) {
        return cache -> get(key);
    }
    void set(LRU<PyObject*, PyObject*>* cache, PyObject* key, PyObject* value) {
        cache -> set(key, value);
    }
    unsigned long long size(LRU<PyObject*, PyObject*>* cache) {
        return cache -> items.size();
    }
}