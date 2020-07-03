#pragma once
#include <vector>
using namespace std;

int searchRecFunc(vector<int>& nums, int startIndex, int endIndex, int target) {
    if (startIndex >= endIndex) {
        if (target > nums[startIndex]) {
            return startIndex + 1;
        }
        else {
            return startIndex;
        }
    }

    int mid = (startIndex + endIndex) / 2;
    if (target == nums[mid]) {
        return mid;
    }
    else if (target > nums[mid]) {
        int sI = mid + 1;
        return searchRecFunc(nums, sI, endIndex, target);
    }
    else {
        int eI = mid - 1;
        return searchRecFunc(nums, startIndex, eI, target);
    }

}

// ----Problem : search for an element in a sorted array. If found, return the index or else return index at which element has to be inserted-----------
int searchInsert(vector<int>& nums, int target) {
    if (nums.size() == 0) { // empty array
        return 0;
    }

#pragma region recursive solution
    //int retVal = searchRecFunc(nums, 0, nums.size() - 1, target);
//return retVal;  
#pragma endregion


    int startIndex = 0;
    int endIndex = nums.size() - 1;
    while (startIndex < endIndex) {
        int mid = (startIndex + endIndex) / 2;
        if (target == nums[mid]) {
            return mid;
        }
        else if (target > nums[mid]) {
            startIndex = mid + 1;
        }
        else {
            endIndex = mid - 1;
        }
    }

    if (target > nums[startIndex]) {
        return startIndex + 1;
    }
    else {
        return startIndex;
    }
}