#pragma once

#include <iostream>
using namespace std;

struct NodeDoubly {
	int data;
	NodeDoubly* prev;
	NodeDoubly* next;
};

class DoublyLinkedList {
private:
	NodeDoubly* head = nullptr;

public:
	void InsertAtIndex(int data, int index) {
		if (index <= 0) { return; }
		NodeDoubly* newNode = new NodeDoubly();
		newNode->data = data;
		if (index == 1) {
			newNode->prev = nullptr;
			newNode->next = head;
			if (head != nullptr) { head->prev = newNode; }
			head = newNode;
		}
		else {
			NodeDoubly* prevPtr = head; // pointer to element after which new node to enter.
			while (index > 2) {
				prevPtr = prevPtr->next;
				index--;
			}
			NodeDoubly* nextPtr = prevPtr->next;
			prevPtr->next = newNode;
			newNode->prev = prevPtr;
			if (nextPtr != nullptr) {
				newNode->next = nextPtr;
				nextPtr->prev = newNode;
			}
		}
	}

	void deletAtIndex(int index) {
		if (index <= 0) { return; }
		else if (index == 1) {
			NodeDoubly* temp = head;
			head = head->next;
			temp->next = nullptr;
			if (head != nullptr) { head->prev = nullptr; }
			delete(temp);
		}
		else {
			NodeDoubly* deletePtr = head; // pointer to element to be deleted.
			while (index > 1)
			{
				deletePtr = deletePtr->next;
				index--;
			}
			NodeDoubly* prevPtr = deletePtr->prev;
			NodeDoubly* nextPtr = deletePtr->next;
			prevPtr->next = nextPtr;
			if (nextPtr != nullptr) { nextPtr->prev = prevPtr; }
			delete(deletePtr);
		}
	}

	void print() {
		NodeDoubly* temp = head;
		while (temp != nullptr) {
			cout << temp->data << " ";
			temp = temp->next;
		}
	}

	void printReverese()
	{
		if (head == nullptr) { return; }
		NodeDoubly* temp = head;
		while (temp->next != nullptr) {
			temp = temp->next;// reach the end node in linked list
		}

		while (temp != nullptr) {
			cout << temp->data << " ";
			temp = temp->prev; // print opposite - from end to start
		}
	}
};
