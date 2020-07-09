#pragma once
#include <unordered_map>
using namespace std;

// DP - Table solution (since climb(1) = 1, climb(2) = 2, climb(3) = 3, climb(4) = 5, climb(5) = 8 is a fibonacci series)
int climbStairsTable(int n, int arr[], int size) {
	int* dpTable = new int[n + 1]{ 0 };
	dpTable[1] = 1;
	dpTable[2] = 2;
	for (int i = 3; i <= n; i++) {
		for (int j = 0; j < size; j++) {
			dpTable[i] += dpTable[i - arr[j]];
		}
	}
	return dpTable[n];
}

// DP - Memoized solution
unordered_map<int, int> SolMap;
int climbStairsMem(int n, int arr[], int size) {
	if (n == 0) { return 1; }
	if (SolMap.find(n) != SolMap.end()) {
		return SolMap[n];
	}
	int sln = 0;
	for (int i = 0; i < size; i++) {
		if (arr[i] <= n) {
			sln = sln + climbStairsMem(n - arr[i], arr, size);
		}
	}
	SolMap[n] = sln;
	return sln;
}

// plain recursive solution
int climbStairsRec(int n, int arr[], int size) {
	if (n == 0) { return 1; }
	int sln = 0;
	for (int i = 0; i < size; i++) {
		if (arr[i] <= n) {
			sln = sln + climbStairsRec(n - arr[i], arr, size);
		}
	}
	return sln;
}



int climbStairs(int n) {
	int arr[2] = { 1, 2 }; // steps that can be taken, i.e, one stair or two at a time..
	int size = 2;
	//return climbStairsRec(n, arr, size);
	return climbStairsMem(n, arr, size);
	//return climbStairsTable(n, arr, size);
}
