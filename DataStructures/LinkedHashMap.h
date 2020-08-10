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
