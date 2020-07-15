#pragma once

// implementation method - Adjacency List, i.e, node information is stored in a linked list
// 2 separate list maintains vertex and edge information. vertex_list stores vertex name
// and edge_list stores pointer to head node of all the connected vertex to a vertex in vertex_list at index i.
// i.e, vertex_list[i] = A then edge_list[i] = {B->C->D}, the connected vertex to vertex A.

#include<iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <stack>
using namespace std;

// name can be anything from A-Z, represents a person in the network....
struct Vertex {
	char name;
};

struct EdgeNode {
	Vertex* vertex; // pointer to a friend
	EdgeNode* next; // pointer to next edge node
	int weight;
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

	void dfsRec(Vertex* root, unordered_map<char, Vertex*>* &map) {
		map->emplace(root->name, root); // mark vertex as visited
		cout << root->name << " ";

		int vertexIndex = getIndex(root->name);
		EdgeNode* PtrConnections = edge_list[vertexIndex]; // get connections for a vertex
		while (PtrConnections != nullptr) {
			if (map->find(PtrConnections->vertex->name) == map->end()) { // if vertex has not been visited
				dfsRec(PtrConnections->vertex, map);
			}
			PtrConnections = PtrConnections->next;
		}
	}

	// for (u,v) edge, if distance[v] > distance[u] + weight[(u,v)] then update parent and distance maps....
	bool relax(char edgeStart, EdgeNode* edgeEnd, unordered_map<char, int>& distanceMap, unordered_map<char, char>& parentMap) {
		if (distanceMap[edgeEnd->vertex->name] > distanceMap[edgeStart] + edgeEnd->weight) {
			distanceMap[edgeEnd->vertex->name] = distanceMap[edgeStart] + edgeEnd->weight;
			parentMap[edgeEnd->vertex->name] = edgeStart;
			return true; // true if this combination result in a better solution..
		}
		return false; // false if this combination is not optimal...
	}

	int getShortestPathByBellmanFord(char source, char destination) {
		unordered_map<char, int> distanceMap; // stores minimum distance of each vertex from source vertex
		unordered_map<char, char> parentMap; // stores parent for each vertex for minimum distance from source

		distanceMap.emplace(source, 0); // set distance of source from source is zero
		for (int i = 0; i < MaxSize; i++) { // update distance of each vertex from source to INT_MAX
			Vertex* vertexPtr = vertex_list[i];
			if (vertexPtr != nullptr && vertexPtr->name != source) {
				distanceMap.emplace(vertexPtr->name, INT_MAX);
			}
		}

		for (int i = 0; i < MaxSize; i++) { // set parent of each vertex as empty
			Vertex* vertexPtr = vertex_list[i];
			if (vertexPtr != nullptr) {
				parentMap.emplace(vertexPtr->name, ' ');
			}
		}

		for (int i = 0; i < (MaxSize - 1); i++) { // outer loop for (v-1) cycles
			// visit all edges in each cycle
			for (int j = 0; j < MaxSize; j++) { // loops through edge list, this for-loop visits all the edges in graph
				EdgeNode* edgeNodePtr = edge_list[j];
				while (edgeNodePtr != nullptr) { // loops through each connection of a vertex
					relax(vertex_list[j]->name, edgeNodePtr, distanceMap, parentMap);
					edgeNodePtr = edgeNodePtr->next;
				}
			}
		}

		// After (v-1) cycles, relaxation should have no impact..if it still relaxes then there is a negative weight cycle in graph....
		// visit one more time through all edges to determine negative cycle in graph -- Bellman Ford alg strength..
		for (int k = 0; k < MaxSize; k++) {
			EdgeNode* edgePtr = edge_list[k];
			while (edgePtr != nullptr) {
				bool canFindOptimalSolution = relax(vertex_list[k]->name, edgePtr, distanceMap, parentMap);
				if (canFindOptimalSolution) {
					cout << "A negative weight cycle exists in the graph." << endl;
					return 0;
				}
				edgePtr = edgePtr->next;
			}
		}

		// print the shortest path from source-destination
		char ptr = destination;
		while (ptr != source) {
			cout << ptr << "<-";
			ptr = parentMap[ptr];
		}
		cout << ptr << endl; // loop will reach source at this point..

		return distanceMap[destination]; // after (v-1) iteration, this will store the minimum distance to reach destination from source....

	}

