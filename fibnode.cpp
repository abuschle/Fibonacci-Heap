template<class T>
void fibnode<T>::print(){
  std::cout << "(" << value.first << ", " << value.second << ") ";
	for(auto i: children)
	{
		i->print();
	}
}

template<class T>
void fibnode<T>::changeKey(double amount, bool increase){
  if(increase){
    value.first += amount;
  }else{
    value.first -= amount;
  }
}

template<class T>
void fibnode<T>::addChild(fibnode<T>* other){
  children.push_back(other);
  other->parent = this;
}

template<class T>
int fibnode<T>::calculateHeight()
{
	if(children.empty()) return 0;
	int maxHeight = 0;
	for(auto i: children)
	{
		int childHeight = i->calculateHeight() + 1;
		if(childHeight > maxHeight) maxHeight = childHeight;
	}
	height = maxHeight;
	return maxHeight;
}

template<class T>
void fibnode<T>::merge(fibnode<T>* other){
	if(getKey() > other->getKey()){
		other->addChild(this);
	}else{
		addChild(other);
	}
}

template<class T>
void fibnode<T>::deleteTree(){
	for(auto i:children){
		i->deleteTree();
	}
	delete this;
}

template<class U>
std::ostream& operator<< (std::ostream& out, const fibnode<U>& fbn)
{
	out << "(" << fbn.value.first << ", " << fbn.value.second << ")  ";
}
