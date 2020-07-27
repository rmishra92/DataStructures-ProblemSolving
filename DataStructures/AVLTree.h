#pragma once
#include <iostream>

using namespace std;
// An AVL Tree is a self-balancing BST that ensures a log(n) time insert/delete/search/min/max operation even on skewed binary tree. A normal BST may have a O(n) complexity
// in case the tree is skewed. Trick is to balance the tree through rotations upon every insert/delete.

struct AVLNode {
	AVLNode* left;
	AVLNode* right;
	int data;
	int height;
};
class AVLTree {
private:
	AVLNode* root = nullptr;

	AVLNode* getNewNode(int data) {
		AVLNode* newNode = new AVLNode();
		newNode->data = data;
		newNode->height = 0; // height is set during node creation.
		newNode->left = nullptr;
		newNode->right = nullptr;
		return newNode;
	}

	void printInOrderRec(AVLNode* root) {
		if (root == nullptr) { return; }
		printInOrderRec(root->left);
		cout << root->data << " ";
		printInOrderRec(root->right);
	}

	int max(int a, int b) {
		return a >= b ? a : b;
	}

	int height(AVLNode* node) {
		if (node == nullptr) {
			return -1;
		}
		return node->height;
	}

	// T(n) = O(1); tells whether a tree is left-heavy(balance > 0) or right-heavy(balance < 0)
	int balance(AVLNode* node) {
		return height(node->left) - height(node->right);
	}

	// T(n) = O(1) ; only pointers are adjusted
	AVLNode* leftRotate(AVLNode* node) {
		AVLNode* x = node->right;
		AVLNode* y = x->left;

		// perform rotate
		x->left = node;
		node->right = y;

		node->height = 1 + max(height(node->left), height(node->right));
		x->height = 1 + max(height(x->left), height(x->right));

		return x;
	}
	// T(n) = O(1) ; only pointers are adjusted
	AVLNode* rightRotate(AVLNode* node) {
		AVLNode* x = node->left;
		AVLNode* y = x->right;

		x->right = node;
		node->left = y;

		node->height = 1 + max(height(node->left), height(node->right));
		x->height = 1 + max(height(x->left), height(x->right));

		return x;
	}

	AVLNode* findMin(AVLNode* node) {
		if (node->left == nullptr) {
			return node;
		}
		return findMin(node->left);
	}

	// inserting an element in AVL tree augments the normal BST insert with few rotations..
	// T(n) = O(logn) because additional steps like rotate(), height(), balance() is O(1).
	AVLNode* insertRecursive(AVLNode* root, int data) {
		if (root == nullptr) {
			root = getNewNode(data);
			return root;
		}

		if (data <= root->data) {
			root->left = insertRecursive(root->left, data);
		}
		else if (data > root->data) {
			root->right = insertRecursive(root->right, data);
		}

		// update height of ancestors
		root->height = 1 + max(height(root->left), height(root->right));

		// rotate tree in case of imbalance - a situation where [height(left subtree) - height(right subtree) > 1/< -1]
		if (balance(root) > 1 && data <= root->left->data) {
			root = rightRotate(root);
		}
		else if (balance(root) > 1 && data > root->left->data) {
			root->left = leftRotate(root->left);
			root = rightRotate(root);
		}
		else if (balance(root) < -1 && data > root->right->data) {
			root = leftRotate(root);
		}
		else if(balance(root) < -1 && data <= root->right->data) {
			root->right = rightRotate(root->right);
			root = leftRotate(root);
		}

		return root;
	}

	// deleting an element from an AVL tree augments the normal BST delete with few rotations..
	// T(n) = O(logn) because additional steps is of O(1) time....
	AVLNode* deleteNodeRecursive(AVLNode* root, int data) {
		if (root == nullptr) { return root; } // no data found in the tree

		if (data < root->data) {
			root->left = deleteNodeRecursive(root->left, data);
		}
		else if (data > root->data) {
			root->right = deleteNodeRecursive(root->right, data);
		}
		else { // data found
			AVLNode* temp = root;
			//1. No child
			if (root->left == nullptr && root->right == nullptr) {
				root = nullptr;
			}
			// 2. One Child
			else if (root->left == nullptr) {
				root = root->right;
			}
			else if (root->right == nullptr) {
				root = root->left;
			}

			// 3. Both child
			else {
				AVLNode* minOnRight = findMin(root->right); // find the minimum element in right subtree
				root->data = minOnRight->data; // copy min element's data to root
				deleteNodeRecursive(root->right, minOnRight->data); // call delete on minimum node in the right
			}

			delete(temp); // free-up memory taken by temp..
			return root;
		}

		// update height on ancestors
		root->height = 1 + max(height(root->left), height(root->right));

		// rotate in case of imbalance in the tree
		if (balance(root) > 1 && balance(root->left) >= 0) { // if root is left-heavy and it's left is also left-heavy
			root = rightRotate(root);
		}
		else if (balance(root) > 1 && balance(root->left) < 0) { // if root is left-heavy and it's left is right-heavy
			root->left = leftRotate(root->left);
			root = rightRotate(root);
		}
		else if (balance(root) < -1 && balance(root->right) <= 0) { // if root is right-heavy and it's right is also right-heavy
			root = leftRotate(root);
		}
		else if (balance(root) < -1 && balance(root->right) > 0) { // if root is right-heavy and it's right is left-heavy
			root->right = rightRotate(root->right);
			root = leftRotate(root);
		}

		return root;
	}


public:
	void insert(int data) {
		// perform normal BST recursive insert
		// update height of ancestors and check for imbalance
		// rotate accordingly to restore balance in the tree
		root = insertRecursive(root, data);
	}

	void deleteNode(int data) {
		// perform normal BST recursive delete
		// update height of ancestors and check for imbalance
		// rotate accordingly to restore balance in the tree
		root = deleteNodeRecursive(root, data);
	}

	void printInOrder() {
		printInOrderRec(root);
	}
};
