#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

#include <utility>

#include <initializer_list>
// Do not add any #include statements here.  If you have a convincing need for adding a different `#include` please post in the forum on KEATS.

// TODO your code goes here:
template <typename T>
class LinkedList{
private:
	Node<T>* head;
	Node<T>* tail;
	int count;
public:
	LinkedList()
:head(nullptr),tail(nullptr),count(0){
	}

	void push_front(T content){
		Node<T>*newNode = new Node<T>(content);
		if (count == 0){
			head = newNode;
			tail = newNode;
		}
		else if (count == 1){
			head = newNode;
			newNode->next = tail;
			tail->previous = newNode;
		}
		else {
			newNode->next = head;
			head->previous = newNode;
			head = newNode;
		}
		count++;
	}

	T & front(){
		return head->data;
	}
	void push_back(T content){
		Node<T>* newNode = new Node<T>(content);
		if (count == 0){
			head = newNode;
			tail = newNode;
		}
		else if (count == 1){
			tail = newNode;
			tail->previous = head;
			head->next = newNode;
		}
		else {
			newNode->previous = tail;
			tail->next = newNode;
			tail = newNode;
		}
		count++;
	}
	T & back(){
		return tail->data;
	}
	int size() const{
		return count;
	}
	NodeIterator<T> begin() const{
		return NodeIterator<T>(head);
	}
	NodeIterator<T> end() const{
		return NodeIterator<T>(nullptr);
	}
	~LinkedList(){
		Node <T>* current = head;
		for (int i = 0; i < count; ++i){
			Node <T>* next = current->next;
			delete current;
			current = next;
		}

	}
	void reverse(){
		Node <T>* current = head;
		head = tail;
		tail = current;
		for (int i = 0; i < count; ++i){
			Node <T>* next = current->next;
			current->next = current->previous;
			current->previous = next;
			current = next;
		}
	}
	LinkedList(std::initializer_list<T> elements):head(nullptr),tail(nullptr),count(0){
		for(T t : elements){
			push_back(t);
		}
	}
	NodeIterator<T> insert(NodeIterator<T> itr, int data){
		Node <T>* current = itr.getCurrent();
		Node <T>* previous = current->previous;
		if (current == head){
			push_front(data);
			NodeIterator<T> itrTwo = NodeIterator<T>(head);
			return itrTwo;
		}
		Node <T>* newNode = new Node<T>(data);
		current->previous = newNode;
		previous->next = newNode;
		newNode->next = current;
		newNode->previous = previous;
		NodeIterator<T> itrTwo = NodeIterator<T>(newNode);
		++count;
		return itrTwo;
	}
	NodeIterator<T> erase(NodeIterator<T> itr){
		if (count == 0){
			NodeIterator<T> itrTwo = NodeIterator<T>(nullptr);
			return itrTwo;
		}
		Node <T>* current = itr.getCurrent();
		Node <T>* previous = current->previous;
		Node <T>* next = current->next;
		if (count == 1){
			head = nullptr;
			tail = nullptr;
		}
		else if (head == current){
			head = next;
			head->previous = nullptr;
		}
		else if (tail == current){
			tail = previous;
			tail->next = nullptr;
		}
		else{
			previous->next = next;
			next->previous = previous;
		}
		delete current;
		NodeIterator<T> itrTwo = NodeIterator<T>(next);
		--count;
		return itrTwo;
	}

};



// do not edit below this line

#endif
