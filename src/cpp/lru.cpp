/*
Author: Jake Mathai
Purpose: LRU implementation
*/

#include <iostream>
#include <unordered_map>
#include <list>

class Object {
    public:
        Object() {}
        template <class T> Object(const T& v);
        Object(const Object& o);
        
        struct AbstractObject {
            virtual ~AbstractObject() {}
            virtual void* get_data() { return 0; }
            virtual void* get_type() { return 0; }
            virtual AbstractObject* clone() const { return 0; }
        };

        template <class T> 
        struct ConcreteObject : public AbstractObject {
            T data;
            static int type;
            ConcreteObject(const T& v): data(v) {}
            virtual ~ConcreteObject () {}
            virtual void* get_data() { return &data; }
            virtual void* get_type() { return &type; }
            virtual ConcreteObject* clone() const { return new ConcreteObject<T>(data); }
            static void* get_type_static() { return &type; }
        };
        AbstractObject* object;
};

template <class T> 
Object::Object(const T& v) { 
    object = new ConcreteObject<T>(v); 
};

Object::Object(const Object& o) {
    object = o.object -> clone();
}

template <class T>
int Object::ConcreteObject<T>::type;

class LRU {
    public:
        LRU();
        LRU(unsigned long long _max_size);
        Object* get(Object* key);
        Object* operator[](Object* key);
        void set(Object* key, Object* value);
        void insert(Object* key, Object* value);
        void remove(Object* key);
        void erase(Object* key);
        unsigned long long size;
        unsigned long long max_size;
        std::list<Object*> items;
        std::unordered_map<Object*, std::list<Object*>::iterator> table;
};

LRU::LRU() {};

LRU::LRU(unsigned long long _max_size) {
    max_size = _max_size;
}

Object* LRU::get(Object* key) {
    std::unordered_map<Object*, std::list<Object*>::iterator>::iterator table_iterator = table.find(key);
    if (table_iterator == table.end())
        return nullptr;
    return *(table_iterator -> second);
}

void LRU::set(Object* key, Object* value) {
    if (items.size() >= max_size)
        items.pop_back();
    items.push_front(value);
    table.insert(std::pair<Object*, std::list<Object*>::iterator>(key, items.begin()));
    size = items.size();
}

void LRU::insert(Object* key, Object* value) {
    set(key, value);
}

void LRU::remove(Object* key) {
    std::unordered_map<Object*, std::list<Object*>::iterator>::iterator table_iterator = table.find(key);
    if (table_iterator == table.end())
        return;
    items.erase(table_iterator -> second);
}

void LRU::erase(Object* key) {
    remove(key);
}

Object* LRU::operator[](Object* key) {
    return get(key);
}

extern "C" {
    LRU* create(unsigned long long max_size) { 
        return new LRU(max_size);
    }
    Object* get(LRU* cache, Object* key) {
        return cache -> get(key);
    }
    void set(LRU* cache, Object* key, Object* value) {
        cache -> set(key, value);
    }
    void print(LRU* cache) {
        std::list<Object*>::iterator i = cache -> items.begin();
        for (; i != cache -> items.end(); ++i) {
            std::cout << *i << std::endl;
        }
    }
    unsigned long long size(LRU* cache) {
        return cache -> size;
    }
}