#pragma once
#include <iostream>
using namespace std;

struct BstNode {
	int data;
	BstNode* left;
	BstNode* right;
};

// complexity for insert,search,delete operation is O(log(n)).
class BinarySerarhTree {
private:
	BstNode* root = nullptr;

	BstNode* getNewNode(int data) {
		BstNode* newNode = new BstNode();
		newNode->data = data;
		newNode->left = nullptr;
		newNode->right = nullptr;

		return newNode;
	}

	void insertRecursiveFunc(BstNode* &root, int data) {
		if (root == nullptr) {
			BstNode* newNode = getNewNode(data);
			root = newNode;
			return;
		}
		else if (data <= root->data) {
			insertRecursiveFunc(root->left, data);
		}
		else {
			insertRecursiveFunc(root->right, data);
		}
	}

	bool searchRecursiveFunc(BstNode*& root, int data) {
		if (root == nullptr) {
			return false;
		}
		else if (root->data == data) {
			return true;
		}
		else if (data <= root->data) {
			searchRecursiveFunc(root->left, data);
		}
		else {
			searchRecursiveFunc(root->right, data);
		}
	}

	void deleteRecFunc(BstNode*& root, int data) {
		if (root == nullptr) { return; }
		else if (data < root->data) { deleteRecFunc(root->left, data); }
		else if (data > root->data) { deleteRecFunc(root->right, data); }
		else {
			// 3 cases
			// 1. No child
			if (root->left == nullptr && root->right == nullptr) {
				delete(root); // now root is a dangling pointer, i.e, a pointer pointing to nothing...so..
				root = nullptr;
			}
			// 2. one child
			else if (root->left == nullptr) {
				BstNode* temp = root;
				root = root->right;
				delete(temp);				
			}
			else if (root->right == nullptr) {
				BstNode* temp = root;
				root = root->left;
				delete(temp);
			}
			// 3. two child
			else {
				// find minimum in right subtree, replace root with minimum and call delete(min) on right subtree....
				int min = findMin(root->right);
				root->data = min;
				deleteRecFunc(root->right, min);
			}
		}
	}

	int findMin(BstNode* root) {
		if (root == nullptr) { // tree is empty
			cout << "No elements in the tree." << endl;
			return 0;
		}
		else {
			BstNode* temp = root;
			while (temp->left != nullptr) {
				temp = temp->left;
			}
			return temp->data;
		}
	}

	int findMax(BstNode* root) {
		if (root == nullptr) {
			cout << "No element in the tree." << endl;
			return 0;
		}
		else {
			BstNode* temp = root;
			while (temp->right != nullptr) {
				temp = temp->right;
			}
			return temp->data;
		}
	}

	void printInOrderRec(BstNode* &root) {
		if (root == nullptr) { return; }
		else {
			printInOrderRec(root->left);
			cout << root->data << " ";
			printInOrderRec(root->right);
		}
	}

	void inOrderSuccessorFunc(BstNode* &root, int data) {
		BstNode* node = findElement(root, data); // find the node with data -> O(h)

	    // case 1 : if there is right child -> minimum in the right subtree is the successor..
		if (node->right != nullptr) {
			int successor = findMin(node->right);
			cout << "Successor : " << successor << endl;
		}
		// case 2 : if there is no right child -> deepest node for which this node is on the left is the successor..
		else {
			BstNode* ancestor = root;
			BstNode* successor = nullptr;
			while (ancestor != node) {
				if (node->data < ancestor->data) {
					successor = ancestor;
					ancestor = ancestor->left;
				}
				else {
					ancestor = ancestor->right;
				}
			}
			if (successor != nullptr) { cout << "Successor : " << successor->data << endl; } // if null then root is the only element in tree..
		}
	}

	void inOrderPredecessorFunc(BstNode*& root, int data) {
		BstNode* node = findElement(root, data);

		// case 1 : if there is left child -> maximum in the left subtree is the predecessor....
		if (node->left != nullptr) {
			int predecessor = findMax(node->left);
			cout << "Predecessor : " << predecessor << endl;
		}
		// case 2 : if no left child -> deepest node for which this node is on the right
		else {
			BstNode* predecessor = nullptr;
			BstNode* ancestor = root;
			// walk from root to the 'node' marking predecessor whenever we take right
			while (ancestor != node) {
				if (node->data < ancestor->data) {
					ancestor = ancestor->left;
				}
				else {
					predecessor = ancestor;
					ancestor = ancestor->right;
				}
			}
			if (predecessor != nullptr) { cout << "Predecessor : " << predecessor->data << endl; }
		}
	}

	BstNode* findElement(BstNode*& root, int data) {
		if (root == nullptr) {
			cout << "Element not found..";
			return NULL;
		}
		else {
			if (data < root->data) { return findElement(root->left, data); }
			else if (data > root->data) { return findElement(root->right, data); }
			else {
				return root;
			}
		}
	}

public:
	void insert(int data) {
		insertRecursiveFunc(root, data);

#pragma region Iterative insertion
		//if (root == nullptr) {
		//	BstNode* newNode = getNewNode(data);
		//	root = newNode;
		//	return;
		//}
		//else {
		//	BstNode* trail = nullptr; // keeps a track of node at which insertion is to be made on left/right.
		//	BstNode* temp = root;
		//	while (temp != nullptr) {
		//		trail = temp;
		//		if (data <= temp->data) {
		//			temp = temp->left;
		//		}
		//		else {
		//			temp = temp->right;
		//		}
		//	}
		//	temp = getNewNode(data);

		//	if (data <= trail->data)
		//	{
		//		trail->left = temp;
		//	}
		//	else {
		//		trail->right = temp;
		//	}
		//}  
#pragma endregion
	}

	bool search(int data) {
		return searchRecursiveFunc(root, data);
	}

	void deleteElement(int data) {
		deleteRecFunc(root, data);
	}

	int minimum() {
		return findMin(root);
	}

	int maximum() {
		return findMax(root);
	}

	void printInOrder() {
		printInOrderRec(root);
	}

	// Given a node element, find it's inorder successor, i.e, if you do an in-order traversal then find it's successor...
	//Solution 1 can be :- do an inorder traversal, store it in an array and give the next element to the element passed..T(n) = O(n)
	// Solution 2 (below) is a O(h) solution........
	void inOrderSuccessor(int data) {
		inOrderSuccessorFunc(root, data);
	}

	void inOrderPredecessor(int data) {
		inOrderPredecessorFunc(root, data);
	}
};