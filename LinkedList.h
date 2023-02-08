#pragma once
#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include "LinkedListInterface.h"

using namespace std;

template <typename T> 
class LinkedList: public LinkedListInterface<T>
{
private:
	struct Node {
		Node(T _value) {
			value = _value;
			next = NULL;
			}
		T value;
		Node* next;
	};
Node *head;
int numItems = 0;

public:

	LinkedList() {
		head = NULL;
	};
	 ~LinkedList() {
		 clear();
	 };

bool checkDupe(T insertionNode) {
	Node* curr = head;
	while(curr != NULL) {
		if (insertionNode == curr->value) {
			return true;
		}
		curr = curr->next;
	}
	return false;
}

 void insertHead(T value) {
	 if (checkDupe(value)) {
		 return;
	 }
	 Node *tmp = new Node(value);
	 tmp->next = head;
	 head = tmp;
	 numItems++;
	}

	void insertTail(T value) {
		if(checkDupe(value)) {
			return;
		}
		if (size() == 0) {
			insertHead(value);
			return;
		}
		else {
			Node* p = head;
			while (p->next != NULL) {
				p = p->next;
			}
			p->next = new Node(value);
		}
		numItems++;
	}
	
	 void insertAfter(T value, T insertionNode) {
		 if (checkDupe(value)) {
			 return;
		 }
		 if(!checkDupe(insertionNode)) {
			 return;
		 }
		 Node *scout = head;
		 while (scout->value != insertionNode) {
			 scout = scout->next;
		 }
		 Node *new_node = new Node(value);
		 new_node->value = value;
		 new_node->next = scout->next;
		 scout->next = new_node;

		 numItems++;
	}

	void remove(T value) {
		if (head == NULL) {
			return;
		}

		if (head->value == value) {
			Node *tmp = head;
			head = head->next;
			delete tmp;
			numItems--;
		}

		if (head == NULL) {
			return;
		}

		Node *current = head->next;
		Node *previous = head;
		while (current != NULL) {
			if (current->value == value) {
				previous->next = current->next;
				delete current;
				numItems--;
				return;
			}
			current = current->next;
			previous = previous->next;
		}
	}

	void clear() {
		while (head != NULL) {
			remove(head->value);
		}
		numItems = 0;
	}

	T at(int index) {
		Node *tempPointer = head;
		if ((index >= 0) && (index < size())) {
			for (int i = 0; i <= index; i++) {
				if (i == index) {
					return (tempPointer->value);
				}
				else {
					tempPointer = tempPointer->next;
				}
			}
		}
		throw out_of_range("Error: Out of Range");
	}

	int size() {
		return numItems;
	} 

	string toString() {
		stringstream ss;
		Node *current = head;
		while (current != NULL) {
			if (current->next != NULL) {
				ss << current->value << " ";
			}
			else {
				ss << current->value;
			}
				current = current->next;
		}
		return ss.str();		
	}
};
