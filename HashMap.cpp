//
//  HashMap.cpp
//  HashMap
//
//  Created by Andrew on 11/23/17.
//  Copyright © 2017 Andrew Golovenko. All rights reserved.
//

//
// Created by Andrew on 11/23/17.
//

#include <functional>
#include <iostream>

template<class K, class V>
class HashMap {
public:
    HashMap() : size_(0), head(nullptr), tail(nullptr) {}
    
    ~HashMap() {
        delete head;
    }
    
    void insert(K key, V value) {
        if (findNode(key))
            return;
        
        auto node = new Node(hash(key), new Pair(key, value), nullptr);
        if (size_ == 0) {
            head = node;
        } else if (size_ == 1) {
            tail = node;
            tail->previous = head;
            head->next = tail;
        } else {
            tail->next = node;
            node->previous = tail;
            tail = tail->next;
        }
        size_++;
    }
    
    void remove(K key) {
        if (size_ == 0)
            return;
        Node* n = findNode(key);
        if (n != nullptr) {
            if (n == head) {
                head = n->next;
            } else if (n == tail) {
                n->previous->next = nullptr;
                tail = n->previous;
            } else {
                n->previous->next = n->next;
            }
            n->next = nullptr;
            delete n;
            n = nullptr;
            size_--;
        }
    }
    
    bool find(K key, V& value) {
        auto pair = findPair(key);
        if (pair == nullptr)
            return false;
        value = pair->value;
        return true;
    }
    
    void print() {
        this->forEach([](Node* n) -> void {
            std::cout << "Key: " << n->item->key << " Value: " << n->item->value << std::endl;
        });
    }
    
private:
    struct Pair {
        Pair(K key, V value) : key(key), value(value) {}
        K key;
        V value;
    };
    struct Node {
        Node(size_t hash, Pair *item, Node *previous) : hash(hash), item(item), previous(previous), next(nullptr) {}
        
        std::size_t hash;
        Pair* item;
        Node* next;
        Node* previous;
        
        ~Node() {
            if (item != nullptr)
                delete item;
            if (next != nullptr)
                delete next;
        }
    };
    
    Node* findNode(K key) {
        if (size_ == 0)
            return nullptr;
        size_t h = hash(key);
        Node* result = nullptr;
        this->forEach([&h, &result](Node* p) -> void {
            if (p->hash == h) {
                result = p;
            }
        });
        return result;
    }
    
    Pair* findPair(K key) {
        Node* node = findNode(key);
        if (node != nullptr)
            return node->item;
        return nullptr;
    }
    
    void forEach(std::function<void(Node*)> f) {
        Node* current = head;
        for (int i = size_; i > 0; i--) {
            f(current);
            current = head->next;
        }
    }
    
    size_t hash(K key) {
        std::hash<K> h;
        return h(key);
    }
    
    Node* head, *tail;
    int size_;
    
};
