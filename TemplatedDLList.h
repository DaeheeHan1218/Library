// header file for the templated DLList

#ifndef TEMPLATEDDLLIST_H
#define TEMPLATEDDLLIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class DLList; // class declaration

// doubly linked list node
template <typename T>
struct DLListNode {
  T obj;
  DLListNode<T> *prev, *next;
  // constructor
  DLListNode(T e=T(), DLListNode *p=nullptr, DLListNode *n=nullptr): obj(e), prev(p), next(n) {}
};

// doubly linked list class
template <typename T>
class DLList {
private:
  DLListNode<T> header, trailer;
public:
  DLList(){
	DLListNode<T> dl;
	header = dl;
	trailer = dl;
	header.next = &trailer;
	trailer.prev = &header;
  }// default constructor
  
  DLList(const DLList<T>& dll){
	if(dll.header.next == &dll.trailer){//check if empty
		DLListNode<T> dl;
		header = dl;
		trailer = dl;
		header.next = &trailer;
		trailer.prev = &header;
	}
	else{
		header.next = new DLListNode<T>();
		header.next->obj = dll.header.next->obj;
		header.next->prev = &header;
		DLListNode<T>* temp = header.next;
		DLListNode<T>* cpyTemp = dll.header.next->next;
		while(cpyTemp != &dll.trailer){
			temp->next = new DLListNode<T>();
			temp->next->obj = cpyTemp->obj;
			temp->next->prev = temp;
			cpyTemp = cpyTemp->next;
			temp = temp->next;
		}
		trailer.prev = temp;
		temp->next = &trailer;
	}
  } // copy constructor
  
  DLList(DLList<T>&& dll){
	DLListNode<T> dl;
	header = dl;
	trailer = dl;
	header.next = dll.header.next;
	dll.header.next->prev = &header;
	trailer.prev = dll.trailer.prev;
	dll.trailer.prev->next = &trailer;
	dll.header.next = &dll.trailer;
	dll.trailer.prev = &dll.header;
  } // move constructor
  
  ~DLList(){
	DLListNode<T> *temp = header.next;
	while(temp != &trailer){
		DLListNode<T> *del = temp;
		temp = temp->next;
		delete del;
	}
	DLListNode<T> dl;
	header = dl;
	trailer = dl;
	header.next = &trailer;
	trailer.prev = &header;
  } // destructor
  
  DLList<T>& operator=(const DLList<T>& dll){
	if(this != &dll){
		DLListNode<T> *temp = header.next;//delete before copy
		while(temp != &trailer){
			DLListNode<T> *del = temp;
			temp = temp->next;
			delete del;
		}
		DLListNode<T> dl;
		header = dl;
		trailer = dl;
		header.next = &trailer;
		trailer.prev = &header;
		if(dll.header.next != &dll.trailer){//check if not empty
			header.next = new DLListNode<T>();
			header.next->obj = dll.header.next->obj;
			header.next->prev = &header;
			DLListNode<T>* temp = header.next;
			DLListNode<T>* cpyTemp = dll.header.next->next;
			while(cpyTemp != &dll.trailer){
				temp->next = new DLListNode<T>();
				temp->next->obj = cpyTemp->obj;
				temp->next->prev = temp;
				cpyTemp = cpyTemp->next;
				temp = temp->next;
			}
			trailer.prev = temp;
			temp->next = &trailer;
		}
    }
    return *this;
  } // copy assignment operator
  
  DLList<T>& operator=(DLList<T>&& dll){
	if(this != &dll){
		DLListNode<T> dl;
		header = dl;
		trailer = dl;
		header.next = dll.header.next;
		dll.header.next->prev = &header;
		trailer.prev = dll.trailer.prev;
		dll.trailer.prev->next = &trailer;
		dll.header.next = &dll.trailer;
		dll.trailer.prev = &dll.header;
	}
	return * this;
  } // move assignment operator
  // return the per to the first node
  DLListNode<T> *first_node() const { return header.next; } 
  // return the pointer to the trailer
  const DLListNode<T> *after_last_node() const { return &trailer; }
  // return if the list is empty
  bool is_empty() const { return header.next == &trailer; }
  T first() const{
	  return header.next->obj;
  } // return the first object
  T last() const{
	  return trailer.prev->obj;
  } // return the last object
  
  void insert_first(T obj){
	DLListNode<T>* ins = new DLListNode<T>();
	ins->obj = obj;
	ins->prev = &header;
	header.next->prev = ins;
	ins->next = header.next;
	header.next = ins;
  } // insert to the first node
  
  T remove_first(){
	if(header.next == &trailer){
		throw std::invalid_argument( "remove called on empty list" );
	}
	DLListNode<T>* del = header.next;
	del->next->prev = &header;
	header.next = del->next;
	T ret = del->obj;
	delete del;
	return ret;
  } // remove the first node
  
  void insert_last(T obj){
	DLListNode<T>* ins = new DLListNode<T>();
	ins->obj = obj;
	ins->prev = trailer.prev;
	ins->next = &trailer;
	trailer.prev->next = ins;
	trailer.prev = ins;
  } // insert to the last node
  
  T remove_last(){
	if(header.next == &trailer){
		throw std::invalid_argument( "remove called on empty list" );
	}
	DLListNode<T>* del = trailer.prev;
	del->prev->next = &trailer;
	trailer.prev = del->prev;
	T ret = del->obj;
	delete del;
	return ret;
  } // remove the last node
  
  void insert_after(DLListNode<T> &p, T obj){
	DLListNode<T>* ins = new DLListNode<T>();
	ins->obj = obj;
	ins->prev = &p;
	ins->next = p.next;
	p.next->prev = ins;
	p.next = ins;
  }
  
  void insert_before(DLListNode<T> &p, T obj){
	DLListNode<T>* ins = new DLListNode<T>();
	ins->obj = obj;
	ins->next = &p;
	ins->prev = p.prev;
	p.prev->next = ins;
	p.prev = ins;
  }
  
  T remove_after(DLListNode<T> &p){
	if(header.next == &trailer){
		throw std::invalid_argument( "remove called on empty list" );
	}
	if(&p != trailer.prev){
		DLListNode<T>* del = p.next;
		del->next->prev = &p;
		p.next = del->next;
		T ret = del->obj;
		delete del;
		return ret;
	}
	else{
		throw std::invalid_argument( "remove_after has last node as parameter" );
	}
  }
  T remove_before(DLListNode<T> &p){
	if(header.next == &trailer){
		throw std::invalid_argument( "remove called on empty list" );
	}
	if(&p != header.next){
		DLListNode<T>* del = p.prev;
		del->prev->next = &p;
		p.prev = del->prev;
		T ret = del->obj;
		delete del;
		return ret;
	}
	else{
		throw std::invalid_argument( "remove_before has first node as parameter" );
	}
  }
};

// output operator
template <typename T>
ostream& operator<<(ostream& out, const DLList<T>& dll){
	DLListNode<T>* temp = dll.first_node();
	while(temp != dll.after_last_node()){
		out << temp->obj << ", ";
		temp = temp->next;
	}
	return out;
}


#endif
