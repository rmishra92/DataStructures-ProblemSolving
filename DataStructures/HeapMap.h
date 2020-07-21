#pragma once
// this datastructure is a combination of heap+map datastructure and is used in finding
// single source shortest distance in Dijkstra algorithm for graph datastructure..It provides O(1) search to any node and 
// O(logn) extract minimum.

#include <unordered_map>
using namespace std;
struct HeapNode {
	int data;
	char code;
};
// Min heap with map datatsructure
class HeapMap {
private:
	int index = 0;
	HeapNode* elementArr[10];
	unordered_map<int, int> elementMap; // data mapped to where in array the data is present

	void HeapifyUp(int index) {
		int elemIndex = index;
		int parentIndex = (elemIndex - 1) / 2;
		while (parentIndex >= 0 && elementArr[parentIndex]->data > elementArr[elemIndex]->data) {
			//swap parent and child
			HeapNode* temp = elementArr[parentIndex];
			elementArr[parentIndex] = elementArr[elemIndex];
			elementMap[elementArr[elemIndex]->data] = parentIndex;
			elementArr[elemIndex] = temp;
			elementMap[temp->data] = elemIndex;

			// move element and parent to up
			elemIndex = parentIndex;
			parentIndex = (elemIndex - 1) / 2;
		}
	}

	void HeapifyDown() {
		int startIndex = 0;
		while ((2*startIndex+1) < index) { // if left child present
			int minIndex = 2 * startIndex + 1;
			if (((2 * startIndex + 2) < index) && elementArr[2 * startIndex + 2]->data < elementArr[minIndex]->data) {
				minIndex = (2 * startIndex + 2);
			}
			if (elementArr[startIndex]->data > elementArr[minIndex]->data) {
				HeapNode* temp = elementArr[startIndex];
				elementArr[startIndex] = elementArr[minIndex];
				elementMap[elementArr[minIndex]->data] = startIndex;
				elementArr[minIndex] = temp;
				elementMap[temp->data] = minIndex;

				startIndex = minIndex;
			}
			else {
				break;
			}
		}
	}

public:
	void insert(int data, char code) {
		HeapNode* node = new HeapNode();
		node->data = data;
		node->code = code;
		elementArr[index] = node;
		elementMap[data] = index;
		index++;
		HeapifyUp(index-1);
	}

	// finds a node present in the heap in O(1) time....
	HeapNode* find(int data) {
		if (elementMap.find(data) != elementMap.end()) {
			return elementArr[elementMap[data]];
		}
		return nullptr;
	 }

	// extracts and returns minimum node present in heap in O(logn) time
	HeapNode* extractMinimum() {
		HeapNode* returnVal = elementArr[0];
		elementMap.erase(elementArr[0]->data);
		elementArr[0] = elementArr[index - 1];
		elementMap[elementArr[index - 1]->data] = 0;
		index = index - 1;
		HeapifyDown();
		return returnVal;
	}
};
