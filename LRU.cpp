#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

struct Node {
  char key;
  int value;
  Node* next;
  Node* prev;
  Node(char key, int value) {
    this->key = key;
    this->value = value;
    next = nullptr;
    prev = nullptr;
  }
};

class LinkedList {
public:
    Node* head;
    Node* tail;

    LinkedList() {
      head = nullptr;
      tail = nullptr;
    }

    Node* insert(char key, int value) {
      if( !head ) {
        head = new Node(key, value);
        tail = head;
        head->next = tail;
        head->prev = tail;
        return head;
      }
      else {
        Node* temp = new Node(key, value);
        temp->next = head;
        tail->next = temp;
        tail = temp;
        return temp;
      }
    }


};

class LRUCache {
  private:
    int maxSize;
    int curSize=0;
    char recentKey;
    unordered_map<char, Node*> keys;
    LinkedList* values;

  public:
    LRUCache() {
      maxSize = 10;
      values = new LinkedList();
    }
    LRUCache(int n) {
      maxSize = n;
      values = new LinkedList();
    }

    void insertKeyValuePair(char key, int value) {
      recentKey = key;
      if( curSize < maxSize ) {
        try {
          Node* temp = keys.at(key);
          temp->value = value;
        }
        catch (out_of_range& e) {
          Node* temp = values->insert(key,value);
          keys.insert({key,temp});

        }
        curSize++;
      }
      else {
        Node* temp = values->head;
        values->head = temp->next;
        values->tail = temp;
        temp->key = key;
        temp->value = value;
        keys.erase(temp->key);
        keys.insert({key,temp});
        values->insert(key,value);

      }


    }

    int* getValueFromKey(char key) {

      try {
        Node* temp = keys.at(key);
        recentKey = key;
        if( temp != values->tail ){
          temp->prev->next = temp->next;
          values->tail->next = temp;
          temp->next = values->head;
          values->tail = temp;
        }
        return &temp->value;
      }
      catch (out_of_range& e) {
        return nullptr;
      }

    }

    char getMostRecentKey() {
      return recentKey;
    }
};

int main() {
  LRUCache* test = new LRUCache(3);
  test->insertKeyValuePair('b', 2);
  test->insertKeyValuePair('a', 1);
  test->insertKeyValuePair('c', 3);
  cout<<test->getMostRecentKey()<<endl;
  cout<<*test->getValueFromKey('a')<<endl;
  cout<<test->getMostRecentKey()<<endl;
}
