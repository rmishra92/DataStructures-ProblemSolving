#pragma once
#include <iostream>
using namespace std;

// Heap exists either as Min/Max heap. In Min heap, root is larger than the children and this property is true for all nodes in the tree..
// operation : Peek(gives the first element in the heap - max element in max heap/ min element in min heap),
//             Pop(deletes the first element from the heap(max/min whether it is max/min heap),
//             Add(inserts and element in to heap).
// Note : Heap is filled top->bottom and then left->right so array implementation is easier.
// left child = 2 * index + 1, right child = 2 * index + 1, parent = (index - 2) / 2

// Note :- for storing "k-best" element in a list, min-heap can be useful. Insert the new element and then pop. Pop will pop the worst element in the list
// leaving the k-best element at this stage....

class MinHeap {
private:
	int MAX_SIZE = 10;
	int arrIndex = 0;
	int* elements = new int[MAX_SIZE];

	void ensureCapacity() {
		if (arrIndex == MAX_SIZE) {
			int* temp = elements;
			elements = new int[MAX_SIZE * 2];
			MAX_SIZE *= 2;
			copyArrayElements(temp, elements, arrIndex);
			delete(temp);
		}
	}

	void copyArrayElements(int* temp, int* elements, int index) {
		for (int i = 0; i < index; i++) {
			elements[i] = temp[i];
		}
	}

	void swap(int &num1, int &num2) {
		int temp = num1;
		num1 = num2;
		num2 = temp;
	}

	bool hasParent(int index) {
		int subFactor = index % 2 == 0 ? 2 : 1;
		if (((index - subFactor) / 2) >= 0) {
			return true;
		}
		else {
			return false;
		}
	}

	bool hasLeftChild(int index) {
		return getLeftChildIndex(index) < arrIndex && elements[getLeftChildIndex(index)] != 0;
	}

	bool hasRightChild(int index) {
		return getRightChildIndex(index) < arrIndex && elements[getRightChildIndex(index)] != 0;
	}

	int getParentIndex(int index) {
		int subFactor = index % 2 == 0 ? 2 : 1;
		int parentIndex = (index - subFactor) / 2;
		return parentIndex;
	}

	int getLeftChildIndex(int index) {
		return (2 * index + 1);
	}

	int getRightChildIndex(int index) {
		return (2 * index + 2);
	}

	// T(n) = O(log(n))
	void heapifyUp() {
		int ptr = arrIndex - 1; // index of last insert
		while (hasParent(ptr) && elements[getParentIndex(ptr)] > elements[ptr]) { // if parent is present and larger than ptr
			swap(elements[getParentIndex(ptr)], elements[ptr]);
			ptr = getParentIndex(ptr);
		}
	}

	// T(n) = O(log(n))
	void heapifyDown() {

		int ptr = 0;
		while (hasLeftChild(ptr)) { // if left child is present
			int smallerChildIndex = getLeftChildIndex(ptr);
			if (hasRightChild(ptr) && (elements[getRightChildIndex(ptr)] < elements[getLeftChildIndex(ptr)])) { // if right child present and smaller than left
				smallerChildIndex = getRightChildIndex(ptr);
			}

			if (elements[ptr] > elements[smallerChildIndex]) {
				swap(elements[smallerChildIndex], elements[ptr]);
				ptr = smallerChildIndex;
			}
			else {
				break;
			}
		}
	}

public:
	void add(int data) {
		ensureCapacity(); // increase the size of array to twice if heap is full or else do nothing.
		elements[arrIndex] = data;
		arrIndex++;
		heapifyUp();
	}

	int peek() {
		return elements[0];
	}

	void pop() {
		elements[0] = elements[arrIndex - 1];
		arrIndex--;
		heapifyDown();
	}

	void print() {
		for (int i = 0; i < arrIndex; i++) {
			cout << elements[i] << " ";
		}
		cout << endl;
	}

	friend int* sortDescending(int* arr, int size);
};

// Steps : Since in a MinHeap, smallest number is always on top of heap. so, swap it with last element in array
// reduce index and heapifyDown() rest of the array to get the smallest on top again.
// Repeat above until index > 1.
int* sortDescending(int* arr, int size) {
	MinHeap* minheap = new MinHeap();
	// create a min heap from the array, T(n) = O(nlog(n))
	for (int i = 0; i < size; i++) {
		minheap->add(arr[i]);
	}

	// T(n) = O(nlog(n))
	while (minheap->arrIndex > 0) {
		minheap->swap(minheap->elements[0], minheap->elements[minheap->arrIndex - 1]);
		minheap->arrIndex--;
		minheap->heapifyDown();
	}

	int* retArray = minheap->elements;
	delete(minheap);

	return retArray;
}
