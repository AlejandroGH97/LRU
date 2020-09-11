#include "LRU.h"

enum {LRU, FIFO};

template<typename T>
void print(T* x) {
  if(x){
    cout<<*x<<endl;
  }
  else{
    cout<<"None"<<endl;
  }
}

int main() {
  LRUCache<char, int, LRU>* test = new LRUCache<char, int, LRU>(3);
  int* res;
  cout<<"LRU TESTS:"<<endl;
  test->insertKeyValuePair('b', 2);
  test->insertKeyValuePair('a', 1);
  test->insertKeyValuePair('c', 3);
  cout<<test->getMostRecentKey()<<endl; //c
  res = test->getValueFromKey('a');
  print(res); //1
  cout<<test->getMostRecentKey()<<endl; //a
  test->insertKeyValuePair('d', 4); 
  res = test->getValueFromKey('b');
  print (res); //None
  test->insertKeyValuePair('a', 5);
  res = test->getValueFromKey('a');
  print(res); //5

  delete(test);

  LRUCache<char, int, FIFO>* test2 = new LRUCache<char, int, FIFO>(3);

  cout<<endl<<"FIFO TESTS:"<<endl;
  test2->insertKeyValuePair('a', 1);
  test2->insertKeyValuePair('b', 2);
  test2->insertKeyValuePair('c', 3);
  res = test2->getValueFromKey('b');
  print(res);
  cout<<test2->getMostRecentKey()<<endl; //c, en FIFO no se modifica el orden si hay un hit.
  test2->insertKeyValuePair('d', 4);
  cout<<test2->getMostRecentKey()<<endl; //d
  res = test2->getValueFromKey('a'); //Insertamos el cuarto elemento entonces a desaparece.
  print (res); //None
}