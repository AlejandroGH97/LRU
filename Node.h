#ifndef NODE_H
#define NODE_H

template<typename keyType, typename valType>
struct Node {
  keyType key;
  valType value;
  Node<keyType,valType>* next;
  Node<keyType,valType>* prev;
  Node(keyType key, valType value);
};

template<typename keyType, typename valType>
Node<keyType,valType>::Node(keyType key, valType value){
    this->key = key;
    this->value = value;
    next = nullptr;
    prev = nullptr;
}
#endif