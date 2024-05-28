#include <stdio.h>
#include <stdlib.h>
#define MAX_N 20

struct pair{
	int index;
	int value;
};



// Function to merge two sorted subarrays arr[low .. mid] and arr[mid + 1 .. high] in place
void merge(pair *arr, int low, int mid, int high){
    int leftIndex = low; // Index for the start of the left subarray
    int rightIndex = mid + 1; // Index for the start of the right subarray

    // If the last element of the left subarray is less than or equal to the first element of the right subarray,
    // then the two subarrays are already sorted, and we don't need to do anything.
    if(arr[mid].value<=arr[rightIndex].value) return;

    while(leftIndex<=mid && rightIndex<=high){
        // If the element at the left index is less than or equal to the element at the right index,
        // we move to the next element in the left subarray.
        if(arr[leftIndex].value<=arr[rightIndex].value) leftIndex++;
        else{
            // Otherwise, we shift the elements in the right subarray to the right by one position,
            // and move the current element from the right subarray to its correct position in the left subarray.
            pair temp = arr[rightIndex];
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
void mergeSort(pair *arr, int n){
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



int *assignment(int A[][MAX_N], int n){
	pair matrix[n][n]; //to become a copy of A to sort each row
	int jobs[n]; //indexes used to refer to columns
	int *answer = (int*)malloc(sizeof(int)*n); //indexes refer to rows, values refer to columns
	
	for(int r=0;r<n;r++){ //+ (n^2)
		for(int c=0;c<n;c++){
			pair temp = {c, A[r][c]};
			matrix[r][c] = temp;
		}
	}
	
	for(int row_index=0; row_index<n; row_index++){ //+ (n^2)*(log n)
		jobs[row_index] = 0; //0 means job untaken, 1 means job taken
		mergeSort(matrix[row_index], n);
		pair temp = {row_index, matrix[row_index][0].value};
	}
	
	for(int i=0;i<n;i++){ //+ (n^2)
		pair *row = matrix[i];
		while(jobs[(*row).index])
			row++; //increment place in row until untaken job found
		jobs[(*row).index] = 1; //take the job
		answer[i] = (*row).index;
	}
	return answer;
	//the most significant degree is (n^2)(log n), thus O( (n^2)log n )
}
void printAssignments(int *answer, int n){
	for(int i=0;i<n;i++){
		printf("Person %d has been assigned:\tJob %d\n",i,answer[i]);
	}
	printf("\n\n");
}

// Driver program
int main(){
    int example1[3][MAX_N]={
		{5,9,1},
		{10,4,7},
		{3,2,6}
	};
	printAssignments(assignment(example1,3), 3);
	
	int example2[3][MAX_N]={
		{2,3,4},
		{4,5,6},
		{7,8,9}
	};
	printAssignments(assignment(example2,3), 3);
    return 0;
}
