#ifndef FIBNODE_H_
#define FIBNODE_H_

#include <list>
#include <iostream>

template<class T>
class fibnode
{
 public:
 fibnode(std::pair<double,T> val):value(val),height(0),marked(false){} //Constructor; the first value in the pair is the key, the second the value
  ~fibnode(){} //Deconstructor
	
  double getKey(){return value.first;} //Getter; returns the key
  void changeKey(double value, bool increase); //If increase is true, key increases by value. If increase is false, key is replaced by value
  T getValue(){return value.second;} //Getter; returns the value
  std::list<fibnode<T>*>* getChildren(){return &children;} //Returns a list consisting of pointers to this node's children. Be cautious when using
  void addChild(fibnode<T>* other); //Adds a child to this node. Be cautious when using
  void removeParent(){parent = nullptr;} //Sets the parent to 0. Do not use; part of setting up a new tree
  fibnode<T>* getParent(){return parent;} //Returns this node's parent
  bool isMarked(){return marked;} //Returns true if the node is "marked"
  void setMarked(bool val){marked = val;} //If true, sets node to marked. If false, sets node to unmarked

  void print(); //Prints the node to the command line. Written as "(Key, Value)"
  int calculateHeight(); //Calculates and returns the height of the node in the given tree. The head of a node is considered to be of height 0
  void merge(fibnode<T>* other); //Adds a node, with children, to this node's children
  void deleteTree(); //Deletes this node and all nodes below it
	
  template<class U>
    friend std::ostream& operator<< (std::ostream& out, const fibnode<U> &fbn); //Same as print();
	
 private:
  std::list<fibnode<T>*> children;
  fibnode* parent;
  std::pair<double, T> value;
  int height;
  bool marked;	
};

#include "fibnode.cpp"

#endif
