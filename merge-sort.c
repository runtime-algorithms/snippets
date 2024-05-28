#include <stdio.h>
//geeks for geeks copy paste

// Function to merge two sorted subarrays arr[low .. mid] and arr[mid + 1 .. high] in place
void merge(int arr[], int low, int mid, int high){
    int leftIndex = low; // Index for the start of the left subarray
    int rightIndex = mid + 1; // Index for the start of the right subarray

    // If the last element of the left subarray is less than or equal to the first element of the right subarray,
    // then the two subarrays are already sorted, and we don't need to do anything.
    if(arr[mid]<=arr[rightIndex]) return;

    while(leftIndex<=mid && rightIndex<=high){
        // If the element at the left index is less than or equal to the element at the right index,
        // we move to the next element in the left subarray.
        if(arr[leftIndex]<=arr[rightIndex]) leftIndex++;
        else{
            // Otherwise, we shift the elements in the right subarray to the right by one position,
            // and move the current element from the right subarray to its correct position in the left subarray.
            int temp = arr[rightIndex];
            for (int i = rightIndex; i > leftIndex; i--)
                arr[i] = arr[i - 1];
            arr[leftIndex] = temp;

            // Increment all relevant indices.
            leftIndex++;
            mid++;
            rightIndex++;
        }
    }
}

// Function to perform an iterative bottom-up mergesort
void mergeSort(int arr[], int n){
    int currSize;  // Current size of subarrays to be merged
    int leftStart; // Starting index of left subarray

    // Merge subarrays in bottom-up manner. First merge subarrays of size 1,
    // then merge subarrays of size 2, then merge subarrays of size 4, and so on.
    for(currSize=1; currSize<=n-1; currSize*=2){
        // Pick starting point of different subarrays of current size
        for(leftStart=0; leftStart<n-1; leftStart+=2*currSize){
            int mid = leftStart + currSize - 1; // Find ending index of left subarray
            int rightEnd = (leftStart+2*currSize-1<n-1)? leftStart+2*currSize-1: n-1; // Find ending index of right subarray

            // Merge subarrays arr[leftStart .. mid] and arr[mid + 1 .. rightEnd] in place
            merge(arr, leftStart, mid, rightEnd);
        }
    }
}

// Function to print an array
void printArray(int arr[], int n){
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

// Driver program
int main(){
    int arr[] = {12, 11, 13, 5, 6, 7, 9, 81, 56, 77, 1, -2, 3, 6, 99, 86, 789, 65};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: \n");
    printArray(arr, n);

    mergeSort(arr, n);

    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}
