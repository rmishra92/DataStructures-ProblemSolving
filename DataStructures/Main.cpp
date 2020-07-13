// DataStructures.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "LinkedList.h"
#include "DoublyLinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include "BinarySearchTree.h"
#include "BinaryTree.h"
#include "Heap.h"
#include "HashTable.h"
#include "Trie.h"
#include "Graph.h"

using namespace std;

int main()
{
#pragma region LinkedList
//LinkedList* linkedList = new LinkedList();

// -----------------Insert at beginning------------------
//linkedList->insertAtBeginning(5);
//linkedList->insertAtBeginning(51);
//linkedList->insertAtBeginning(52);
//linkedList->print();

// ------------------Insert at end-----------------------
//linkedList->insertAtEnd(5);
//linkedList->insertAtEnd(51);
//linkedList->insertAtEnd(52);
//linkedList->printThruRecursion();
//cout << endl;
//linkedList->printReverseThruRecursion();


// -------------------Insert at an index position--------------
//linkedList->insertAtIndex(2, 1);
//linkedList->insertAtIndex(7, 2);
//linkedList->insertAtIndex(8, 3);
//linkedList->insertAtIndex(12, 1);
//linkedList->insertAtIndex(15, 5);
//linkedList->insertAtIndex(10, 3);
//linkedList->print();

// ---------------------Reverse a linked list - through iteration and recursion-------------
//linkedList->reverse();
//cout << endl;
//cout << "Reversed List : " << endl;
//linkedList->print();
//linkedList->revereseThruRecursion();
//cout << endl;
//cout << "Reversed List(thru recursion) : " << endl;
//linkedList->print();
//linkedList->revereseThruRecursion2();
//cout << endl;
//cout << "Reversed List(thru recursion2) : " << endl;
//linkedList->print();

// ---------------------Delete an element from an index position---------------------------
//linkedList->deleteAtIndex(1);
//cout << endl;
//linkedList->print();
//linkedList->deleteAtIndex(5);
//cout << endl;
//linkedList->print();
//linkedList->deleteAtIndex(2);
//cout << endl;
//linkedList->print();

//delete(linkedList);
#pragma endregion

#pragma region Doubly LinkedList
	//DoublyLinkedList* doublyLinkedList = new DoublyLinkedList();
	//doublyLinkedList->InsertAtIndex(5, 1);
	//doublyLinkedList->InsertAtIndex(7, 2);
	//doublyLinkedList->InsertAtIndex(8, 3);
	//doublyLinkedList->InsertAtIndex(10, 4);
	//doublyLinkedList->InsertAtIndex(9, 4);
	//doublyLinkedList->InsertAtIndex(12, 6);
	//doublyLinkedList->InsertAtIndex(15, 7);
	//doublyLinkedList->print();
	//cout << endl;

	//doublyLinkedList->deletAtIndex(1);
	//doublyLinkedList->deletAtIndex(6);
	//doublyLinkedList->deletAtIndex(3);
	//doublyLinkedList->print();
	//cout << endl;
	//cout << "Print Reverse:" << endl;
	//doublyLinkedList->printReverese();
#pragma endregion

#pragma region Stack- implementation using array and linked list
	//StackUsingArray* stack1 = new StackUsingArray(3);
	//stack1->pop(); // stack is empty at this point
	//stack1->push(1);
	//stack1->push(2);
	//stack1->push(3);
	//stack1->push(4); // stack is full at this point
	//cout << "Element on top is : " << stack1->top() << endl;
	//int retVal = stack1->pop();
	//cout << "Popped Value : " << retVal << endl;
	//cout << "Element on top is : " << stack1->top() << endl;
	//stack1->pop();
	//stack1->pop();
	//stack1->pop(); // stack is empty at this point
	//cout << endl;
	//delete(stack1);


	//StackUsingLinkedList* stack2 = new StackUsingLinkedList();
	//stack2->pop(); // stack is empty at this point
	//stack2->push(1);
	//stack2->push(2);
	//stack2->push(3);
	//cout << "Element on top is : " << stack2->top() << endl;
	//int retVal1 = stack2->pop();
	//cout << "Popped Value : " << retVal1 << endl;
	//cout << "Element on top is : " << stack2->top() << endl;
	//stack2->pop();
	//stack2->pop();
	//stack2->pop(); // stack is empty at this point

	//delete(stack2);  
#pragma endregion

#pragma region reverse linked list through stack
//LinkedList* list = new LinkedList();
//list->insertAtBeginning(2);
//list->insertAtBeginning(4);
//list->insertAtBeginning(6);
//list->insertAtBeginning(8);
//list->print();
//cout << endl;
//
//list->reverseUsingStack();
//cout << "Reversed stack : " << endl;
//list->print();  
#pragma endregion

#pragma region Queue - implementation using array and linked list

//QueueUsingArray* queue = new QueueUsingArray();
//queue->dequeue(); // queue is empty
//
//queue->enqueue(1);
//queue->enqueue(2);
//queue->enqueue(3);
//queue->enqueue(4);
//queue->enqueue(5);
//queue->enqueue(2); // queue is full here
//
//cout << "Front of queue : " << queue->peek() << endl;
//queue->dequeue();
//queue->enqueue(6);
//cout << "Front of queue : " << queue->peek() << endl;
//
//delete(queue);
//
//QueueUsingLinkedList* queue1 = new QueueUsingLinkedList();
//queue1->dequeue(); // queue is empty
//
//queue1->enqueue(1);
//queue1->enqueue(2);
//queue1->enqueue(3);
//queue1->enqueue(4);
//queue1->enqueue(5);
//
//cout << "Front of queue : " << queue1->peek() << endl;
//queue1->dequeue();
//queue1->enqueue(6);
//cout << "Front of queue : " << queue1->peek() << endl;
//
//delete(queue1);

#pragma endregion

#pragma region Binary Search Tree - insert/search/delete, min/maximum, *In-Order successor, In-Order predecessor*

//BinarySerarhTree* bst = new BinarySerarhTree();
//bst->insert(15); bst->insert(10); bst->insert(8); bst->insert(12); bst->insert(20);
//bst->insert(4); bst->insert(50); bst->insert(13); bst->insert(48); bst->insert(52);
//
//bst->printInOrder(); cout << endl;
//
//bool isElementFound = bst->search(12);
//cout << "Element(12) Found : " << isElementFound << endl;
//
//cout << "In-Order successor of element(12) : ";
//bst->inOrderSuccessor(12); cout << endl;
//
//cout << "In-Order successor of element(48) : ";
//bst->inOrderSuccessor(48); cout << endl;
//
//cout << "In-Order predecessor of element(10) : ";
//bst->inOrderPredecessor(10); cout << endl;
//
//cout << "In-Order predecessor of element(13) : ";
//bst->inOrderPredecessor(13); cout << endl;
//
//cout << "Minimum element in the BST is : " << bst->minimum() << endl;
//cout << "Maximum element in the BST is : " << bst->maximum() << endl;
//
//cout << "Delete Node(52) in BST : " << endl;
//bst->deleteElement(52); // delete node with no child..
//bst->printInOrder(); cout << endl;
//
//cout << "Delete Node(50) in BST : " << endl;
//bst->deleteElement(50); // delete node with one child..
//bst->printInOrder(); cout << endl;
//
//cout << "Delete Node(10) in BST : " << endl;
//bst->deleteElement(10); // delete node with two child..
//bst->printInOrder(); cout << endl;
//
//delete(bst);
#pragma endregion

#pragma region Binary Tree - Find height, Traversal(Level Order, Pre-Order, In-Order, Post-Order), IsBST

//BinaryTree* bt = new BinaryTree();
//bt->insert(15);bt->insert(10);bt->insert(8);bt->insert(12);bt->insert(20);bt->insert(4);bt->insert(50);bt->insert(2);bt->insert(1);
//
//cout << "Height of the binary tree is : " << bt->findHeight() << endl;
//
//cout << "Level Order Traversal : ";
//bt->levelOrderTraversal();
//cout << endl;
//
//cout << "Pre Order Traversal : ";
//bt->preOrderTraversal();
//cout << endl;
//
//cout << "In Order Traversal : ";
//bt->inOrderTraversal();
//cout << endl;
//
//cout << "Post Order Traversal : ";
//bt->postOrderTraversal();
//cout << endl;
//
//cout << "Is BST : " << bt->isBinarySearchTree() << endl;
//
//cout << "Is BST(by method 2) : " << bt->isBinarySearchTree2() << endl;
//
//delete(bt);

#pragma endregion

#pragma region Heap - Min Heap(implementation, add, peek, pop, print)
//MinHeap* minHeap = new MinHeap();
//minHeap->add(10);
//minHeap->add(15);
//minHeap->add(20);
//minHeap->add(17);
//minHeap->add(8);
//
//minHeap->print();
//cout << "Peek on Min Heap : " << minHeap->peek() << endl;
//minHeap->pop();
//minHeap->print();
//
//delete(minHeap);

// ---------------------- Heap Sort(descending order using min heap) --------------------
//cout << "Enter size of the array to sort : " << endl;
//int size = 0;
//cin >> size;
//int* arr = new int[size];
//for (int i = 0; i < size; i++) {
//	cout << "Enter element : ";
//	cin >> arr[i];
//	cout << endl;
//}
//
//int* retArray = sortDescending(arr, size);
//cout << "Sorted array in descending order : ";
//for (int i = 0; i < size; i++) {
//	cout << retArray[i] << " ";
//}
//cout << endl;
#pragma endregion

#pragma region Hash Table (implementation, insert & search -> open addressing & closed addressing)
// open addressing based implementation, i.e,
// on collision, find the next available spot in the array and store the element there....
//HashTable* dict = new HashTable();
//dict->insert("app", "apple");
//dict->insert("ba", "banana");
//dict->insert("ca", "camel");
//dict->insert("t", "toy");
//dict->insert("r", "rat"); // at this point array in hash table is full so next insert will resize it
//dict->insert("z", "zebra");
//
//Object* obj = dict->search("t");
//cout << "Key : " << obj->key << ", ";
//cout << "Value : " << obj->value << endl;
//
//Object* obj1 = dict->search("abc");
//if (obj1 != nullptr) {
//	cout << "Key : " << obj1->key << ", ";
//	cout << "Value : " << obj1->value << endl;
//}
//
//delete(dict);

// closed addressing, i.e, chaining based implementation, i.e,
//on collision, store element as next node in the linked list maintained at every index....
//HashTable* dict1 = new HashTable();
//dict1->insertChaining("app", "apple");
//dict1->insertChaining("ba", "banana");
//dict1->insertChaining("ca", "camel");
//dict1->insertChaining("t", "toy");
//dict1->insertChaining("r", "rat"); // at this point array in hash table is full so next insert will resize it
//dict1->insertChaining("z", "zebra");
//
//Object* obj2 = dict1->searchChaining("t");
//cout << "Key : " << obj2->key << ", ";
//cout << "Value : " << obj2->value << endl;
//
//Object* obj3 = dict1->searchChaining("abc");
//if (obj3 != nullptr) {
//	cout << "Key : " << obj3->key << ", ";
//	cout << "Value : " << obj3->value << endl;
//}
//
//delete(dict1);
#pragma endregion

#pragma region Trie - Insert, Search and Delete a word in dictionary in O(length of word)
//Trie* wordDictionary = new Trie();
//cout << "Enter number of words to configure in dictionary : " << endl;
//int count = 0;
//cin >> count;
//cout << "Enter 'X' to stop configuring : " << endl;
//string word = "";
//for (int i = 0; i < count; i++) {
//	cin >> word;
//	wordDictionary->insert(word);
//}
//
//cout << "Enter Word to search : " << endl;
//cout << "Enter 'X' to stop searching : " << endl;
//string searchWord = "";
//while (searchWord != "X") {
//	cin >> searchWord;
//	string outputMsg = wordDictionary->search(searchWord) == 1 ? "Valid Word" : "Invalid Word";
//	cout << outputMsg << endl;
//}
//
//wordDictionary->remove("RAB");
//wordDictionary->remove("RAM");
//
//delete(wordDictionary);
#pragma endregion

#pragma region Graph - Simple graph modelling a directed(A->B != B->A) social network....
//Graph* network = new Graph();
//// addVertex() mimics people joining the network
//network->addVertex('A');
//network->addVertex('B');
//network->addVertex('C');
//network->addVertex('D');
//network->addVertex('E');
//
//// addEdge() mimics follow request hence directed edges....
//// below graph represented a graph with negative edge weight(c->D) and,
//// contains a negative weight cycle, A->C->D->A (can be detected using Bellman Ford's shortest path algorithm)...To detect that uncomment addEdge('C', 'D', -3) below..
//network->addEdge('A', 'B', 1); // these are directed edges....
//network->addEdge('A', 'C', 1);
//network->addEdge('A', 'D', 1);
//network->addEdge('B', 'A', 2);
//network->addEdge('B', 'C', 2);
//network->addEdge('C', 'D', -1);
////network->addEdge('C', 'D', -3);
//network->addEdge('D', 'B', 5);
//network->addEdge('C', 'E', 4);
//network->addEdge('D', 'E', 3);
//network->addEdge('D', 'A', 1);
//
//cout << "Connected Vertex of A : "; network->printConnectedVertexOf('A'); cout << endl;
//cout << "Connected Vertex of B : "; network->printConnectedVertexOf('B'); cout << endl;
//cout << "Connected Vertex of C : "; network->printConnectedVertexOf('C'); cout << endl;
//cout << "Connected Vertex of D : "; network->printConnectedVertexOf('D'); cout << endl;
//
//cout << "Is Connected (A-D) : " << network->isConnected('A', 'D') << endl;
//cout << "Is Connected (A-F) : " << network->isConnected('A', 'F') << endl;
//cout << "Is Connected (Z-B) : " << network->isConnected('Z', 'B') << endl;
//
//cout << "Breadth First Traversal of network : ";
//network->breadthFirstTraversal(); cout << endl;
//
//cout << "Depth First Traversal of network : ";
//network->depthFirstTraversal(); cout << endl;
//
//cout << "Shortest path from (A-E) : ";
//int dist = network->getShortestPath('A', 'E');
//cout << "Total distance : " << dist << endl;
//
//delete(network);
#pragma endregion

}
