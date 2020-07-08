#pragma once

// implementation method - Adjacency List, i.e, node information is stored in a linked list
// 2 separate list maintains vertex and edge information. vertex_list stores vertex name
// and edge_list stores pointer to head node of all the connected vertex to a vertex in vertex_list at index i.
// i.e, vertex_list[i] = A then edge_list[i] = {B->C->D}, the connected vertex to vertex A.

#include<iostream>
#include <string>
using namespace std;

// name can be anything from A-Z, represents a person in the network....
struct Vertex {
	char name;
};

struct EdgeNode {
	Vertex* vertex; // pointer to a friend
	EdgeNode* next; // pointer to next edge node
};

class Graph {
private:
	int MaxSize = 26; // for 26 letters from A-Z
	Vertex** vertex_list; // stores vertex information for a person in a network..
	EdgeNode** edge_list; // stores pointer to a linked list containing all the friends of person.

	// generates a unique index for storing a vertex by it's name
	// simple hash function that generates a unique index in the array of size 'n'....
	int getIndex(char name) {
		int index = (name - 'A') % MaxSize; // so A = 0, B = 1, C = 2, D = 3, E = 4, etc..
		return index;
	}

	void updateEdgeList(int index, char vertex) {
		int indexOfVertex = getIndex(vertex);
		Vertex* v = vertex_list[indexOfVertex];

		EdgeNode* head = edge_list[index]; // head of linked list storing connected vertices

		EdgeNode* edgeNode = new EdgeNode();
		edgeNode->vertex = v;
		edgeNode->next = head;
		head = edgeNode; // change head to point to new edge node

		edge_list[index] = head; // updating new head in the edge_list
	}

public:
	Graph() {
		vertex_list = new Vertex * [MaxSize] {nullptr};
		edge_list = new EdgeNode * [MaxSize] {nullptr};
	}

	// adds a vertex to the graph,i.e, adds a person to the network
	// T(n) = O(1) because we just need to add a new vertex in the vertex list....
	void addVertex(char name) {
		Vertex* v = new Vertex();
		v->name = name;
		int index = getIndex(name);
		vertex_list[index] = v;
	}

	// adds an edge between start and end vertex, i.e, start becoming friend of end. Entry of connection is not vice-versa, i.e, it is a directed graph....
	// T(n) = O(1) because of insert at head of linked list
	void addEdge(char start, char end) {
		int indexOfStart = getIndex(start); // gets index of start vertex in the vertex_list
		int indexOfEnd = getIndex(end);
		Vertex* vertexPtrEnd = vertex_list[indexOfEnd];

		EdgeNode* head = edge_list[indexOfStart]; // head of linked list storing connected vertices

		EdgeNode* edgeNode = new EdgeNode();
		edgeNode->vertex = vertexPtrEnd;
		edgeNode->next = head;
		head = edgeNode; // change head to point to new edge node

		edge_list[indexOfStart] = head; // updating new head in the edge_list
	}

	// T(n) = O(|v|) in the worst case when one vertex is friends of all other vertices...
	void printConnectedVertexOf(char name) {
		int index = getIndex(name);

		if (vertex_list[index]->name == name) {
			EdgeNode* ptrToHead = edge_list[index];
			while (ptrToHead != nullptr) {
				cout << ptrToHead->vertex->name << ",";
				ptrToHead = ptrToHead->next;
			}
			cout << endl;
		}
		else {
			// given vertex is not part of network
			cout << "Vertex not part of network." << endl;
		}
	}

	// whether vertex 'first' is connected to vertex 'second'....
	// T(n) = O(|v|) in worst case when one vertex is friends of all other vertices...
	bool isConnected(char first, char second) {
		int firstIndex = getIndex(first);
		bool isConnected = false;
		if (vertex_list[firstIndex] != nullptr && vertex_list[firstIndex]->name == first) {
			EdgeNode* head = edge_list[firstIndex];
			while (head != nullptr) {
				if (head->vertex->name == second) {
					isConnected = true;
					break;
				}
				head = head->next;
			}
		}
		return isConnected;
	}
};