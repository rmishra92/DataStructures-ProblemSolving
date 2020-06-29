#pragma once
#include <iostream>
#include <stack>
using namespace std;

struct Node
{
public:
	int data;
	Node* next;
};

class LinkedList {
private:
	Node* head = nullptr;

	void reverseRecursionFunc(Node* ptr1, Node* ptr2, Node* ptr3) {
		if (ptr1 == nullptr) { return; }
		ptr2 = ptr1;
		ptr1 = ptr1->next;
		ptr2->next = ptr3;
		ptr3 = ptr2;
		head = ptr2;
		reverseRecursionFunc(ptr1, ptr2, ptr3);
	}

	void reverseRecursionFunc2(Node* p)
	{
		if (p->next == nullptr)
		{
			head = p;
			return;
		}
		reverseRecursionFunc2(p->next);
		Node* temp = p->next;
		temp->next = p;
		p->next = nullptr;
	}

	void printRec(Node* node) {
		if (node == nullptr) { return; }

		cout << node->data << " ";
		printRec(node->next);
	}

	void printRecReverse(Node* node) {
		if (node == nullptr) { return; }

		printRecReverse(node->next);
		cout << node->data << " ";
	}

public:
	void insertAtBeginning(int x) {
		Node* temp = new Node();
		temp->data = x;
		temp->next = head;
		head = temp;
	}

	void insertAtEnd(int x) {
		Node* temp = new Node();
		temp->data = x;
		temp->next = nullptr;
		if (head == nullptr) { head = temp; }
		else {
			Node* ptr = head;
			while (ptr->next != nullptr) {
				ptr = ptr->next;
			}
			ptr->next = temp;
		}
	}

	void insertAtIndex(int x, int index) {
		if (index <= 0) { return; }
		Node* newNode = new Node();
		newNode->data = x;
		if (index == 1) {
			newNode->next = head;
			head = newNode;
			return;
		}
		Node* posPtr = head;
		while (index > 2) {
			posPtr = posPtr->next;
			index--;
		}
		newNode->next = posPtr->next;
		posPtr->next = newNode;
	}

	void deleteAtIndex(int index) {
		if (index <= 0) { return; }
		Node* ptr1 = nullptr;
		Node* ptr2 = head;
		if (index == 1) { head = ptr2->next; delete(ptr2); return; }
		while (index > 1)
		{
			ptr1 = ptr2;
			ptr2 = ptr2->next;
			index--;
		}
		ptr1->next = ptr2->next;
		delete(ptr2); // free up space taken by the deleted node.
	}

	void reverse() {
			Node* ptr1 = head;
			Node* ptr2 = nullptr;
			Node* ptr3 = nullptr;
			while (ptr1 != nullptr) {
				ptr2 = ptr1;
				ptr1 = ptr1->next;
				ptr2->next = ptr3;
				ptr3 = ptr2;
				head = ptr2;
			}
	}

	void revereseThruRecursion() {
			Node* ptr1 = head;
			Node* ptr2 = nullptr;
			Node* ptr3 = nullptr;
			reverseRecursionFunc(ptr1, ptr2, ptr3);
	}

	// this function uses recursion in a better way to reverse the linked list....
	void revereseThruRecursion2() {
		if (head == nullptr) { return; }
		Node* temp = head;
		reverseRecursionFunc2(temp);
	}

	void reverseUsingStack() {
		Node* temp = head;
		stack<Node*> stack; // stack implementation used from STL function in '#include <stack>'
		while (temp != nullptr) {
			stack.push(temp);
			temp = temp->next;
		}

		head = stack.top();
		temp = stack.top();
		stack.pop();
		while (!stack.empty()) {
			temp->next = stack.top();
			stack.pop();
			temp = temp->next;
		}
		temp->next = nullptr;
	}

	void print() { // more efficient than recursive implementation of normal print
		Node* temp = head;
		while (temp != nullptr) {
			cout << temp->data << " ";
			temp = temp->next;
		}
	}

	void printThruRecursion()
	{
		Node* temp = head;
		printRec(temp);
	}

	void printReverseThruRecursion()
	{
		Node* temp = head;
		printRecReverse(temp);
	}
};

