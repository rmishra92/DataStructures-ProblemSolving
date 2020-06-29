#pragma once
#include <iostream>
using namespace std;

class StackUsingArray {
private:
	int* elements = nullptr;
	int index = -1; // points to the last element on top..
	int stackSize = 5; // default size of stack

	bool isStackFull() {
		if ((index + 1) == stackSize) {
			return true;
		}
		return false;
	}

	bool isStackEmpty() {
		if (index == -1) {
			return true;
		}
		return false;
	}

public:
	StackUsingArray() {
		elements = new int[stackSize]; // create array with default size..
	}

	StackUsingArray(int size) {
		stackSize = size;
		elements = new int[stackSize];
	}

	void push(int data) {
		if (isStackFull()) { cout << "Stack is full." << endl; return; }
		index++;
		elements[index] = data;
	}

	int pop() {
		if (isStackEmpty()) { cout << "Stack is empty" << endl; return -1; }
		int returnVal = elements[index];
		index--;
		return returnVal;
	}

	int top() {
		return elements[index];
	}
};

// size determination is not required at the start....
class StackUsingLinkedList {
private:
	Node* head = nullptr;
	void insertAtBeginning(int data) {
		Node* newNode = new Node();
		newNode->data = data;
		newNode->next = head;
		head = newNode;
	}
public:
	void push(int data) {
		insertAtBeginning(data);
	}

	int pop() {
		if(head == nullptr) { cout << "Stack is empty" << endl; return -1; }
		Node* retNode = head;
		head = head->next;
		int retVal = retNode->data;
		// cleanup node from the memory
		retNode->next = nullptr;
		delete(retNode);

		return retVal;
	}

	int top() {
		return head->data;
	}
};
