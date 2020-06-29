#pragma once
#include <iostream>
using namespace std;

class QueueUsingArray {
private:
	const static int MAX_SIZE = 5;
	int members[MAX_SIZE]; // this array is utilized in a circular fashion to maximize it's space usage..
	int front = -1;
	int rear = -1;

public:
	void enqueue(int x) {
		if (front == -1 && rear == -1) {
			front = rear = 0;
			members[rear] = x;
		}
		else if ((rear + 1) % MAX_SIZE == front) {
			cout << "Queue is full." << endl;
		}
		else {
			rear = (rear + 1) % MAX_SIZE;
			members[rear] = x;
		}
	}

	void dequeue() {
		if (front == -1 && rear == -1) {
			cout << "Queue is empty." << endl;
		}
		else if (front == rear) {
			front = -1;
			rear = -1;
		}
		else {
			front = (front + 1) % MAX_SIZE;
		}
	}

	int peek() {
		return members[front];
	}
};

// Queue implemented using array have following limitations :
// 1. lots of space unused at any time
// 2. queue can be full and following insertion will take O(n) time.
class QueueUsingLinkedList {
private:
	Node* front = nullptr;
	Node* rear = nullptr;

public:
	void enqueue(int x) {
		Node* temp = new Node();
		temp->data = x;
		temp->next = nullptr;
		if (front == nullptr && rear == nullptr) {
			front = rear = temp;
		}
		else {
			rear->next = temp;
			rear = temp;
		}
	}

	void dequeue() {
		if (front == nullptr && rear == nullptr) {
			cout << "Queue is empty." << endl;
		}
		else if (front == rear) {
			Node* temp = front;
			front = rear = nullptr;
			delete(temp); // free up the space in the memory

		}
		else {
			Node* temp = front;
			front = front->next;
			delete(temp); // free up the space in the memory
		}
	}

	int peek() {
		return front->data;
	}
};
