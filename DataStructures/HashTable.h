#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Object {
	string key;
	string value;
};

class HashTable {
private:
	int size = 5;
	Object** elements;

	void ensureCapacity() {
		// check if array is full
		bool isArrayFull = true;
		for (int i = 0; i < size; i++) {
			if (elements[i] == nullptr) {
				isArrayFull = false;
				break;
			}
		}

		// If array is full, create a new array of twice the size and copy the elements in old array there
		if (isArrayFull) {
			Object** temp = elements;
			elements = new Object * [size * 2]{nullptr};
			for (int i = 0; i < size; i++) {
				elements[i] = temp[i];
			}
			size = size * 2;
			delete(temp); // delete old array
		}
	}

	// generates the index of array based on key
	// algorithm can be anything - (no. of character - 1) in string for index or (sum of ASCII value of charcaters) mod (size of array), etc.
	int hashFunction(string key) {
		int index = key.size() - 1;
		return index;
	}

public:
	HashTable() {
		elements = new Object * [size] {nullptr};
	}
	// ------------- Open addressing based implementation of insert() and search() function -------------------
	// T(n) = O(1) in best case, O(n) in worst case
	void insert(string key, string value) {
		ensureCapacity();
		int index = hashFunction(key);
		Object* newNode = new Object();
		newNode->key = key;
		newNode->value = value;
		if (elements[index] == nullptr) {
			elements[index] = newNode;
		}
		else {
			// move circularly in array to fill all indexes upon collision
			int nextIndex = (index + 1) % size;
			while (elements[nextIndex] != nullptr) {
				nextIndex = (nextIndex + 1) % size;
			}
			elements[nextIndex] = newNode;
		}
	}

	//T(n) = O(1) in best case, O(n) in worst case
	Object* search(string key) {
		int index = hashFunction(key);
		Object* node = elements[index];
		if (node == nullptr) {
			cout << "Key not found." << endl;
			return nullptr;
		}
		else if (node->key == key) {
			return node;
		}
		else {
			int nextIndex = (index + 1) % size;
			while (elements[nextIndex] == nullptr || nextIndex != index && elements[nextIndex] != nullptr && elements[nextIndex]->key != key ) {
				nextIndex = (nextIndex + 1) % size;
			}

			if (nextIndex == index) {
				cout << "Key not found." << endl;
				return nullptr;
			}
			else {
				return elements[nextIndex];
			}
		}
	}
};
