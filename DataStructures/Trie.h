#pragma once
#include <iostream>
#include <unordered_map>
using namespace std;

struct TrieNode {
	unordered_map<char, TrieNode*> map;
	bool endOfWord = false;
};

// very useful data structure for "word validation" related tasks..
// This DS is also used for spell-checking in O(1) time by moving to next node as soon as char is entered..
class Trie {
private:
	TrieNode* root;

public:
	Trie() {
		root = new TrieNode();
	}

	// T(n) = O(n), n = size of word
	void insert(string word) {
		TrieNode* temp = root;
		for (int i = 0; i < word.size(); i++) {
			auto el = temp->map.find(word[i]); // O(1), since it is a find in hash map..
			if (el == temp->map.end()) { // key is not found in the map
			    TrieNode* newNode = new TrieNode();
				temp->map.emplace(word[i],newNode);
			}
			temp = temp->map.at(word[i]); // O(1)
		}
		temp->endOfWord = true; // after word is inserted, endOfWord is set to true....
	}

	// T(n) = O(n), n is size of word
	bool search(string word) {
		TrieNode* temp = root;
		for (int i = 0; i < word.size(); i++) {
			if (temp->map.find(word[i]) == temp->map.end()) { // char not found
				return false;
			}
			temp = temp->map.at(word[i]);
		}
		return temp->endOfWord; // if leaf node is endOfWord then return true or else false...
	}
};