#include "Node.h"

template<typename keyType, typename valType>
Node<keyType,valType>::Node(keyType key, valType value){
    this->key = key;
    this->value = value;
    next = nullptr;
    prev = nullptr;
}