	char findMin(unordered_map<char,int> &list) { // a priority queue can be used here to reduce finding minimum to O(logn) from O(n)
		int min = INT_MAX;
		char minkey = ' ';
		for (pair<char, int> i : list) {
			if (i.second < min)
			{
				min = i.second;
				minkey = i.first;
			}
		}
		return minkey;
	}

	// Idealy, T(n) = O((|e|+|v|)log(|v|)) when a heap+map DS gives a O(1) access to vertex and log|v| for extract min but currently it is |v| for extract min because of implementation....
	//S(n) = O(|v|) for storing all vertex in distance map or parent map
	//Djikstra is a greedy algorithm - picks minimum distance vertex from 'heapMap'(see below) and relaxes it's neighbours and continues this process...
	int getShortestPathByDijkstra(char source, char destination) {
		unordered_map<char, int> distanceMap; // stores minimum distance of each vertex from source vertex
		unordered_map<char, char> parentMap; // stores parent for each vertex for minimum distance from source

		unordered_map<char, int> heapMap; // DS to mimick a (heap + map) DS that provides O(1) access and O(logn) extract minimum element..
		heapMap.emplace(source, 0); // set distance of source from source is zero
		for (int i = 0; i < MaxSize; i++) { // update distance of each vertex from source to INT_MAX
			Vertex* vertexPtr = vertex_list[i];
			if (vertexPtr != nullptr && vertexPtr->name != source) {
				heapMap.emplace(vertexPtr->name, INT_MAX);
			}
		}

		for (int i = 0; i < MaxSize; i++) { // set parent of each vertex as empty
			Vertex* vertexPtr = vertex_list[i];
			if (vertexPtr != nullptr) {
				parentMap.emplace(vertexPtr->name, ' ');
			}
		}

		while (!heapMap.empty()) {
			char minKey = findMin(heapMap); // ideally O(log|v|) when priority queue/heap is in place but now O(|V|) because it is linear search..
			EdgeNode* connection = edge_list[getIndex(minKey)];
			while (connection != nullptr) {
				if (heapMap.find(connection->vertex->name) != heapMap.end() && heapMap[connection->vertex->name] > heapMap[minKey] + connection->weight) {
					heapMap[connection->vertex->name] = heapMap[minKey] + connection->weight;
					parentMap[connection->vertex->name] = minKey;
				}
				connection = connection->next;
			}
			distanceMap.emplace(minKey, heapMap[minKey]);
			heapMap.erase(minKey);
		}

		// print the shortest path from source-destination
		char ptr = destination;
		while (ptr != source) {
			cout << ptr << "<-";
			ptr = parentMap[ptr];
		}
		cout << ptr << endl; // loop will reach source at this point..

		return distanceMap[destination]; 
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
	void addEdge(char start, char end, int weight = 0) {
		int indexOfStart = getIndex(start); // gets index of start vertex in the vertex_list
		int indexOfEnd = getIndex(end);
		Vertex* vertexPtrEnd = vertex_list[indexOfEnd];

		EdgeNode* head = edge_list[indexOfStart]; // head of linked list storing connected vertices

		EdgeNode* edgeNode = new EdgeNode();
		edgeNode->vertex = vertexPtrEnd;
		edgeNode->next = head;
		edgeNode->weight = weight;
		head = edgeNode; // change head to point to new edge node

		edge_list[indexOfStart] = head; // updating new head in the edge_list
	}

	// T(n) = O(|v|) in the worst case when one vertex is friends of all other vertices...
	void printConnectedVertexOf(char name) {
		int index = getIndex(name);

		if (vertex_list[index] != nullptr && vertex_list[index]->name == name) {// first check to ensure vertex exists in the graph....
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

	// performs a breadth first traversal, starts from first node in the vertex_list....
	// T(n) = O(|v| + |e|); In worst case, when edges are much more than vertices(i.e, connected graph), |e| term will dominate and 
	// complexity will be O(|e|) or, |e| ~ |v|^2 hence, O(|v| * |v|)
	// for sparse graph with |v| >>> |e|, |v| will dominate and T(n) = O(|v|)....
	// S(n) = O(| v | ) - stores all element in the graph
	void breadthFirstTraversal() {
		queue<Vertex*>* q = new queue<Vertex*>(); // queue to perform BFS
		unordered_map<char, Vertex*>* ht = new unordered_map<char, Vertex*>(); // map to store visited vertices
		q->push(vertex_list[0]); // insert first node in vertex
		ht->emplace(vertex_list[0]->name, vertex_list[0]); // mark vertex_list[0] as visited by placing it in map....

		while (!q->empty()) {
			Vertex* vertex = q->front();
			q->pop();
			cout << vertex->name << " ";
			int vertexIndex = getIndex(vertex->name); // at this index in edge_list, connected vertex(i.e, vertex at length 1) is present..
			EdgeNode* head = edge_list[vertexIndex];
			while (head != nullptr) {
				if (ht->find(head->vertex->name) == ht->end()) { // vertex not visited so insert in map....
					q->push(head->vertex);
					ht->emplace(head->vertex->name, head->vertex);
				}
				head = head->next;
			}
		}
	}

	// performs a depth first traversal, starts from first node in the vertex_list. In depth first, we go as deep as we can for a vertex and then backtrack if no path exists from a vertex.
	// if graph = 0 -> 1, 0 -> 2, 1 -> 2, 2 -> 0, 2 -> 3, 3 -> 3, DFS from vertex 1 : 1 2 0 3
	// Algorithm : Visit a node, go to it's connections and backtrack if no connection or all connections are visited already..Repeat from start..
	// 2 ways : a) backtracking using recusrion b) backtracking using stack
	// T(n) = O(|v| + |e|);
	// S(n) = O(| v |) - stores all element in the graph
	void depthFirstTraversal() {
		Vertex* root = vertex_list[0]; // we start DFS from this node
		unordered_map<char, Vertex*>* map = new unordered_map<char, Vertex*>();
		// backtracking using recursion......
		//dfsRec(root, map);

		// backtracking using stack........
		stack<Vertex*>* s = new stack<Vertex*>();
		s->push(root);
		map->emplace(root->name, root);
		cout << root->name << " ";

		while (!s->empty()) {
			root = s->top();
			EdgeNode* connectionsPtr = edge_list[getIndex(root->name)];
			
			while (connectionsPtr != nullptr && map->find(connectionsPtr->vertex->name) != map->end()) {
				connectionsPtr = connectionsPtr->next;
			}

			if (connectionsPtr != nullptr) {
				s->push(connectionsPtr->vertex);
				map->emplace(connectionsPtr->vertex->name, connectionsPtr->vertex);
				cout << connectionsPtr->vertex->name << " ";
			}
			else {
				s->pop();
			}
		}
	}

	// Single Source Shortest Path problem : finds the shortest path from a source to all vertices by different graph algorithms
	// returns shortest path distance and prints the path....
	// 1. Bellman-Ford : T(n) = O(|v| * |e|), visit all edges (|v| - 1) times and relax. Can detect negative cycle but costly compared to other algs.
	// 2. Djikstra : T(n) = O((|e|+|v|) * log(|v|)), doesn't work if graph has negative weight edges but better for non-negative edges containing graph....
	int getShortestPath(char source, char destination) {
		//int result = getShortestPathByBellmanFord(source, destination);

		int result = getShortestPathByDijkstra(source, destination);
		return result;
	}
};