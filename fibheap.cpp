template<class T>
fibheap<T>::~fibheap<T>(){
	for(auto i:trees){
		i->deleteTree();
	}
	for(auto i: heights){
		delete i;
	}
}

template<class T>
fibnode<T>* fibheap<T>::insert(std::pair<double, T> value)
{
	//Add tree
	fibnode<T>* tmp = new fibnode<T>(value);
	trees.push_back(tmp);
	heights[0]->push_back(tmp);
	
	//Update min and max
	if(trees.size()==1)
	{
		extreme = tmp;
	}
	else
	{
		if(maxHeap)
		{
			if(value.first > extreme->getKey()) extreme = tmp;
		}else{ 
			if(value.first < extreme->getKey()) extreme = tmp;
		}
	}
	return tmp;
}

template<class T>
void fibheap<T>::changeKey(double amount, fibnode<T>* nd){
  nd->changeKey(amount, maxHeap);
  if((maxHeap && nd->getKey() > extreme->getKey()) ||
     (!maxHeap && nd->getKey() < extreme->getKey())){
    extreme = nd;
  }
  if(nd->getParent() != nullptr){
    if((maxHeap && nd->getKey() > nd->getParent()->getKey()) ||
       (!maxHeap && nd->getKey() < nd->getParent()->getKey())){
      fibnode<T>* pnt;
      do{
	pnt = nd->getParent();
	nd->setMarked(false);
	trees.push_back(nd);
	nd->getParent()->getChildren()->remove(nd);
	nd->removeParent();
	heights[0]->push_back(nd);
	nd = pnt;
      }while(nd != nullptr && nd->isMarked());
      if(nd != nullptr)
	nd->setMarked(true);
    }
  }
}

template<class T>
void fibheap<T>::consolidate(){
	fibnode<T>* tmp1;
	fibnode<T>* tmp2;
	for(int i = 0; i < heights.size(); i++){
		while(heights[i]->size() >= 2){
			tmp1 = heights[i]->back();
			heights[i]->pop_back();
			tmp2 = heights[i]->back();
			heights[i]->pop_back();			
			if(maxHeap){
				if(tmp1->getKey() < tmp2->getKey()){
					if(i + 1 == heights.size())
						heights.push_back(new std::list<fibnode<T>*>());
					tmp2->addChild(tmp1);
					trees.remove(tmp1);
					heights[i + 1]->push_back(tmp2);
				}else{
					if(i + 1 == heights.size())
						heights.push_back(new std::list<fibnode<T>*>());
					tmp1->addChild(tmp2);
					trees.remove(tmp2);
					heights[i + 1]->push_back(tmp1);
				}			
			}else{
				if(tmp1->getKey() > tmp2->getKey()){
					if(i + 1 == heights.size())
						heights.push_back(new std::list<fibnode<T>*>());
					tmp2->addChild(tmp1);
					trees.remove(tmp1);
					heights[i + 1]->push_back(tmp2);
				}else{
					if(i + 1 == heights.size())
						heights.push_back(new std::list<fibnode<T>*>());
					tmp1->addChild(tmp2);
					trees.remove(tmp2);
					heights[i + 1]->push_back(tmp1);
				}
			}
		}
	}
}

template<class T>
T fibheap<T>::deleteExtreme(){
  T retVal = extreme->getValue();
	trees.merge(*extreme->getChildren());
	trees.remove(extreme);
	heights[extreme->calculateHeight()]->remove(extreme);
	for(auto i:*extreme->getChildren()){
    heights[i->getHeight()]->push_back(i);
	  i->removeParent();
	}
	delete extreme;
	consolidate();
	//Find new extreme
	extreme = trees.front();
	if(maxHeap){
		for(auto i:trees){
			if(i->getKey() > extreme->getKey()){
				extreme = i;
			}
		}
	}else{
		for(auto i:trees){
			if(i->getKey() < extreme->getKey()){
				extreme = i;
			}
		}
	}
	return retVal;
}

template<class U>
std::ostream& operator<< (std::ostream& out, const fibheap<U>& fhp)
{
	for(auto i: fhp.trees)
	{
		i->print();
		out << std::endl;
	}
	out << std::endl;
}
