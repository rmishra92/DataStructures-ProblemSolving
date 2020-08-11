#pragma once

#include<unordered_map>
#include <algorithm>
#include <tuple>
using namespace std;

class LFUCache {
private:
	unordered_map<int, list<tuple<int, int, int>>::iterator> map;
	list<tuple<int, int, int>> vec; // pair = <counter, value> so sort will sort on counter first and if counter is same(frequency of use same) then sort on value which doesn't matter....
	int capacity = 0;

	void use(list<tuple<int, int, int>>::iterator& it, int value) {
		auto listElemPtr = it;
		std::get<0>(*it)++;
		std::get<1>(*it) = value;
		//it->first++; // increase counter
		//it->second = value; // update value
		int startCounter = std::get<0>(*it); //it->first;
		// this leads to O(n) time complexity...
		while (it != vec.begin() && std::get<0>(*it) <= startCounter) {
			it--;
		}
		if (it == vec.begin() && std::get<0>(*it) <= startCounter) {
			vec.push_front(*listElemPtr);
			it = vec.begin();
		}
		else {
			vec.insert(++it, *listElemPtr);
			it--;
		}
		vec.erase(listElemPtr);
	}

public:
	LFUCache(int cap) {
		capacity = cap;
	}

	void put(int key, int value) {
		if (capacity == 0) { return; }
		auto item = map.find(key);
		if (item != map.end()) {
			use(item->second, value); // update the element in the list and also the iterator in the map
			return;
		}

		// ensure capacity
		if (capacity == vec.size()) {
			map.erase(std::get<2>(vec.back())); // vector.pair 2nd value is the key in the map also..
			vec.pop_back();
		}
		vec.push_back(make_tuple(1, value, key));
		map[key] = --vec.end(); // pointer to last element in the list..
		use(map[key], value);
	}

	int get(int key) {
		auto item = map.find(key);
		if (item == map.end()) {
			return -1;
		}
		use(item->second, std::get<1>(*(item->second)));
		return std::get<1>(*(item->second));
	}
}; 
