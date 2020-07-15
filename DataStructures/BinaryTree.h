#pragma once
#include "BinarySearchTree.h"
#include <queue>

// not a binary search tree..
class BinaryTree {
private:
	BstNode* root = nullptr;

	BstNode* getNewNode(int data) {
		BstNode* newNode = new BstNode();
		newNode->data = data;
		newNode->left = nullptr;
		newNode->right = nullptr;

		return newNode;
	}

	int findHeightRecursiveFunc(BstNode* &root) {
		if (root == nullptr) {
			return -1;
		}
		else {
			return { 1 + maximum(findHeightRecursiveFunc(root->left), findHeightRecursiveFunc(root->right)) };
		}
	}

	int maximum(int num1, int num2) {
		if (num1 >= num2) {
			return num1;
		}
		else {
			return num2;
		}
	}

	void preOrderTraversalRecFunc(BstNode*& root) {
		if (root == nullptr) { return; }
		cout << root->data << " ";
		preOrderTraversalRecFunc(root->left);
		preOrderTraversalRecFunc(root->right);
	}

	void inOrderTraversalRecFunc(BstNode*& root) {
		if (root == nullptr) { return; }
		inOrderTraversalRecFunc(root->left);
		cout << root->data << " ";
		inOrderTraversalRecFunc(root->right);
	}

	void postOrderTraversalRecFunc(BstNode*& root) {
		if (root == nullptr) { return; }
		postOrderTraversalRecFunc(root->left);
		postOrderTraversalRecFunc(root->right);
		cout << root->data << " ";
	}

	bool isBSTRecFunc(BstNode* &root) {
		if (root == nullptr) { return true; }
		else {
			return isSubtreeSmallerOrEqual(root->left, root->data) &&
				isSubtreeLarger(root->right, root->data) &&
				isBSTRecFunc(root->left) &&
				isBSTRecFunc(root->right);
		}
	}

	bool isSubtreeSmallerOrEqual(BstNode*& root, int data) {
		if (root == nullptr) { return true; }
		else {
			return (root->data <= data) && isSubtreeSmallerOrEqual(root->left, data) && isSubtreeSmallerOrEqual(root->right, data);
		}
	}

	bool isSubtreeLarger(BstNode*& root, int data) {
		if (root == nullptr) { return true; }
		else {
			return (root->data > data) && isSubtreeLarger(root->left, data) && isSubtreeLarger(root->right, data);
		}
	}

	// above 2 function[isSubtreeSmallerOrEqual(), isSubtreeLarger()] can be reduced to a comparison if we know the range of any node value...
	bool isBSTRecFuncSmarter(BstNode* root, int minRange, int maxRange) {
		if (root == nullptr) { return true; }
		else {
			return (root->data >= minRange) && (root->data < maxRange) && isBSTRecFuncSmarter(root->left, minRange, root->data) 
				&& isBSTRecFuncSmarter(root->right, root->data, maxRange);
		}
	}

	void fillElementsInOrder(BstNode* root, int* elements, int& index) {
		if (root == nullptr) { return; }
		else {
			fillElementsInOrder(root->left, elements, index);
			elements[index] = root->data;
			index++;
			fillElementsInOrder(root->right, elements, index);
		}
	}

	bool traverseInOrderAndCompare(BstNode* root, int minRange, int maxRange) {
		if (root == nullptr) { return true; }
		else {
			bool nodeValueInRange = (root->data >= minRange) && (root->data < maxRange);
			bool isLeftSubTreeNodeInRange = traverseInOrderAndCompare(root->left, minRange, root->data);
			bool isRightSubTreeInRange = traverseInOrderAndCompare(root->right, root->data, maxRange);
			return nodeValueInRange && isLeftSubTreeNodeInRange && isRightSubTreeInRange;
		}
	}

	// whether an element is present in a binary tree, T(n) = O(n)
	bool isPresent(BstNode* root, int a) {
		if (root == nullptr) { return false; }
		if (root->data == a) { return true; }
		return isPresent(root->left, a) || isPresent(root->right, a);
	}

#pragma region Lowest Commn Ancestor in binary tree - not in BST
	bool isBothInTree(int p, int q, BstNode* root) {
		return isPresent(root, p) && isPresent(root, q);
	}

