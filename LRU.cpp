#include "LRU.h"

template<typename keyType, typename valType>
LRUCache<keyType, valType>::LRUCache() {
      maxSize = 10;
      values = new LinkedList<keyType, valType>();
      curSize = 0;
}

template<typename keyType, typename valType>
LRUCache<keyType, valType>::LRUCache(int n) {
    maxSize = n;
    values = new LinkedList<keyType, valType>();
    curSize = 0;
}
template<typename keyType, typename valType>
void LRUCache<keyType, valType>::insertKeyValuePair(keyType key, valType value) {
    //cout<<"Insert\n";
    recentKey = key;
    if( curSize < maxSize ) {
    try { //Existe el key entonces cambiamos su valor y lo movemos al tail (mas reciente).
        Node<keyType, valType>* temp = keys.at(key);
        cout<<"Key changed, inc\n"; 
        temp->value = value;
        if(temp != values->tail) {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        values->tail->next = temp;
        temp->prev = values->tail;
        temp->next = values->head;
        values->head->prev = temp;
        values->tail = temp;
        }

    }
    catch (out_of_range& e) {//No existe el key y hay espacio, insertamos al final.
        //cout<<"New key\n";
        Node<keyType, valType>* temp = values->insert(key,value);
        keys.insert(pair<keyType, Node<keyType, valType>*>(key,temp));

    }
    curSize++;
    }
    else {
    try {//No hay espacio y existe el key. Cambiamos el valor y lo movemos al final.
        Node<keyType, valType>* temp = keys.at(key);
        //cout<<"Key changed\n";
        temp->value = value;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        values->tail->next = temp;
        temp->next = values->head;
        values->head->prev = temp;
        values->tail = temp;
    }
    //Como no existe el key, reemplazamos el head por el nuevo key y avanzamos el LL un lugar. 
    //Como cambiamos un key, tenemos que borrar y crear un nuevo entry en nuestro unordered_map.
    catch (out_of_range& e) {
        char tempKey = values->head->key;
        Node<keyType, valType>* tempNode = keys.at(tempKey);
        keys.erase(tempKey);
        keys.insert(pair<keyType, Node<keyType, valType>*>(key,tempNode));
        tempNode->key = key;
        tempNode->value = value;
        values->tail = values->head;
        values->head = values->head->next;
    }

    }

}

template<typename keyType, typename valType>
valType LRUCache<keyType, valType>::getValueFromKey(keyType key) {
    //cout<<"GetValue\n";
    try {//Sacamos el valor del key y si no es el tail lo movemos al tail.
    Node<keyType, valType>* temp = keys.at(key);
    recentKey = key;
    if( temp != values->tail ){
        temp->prev->next = temp->next;
        values->tail->next = temp;
        temp->next = values->head;
        values->tail = temp;
    }
    
    return temp->value;
    }
    catch (out_of_range& e) { //No existe el key entonces retornamos -1 (Se puede cambiar a punteros para poder retornar null).
    return -1;
    }

}

template<typename keyType, typename valType>
keyType LRUCache<keyType, valType>::getMostRecentKey() {
    //cout<<"Most recent\n";
    return recentKey;
}