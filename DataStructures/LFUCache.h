#pragma once

#include<unordered_map>
#include <algorithm>
#include <tuple>
using namespace std;

// get = O(n), put = O(n)..Not the best solution..
class LFUCache {
private:
	unordered_map<int, list<tuple<int, int, int>>::iterator> map;
	list<tuple<int, int, int>> vec; // pair = <counter, value, key> so sort will sort on counter first and if counter is same(frequency of use same) then sort on value which doesn't matter....
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

// get = O(1), put = O(1)..ideal solution
class LFUCacheEfficient {
private:
	unordered_map<int, list<int>> freq_keyList_Map;
	unordered_map<int, pair<int, int>> key_FreqValue_Map;
	unordered_map<int, list<int>::iterator> key_keyPtr_Map;
	int capacity;
	int currSize;
	int minFreq;

public:
	LFUCacheEfficient(int cap) {
		capacity = cap;
		currSize = 0;
		minFreq = 0;
	}

	int get(int key) {
		auto key_FreqVal = key_FreqValue_Map.find(key);
		if (key_FreqVal == key_FreqValue_Map.end()) {
			return -1;
		}
		auto freqValPair = key_FreqVal->second;
		int freq = freqValPair.first;
		int value = freqValPair.second;

		list<int>::iterator listElemePtr = key_keyPtr_Map[key];
		freq_keyList_Map[freq].erase(listElemePtr);
		if (freq_keyList_Map[freq].size() == 0 && minFreq == freq) { minFreq = freq + 1; }
		freq_keyList_Map[freq + 1].push_back(key);
		key_keyPtr_Map[key] = --freq_keyList_Map[freq + 1].end();
		key_FreqValue_Map.find(key)->second.first = freq + 1;

		return value;
	}

	void set(int key, int value) {
		if (capacity == 0) { return; }

		if (key_FreqValue_Map.find(key) != key_FreqValue_Map.end()) {
			int prevFreq = key_FreqValue_Map.find(key)->second.first;
			list<int>::iterator listElemePtr = key_keyPtr_Map[key];
			freq_keyList_Map[prevFreq].erase(listElemePtr);
			if (freq_keyList_Map[prevFreq].size() == 0 && minFreq == prevFreq) { minFreq = prevFreq + 1; }
			freq_keyList_Map[prevFreq + 1].push_back(key);
			key_keyPtr_Map[key] = --freq_keyList_Map[prevFreq + 1].end();
			key_FreqValue_Map[key].first = prevFreq + 1;
			key_FreqValue_Map[key].second = value;
			return;
		}

		if (currSize == capacity) {
			int key = freq_keyList_Map[minFreq].front();
			freq_keyList_Map[minFreq].pop_front();
			key_keyPtr_Map.erase(key);
			key_FreqValue_Map.erase(key);
			currSize--;
		}

		minFreq = 1;
		currSize++;
		freq_keyList_Map[1].push_back(key);
		key_FreqValue_Map[key].first = 1;
		key_FreqValue_Map[key].second = value;
		key_keyPtr_Map[key] = --freq_keyList_Map[1].end();
	}
};
