#include <iostream>
#include "MaxHeap.h"
#include "MaxPriorityQueue.h"

using namespace std;

MaxPriorityQueue * initMaxPQ (int A[], int numElements) {
	MaxPriorityQueue *q=new MaxPriorityQueue;
	q->heap=initMaxHeapFromArray(A,numElements);
	buildMaxHeap(q->heap);
	return q;
}


int maximumPQ (MaxPriorityQueue * maxPQ) {
	if(isEmptyMaxHeap(maxPQ->heap)) return -1;
	return maxPQ->heap->A[1];
}


int extractMaximumPQ (MaxPriorityQueue * maxPQ) {
	if(isEmptyMaxHeap(maxPQ->heap)) return -1;
	return deleteMaxHeap(maxPQ->heap,1);
}


void insertMaxPQ (MaxPriorityQueue * maxPQ, int priority) {
	insertMaxHeap(maxPQ->heap,priority);
}


void increasePriority (MaxPriorityQueue * maxPQ, int i, int newPriority) {
	if(i>maxPQ->heap->size || maxPQ->heap->A[i]>=newPriority) return;
	maxPQ->heap->A[i]=newPriority;
	while(i>1&&maxPQ->heap->A[i/2]<maxPQ->heap->A[i]){
		int temp=maxPQ->heap->A[i/2];
		maxPQ->heap->A[i]=temp;
		i/=2;
	}
}


void displayMaxPQ (MaxPriorityQueue * maxPQ) {
	displayMaxHeap (maxPQ->heap);
}

