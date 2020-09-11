#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"

template<typename keyType, typename valType>
class Node;

template<typename keyType, typename valType>
class LinkedList {
public:
    Node<keyType,valType>* head;
    Node<keyType,valType>* tail;

    LinkedList();

    Node<keyType,valType>* insert(keyType key, valType value);

};

template<typename keyType, typename valType>
LinkedList<keyType,valType>::LinkedList() {
      head = nullptr;
      tail = nullptr;
    }

template<typename keyType, typename valType>
Node<keyType,valType>* LinkedList<keyType, valType>::insert(keyType key, valType value) {
    if( !head ) {//Insert en lista vacia.
        head = new Node<keyType,valType>(key, value);
        tail = head;
        head->next = tail;
        head->prev = tail;
        return head;
    }
    else {//Insert cuando ya existe un elemento.
        Node<keyType, valType>* temp = new Node<keyType, valType>(key, value);
        temp->next = head;
        tail->next = temp;
        temp->prev = tail;
        head->prev = temp;
        tail = temp;
        return temp;
      }
}


#endif