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

	bool removeRecFunc(string& word, TrieNode* root, int index = 0) {
		if (root->map.find(word[index]) == root->map.end()) { // char of word not found in map, i.e, word doesn't exists..
			return false;
		}
		else if (index == word.size() - 1) {
			// get the node after last character in word
			TrieNode* temp = root->map.at(word[index]);
			// if this word has continuation word after this character, e.g, RAM in trie and also RAMEN
			// then mark the temp's endOfWord = false....
			if (temp->map.size() != 0) {
				temp->endOfWord = false;
			}
			else { // no continuation word, erase from the map of last char node and delete the temp node....
				root->map.erase(word[index]);
				delete(temp);
			}
			
			return root->map.size() == 0;
		}
		else {
			TrieNode* temp = root->map.at(word[index]);
			bool shouldDeleteMapping = removeRecFunc(word, temp, index + 1);

			if (shouldDeleteMapping) {
				root->map.erase(word[index]);
				delete(temp);
			}
			return root->map.size() == 0;
		}
	}

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

	// T(n) = O(n), n is size of word
	void remove(string word) {
		TrieNode* temp = root;
		
		removeRecFunc(word, temp);
	}
};