#ifndef FIBHEAP_H_
#define FIBHEAP_H_

#include <list>
#include <iostream>
#include <vector>
#include "fibnode.h"

template<class T>
class fibheap
{
 public:
  fibheap<T>():trees(std::list<fibnode<T>*>()),extreme(nullptr), heights(std::vector<std::list<fibnode<T>*>*>()), maxHeap(false){heights.push_back(new std::list<fibnode<T>*>());} //Default Constructor; creates a minheap
  fibheap<T>(bool isMaxHeap):trees(std::list<fibnode<T>*>()),extreme(nullptr), heights(std::vector<std::list<fibnode<T>*>*>()),  maxHeap(isMaxHeap){heights.push_back(new std::list<fibnode<T>*>());} //Non-Default Constructor; creates a minheap if false is passed, a maxheap if true is passed
  ~fibheap<T>(); //Deconstructor
	
  fibnode<T>* getExtreme(){return extreme;} //Returns a pointer to the min node if minheap, max node if maxheap
  T getExtremeValue(){return extreme->getValue();} //Returns the value of the min node if minheap, max node if maxheap
  int getSize(){return trees.size();} //Returns the number of trees in the heap

  T deleteExtreme(); //Removes the min if minheap, max if maxheap
  fibnode<T>* insert(std::pair<double, T> value); //Inserts a new node. The first item in the pair is the key, the second is the value
  void changeKey(double amount, fibnode<T>* nd); //Changes the key of the node given
	
  template<class U>
    friend std::ostream& operator<< (std::ostream& out, const fibheap<U> &fhp); //Prints the heap to the command line. Nodes are written as "(key,value)"; each tree is listed in a line, with the root first
	
	private:
	bool maxHeap;
	std::list<fibnode<T>*> trees;
	std::vector<std::list<fibnode<T>*>*> heights;
	fibnode<T>* extreme;
	
	void consolidate();
};

#include "fibheap.cpp"

#endif