	// T(n) = O(nlog(n))
	BstNode* findLCA(BstNode* root, int p, int q) {
		if (root->data == p || root->data == q) {
			return root;
		}

		if (isBothInTree(p, q, root->left)) {
			return findLCA(root->left, p, q);
		}
		else if (isBothInTree(p, q, root->right)) {
			return findLCA(root->right, p, q);
		}
		return root;
	}

	// T(n) = O(n)
	BstNode* findLCAFast(BstNode* root, int p, int q) {
		if (root == nullptr) { return nullptr; }
		if (root->data == p || root->data == q) {
			return root;
		}
		BstNode* left = findLCAFast(root->left, p, q);
		BstNode* right = findLCAFast(root->right, p, q);
		if (left != nullptr && right != nullptr) { return root; }
		else if (left == nullptr && right == nullptr) { return nullptr; }
		else {
			return left != nullptr ? left : right;
		}
	}
#pragma endregion


public:
	int findHeight() {
		return findHeightRecursiveFunc(root);
	}

	// insertion is like BST insertion because element in binary tree can be inserted in any way until children for a root is atmost 2....
	void insert(int data) {
		if (root == nullptr) {
			BstNode* newNode = getNewNode(data);
			root = newNode;
			return;
		}
		else {
			BstNode* trail = nullptr; // keeps a track of node at which insertion is to be made on left/right.
			BstNode* temp = root;
			while (temp != nullptr) {
				trail = temp;
				if (data <= temp->data) {
					temp = temp->left;
				}
				else {
					temp = temp->right;
				}
			}
			temp = getNewNode(data);

			if (data <= trail->data)
			{
				trail->left = temp;
			}
			else {
				trail->right = temp;
			}
		}
	}

#pragma region Binary Tree Traversal -> BFS(Level Order), DFS(Pre-Order, In-Order, Post-Order)
	// If 'n' is no. of nodes in the tree, time complexity = O(n), space complexity = O(1) - best, O(n) - worst
	void levelOrderTraversal() {
		if (root == nullptr) { // tree is empty
			cout << "tree is empty." << endl;
			return;
		}
		queue<BstNode*>* q = new queue<BstNode*>();
		BstNode* temp = root;
		q->push(temp);

		while (!q->empty()) {
			BstNode* nodePtr = q->front();
			cout << nodePtr->data << " ";
			if (nodePtr->left != nullptr) { q->push(nodePtr->left); }
			if (nodePtr->right != nullptr) { q->push(nodePtr->right); }
			q->pop();
		}
		cout << endl;
		delete(q);
	}

	void preOrderTraversal() {
		preOrderTraversalRecFunc(root);
	}

	void inOrderTraversal() {
		inOrderTraversalRecFunc(root);
	}

	void postOrderTraversal() {
		postOrderTraversalRecFunc(root);
	}
#pragma endregion

	// uses recursion to fins whether a binary tree is BST or not.
	bool isBinarySearchTree() {
#pragma region Solution 1
		// T(n) = O(n^2)
		//return isBSTRecFunc(root);  
#pragma endregion

#pragma region Solution 2
		// T(n) = O(n), space complexity = O(1) -----> best solution <-----
		return isBSTRecFuncSmarter(root, INT_MIN, INT_MAX);
#pragma endregion

	}

	bool isBinarySearchTree2() {
#pragma region Solution 1
		// stores in-order traversal of binary tree in an array and checks if array is increasing. If yes, it is a BST(in-order traversal of a BST gives a sorted list)..
		// T(n) = O(2n) = O(n), space complexity = O(n)

		//int* elements = new int[100];

		//BstNode* temp = root;
		//int index = 0;
		//if (root == nullptr) { return true; }
		//else {
		//	fillElementsInOrder(root, elements, index); // store in-order traversal of binary tree in an array
		//}

		//// loop through the array and check if it is increasing..
		//for (int i = 1; i < index; i++) {
		//	if (elements[i - 1] > elements[i]) {
		//		return false;
		//	}
		//}
		//return true;  
#pragma endregion

#pragma region Solution 2
		// while traversing in-order, pass the range for the node value.
		// time complexity = O(n), space complexity = O(1)...no need to store traversal in an array..
		return traverseInOrderAndCompare(root, INT_MIN, INT_MAX);
#pragma endregion
	}

	// Finding lowest common ancestor of two nodes in a binary tree..
	// Note : this solution is not for LCA in case of BST.
	BstNode* lowestCommonAncestor(int p, int q) {
		return findLCA(root, p, q); // T)n) = O(nlog(n))
		//return findLCAFast(root, p, q); // T(n) = O(n)
	}
};
