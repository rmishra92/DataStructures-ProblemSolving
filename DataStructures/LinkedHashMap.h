#pragma once
#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;

class LRUCache {
private :
	list<int> lst;
	// <key, pair<value, key itertaor>>
	unordered_map<int, pair<int, list<int>::iterator>> map;
	int capacity;

	void use(unordered_map<int, pair<int, list<int>::iterator>>::iterator &it) {
		lst.erase(it->second.second);
		lst.push_front(it->first);
		it->second.second = lst.begin(); // iterator to list<int> element set in map..
	}

public:
	LRUCache(int cap) {
		capacity = cap;
	}

	int get(int key) {
		unordered_map<int, pair<int, list<int>::iterator>>::iterator item = map.find(key);
		// if key doesn't exists, return -1
		if (item == map.end()) {
			return -1;
		}
		// if key exists, return value and update the queue with most recently used
		use(item);
		return item->second.first;
	}

	void set(int key, int value) {
		unordered_map<int, pair<int, list<int>::iterator>>::iterator item = map.find(key);
		// if key exists, update the value and list
		if (item != map.end()) {
			use(item);
			map[key] = { value, lst.begin() };
			return;
		}

		// if key doesn't exists
		// ensure capacity by purging LRU element(exists at the end of list) and then insert
		if (lst.size() == capacity) {
			map.erase(lst.back());
			lst.pop_back();
		}

		lst.push_front(key);
		map.insert({ key, {value, lst.begin()} });

	}
};

// Same implementation of LRU cache without STL and using Doubly Linked List to maintain the recent object list....
class LRUCache2 {
private:
	unordered_map<int, NodeDoubly*> map;
	NodeDoubly* head; // a doubly linked list storing the order of elements.
	NodeDoubly* tail;
	int capacity = 0;
	int currSize = 0;

	NodeDoubly* use(NodeDoubly* nodePtr, int data) {
		// delete the node at the pointer, insert at head of linked list and return the newPtr..
		deleteNode(nodePtr);

		NodeDoubly* newNode = insertAtHead(data);
		return newNode;
	}

	NodeDoubly* insertAtHead(int data) {
		NodeDoubly* newNode = new NodeDoubly();
		newNode->data = data;
		newNode->next = head;
		if (head == nullptr) {
			head = newNode;
			tail = newNode;
		}
		else {
			head->prev = newNode;
			head = newNode;
		}
		return head;
	}

	void deleteNode(NodeDoubly* nodePtr) {
		if (nodePtr == nullptr) { return; }
		if (nodePtr == head && nodePtr == tail) {
			head = tail = nullptr;
		}
		else if (nodePtr == head) {
			head = head->next;
			head->prev = nullptr;
		}
		else if (nodePtr == tail) {
			tail = tail->prev;
			tail->next = nullptr;
		}
		else {
			NodeDoubly* prev = nodePtr->prev;
			NodeDoubly* next = nodePtr->next;
			prev->next = next;
			next->prev = prev;
		}
		delete nodePtr;
	}

public:
	LRUCache2(int cap) {
		capacity = cap;
	}

	void set(int data) {
		unordered_map<int, NodeDoubly*>::iterator item = map.find(data);

		if (item != map.end()) { // key exists, element is being updated(deleted from current position and inserted at head)
			NodeDoubly* newPtr = use(item->second, data);
			item->second = newPtr;
			return;
		}

		if (currSize == capacity) {
			NodeDoubly* tailElement = tail;
			tail = tail->prev;
			map.erase(tailElement->data); // data is stored as key in map and also in doubly linked list..
			delete(tailElement);
			currSize--;
		}
		NodeDoubly* newNode = insertAtHead(data);
		map.insert({ data,newNode });
		currSize++;
	}

	int get(int key) {
		auto item = map.find(key);
		if (item == map.end()) {
			return -1;
		}
		item->second = use(item->second, item->first);
		return item->first;
	}
};
