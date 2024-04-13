#include "heap.h"

void PQ_CONSTRUCTOR(PQ *this, int levelArg)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	this->level = levelArg;
	this->size = 1;
	for (int i=0 ; i<levelArg ; i++){
		(this->size) = (this->size)*2;
	}
	this->size -= 1;
	this->heapArray = (BINARY_HEAP_NODE *)malloc(sizeof(BINARY_HEAP_NODE )*(this->size));
	memset(this->heapArray, 0, sizeof(BINARY_HEAP_NODE)*(this->size));
	this->lastIndex = -1;

	//Binding the method Functions
	this->Enqueue = &PQ_METHOD_Enqueue;
	this->Dequeue = &PQ_METHOD_Dequeue;

	return ;
}

void PQ_DESTRUCTOR(PQ *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//Exception Handling
	if (this->heapArray == NULL){
		PRINTF_ERROR("ERROR: 'this->heapArray' is NULL.\n");
		return ;
	}

	free(this->heapArray);
	this->heapArray = NULL;

	return ;
}

PQ *PQ_METHOD_Enqueue(PQ *this, BINARY_HEAP_NODE *inputArg)
{
	int currentIndex=0, parentIndex=0;
	BINARY_HEAP_NODE *pHeapArray = NULL;
	BINARY_HEAP_NODE buf;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the heap is full currently.
	if (this->lastIndex == this->size - 1){
		PRINTF_ERROR("ERROR: heap is full currently.\n");
		return NULL;
	}

	this->lastIndex += 1;
	memcpy(&((this->heapArray)[this->lastIndex]), inputArg, sizeof(BINARY_HEAP_NODE));

	pHeapArray = this->heapArray;
	currentIndex = this->lastIndex;

	while(currentIndex != 0){
		parentIndex = (currentIndex-1)/2;
		if (strcmp(pHeapArray[parentIndex].name, pHeapArray[currentIndex].name)>0){
			//Swap(Parent, Current)
			memcpy(&buf, pHeapArray+parentIndex, sizeof(BINARY_HEAP_NODE));
			memcpy(pHeapArray+parentIndex, pHeapArray+currentIndex, sizeof(BINARY_HEAP_NODE));
			memcpy(pHeapArray+currentIndex, &buf, sizeof(BINARY_HEAP_NODE));

			currentIndex = parentIndex;
			continue;
		}
		//Don't swap
		break;
	}

	return this;
}

PQ *PQ_METHOD_Dequeue(PQ *this, BINARY_HEAP_NODE *dest)
{
	int currentIndex=0, leftIndex=0, rightIndex=0;
	BINARY_HEAP_NODE *pHeapArray = NULL;
	BINARY_HEAP_NODE buf;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the heap is empty currently.
	if (this->lastIndex == -1){
		PRINTF_ERROR("ERROR: The heap is empty currently.\n");
		return NULL;
	}

	pHeapArray = this->heapArray;
	memcpy(dest, pHeapArray + 0, sizeof(BINARY_HEAP_NODE));
	memcpy(pHeapArray+0, pHeapArray+(this->lastIndex), sizeof(BINARY_HEAP_NODE));
	memset(pHeapArray+(this->lastIndex), 0, sizeof(BINARY_HEAP_NODE));
	this->lastIndex -= 1;

	//When the heap becomes empty after the dequeueing.
	if (this->lastIndex == -1){
		return this;
	}

	currentIndex = 0;
	while(1){
		leftIndex = currentIndex*2 + 1;
		rightIndex = leftIndex + 1;

		if (leftIndex > this->lastIndex){
			//When the currentIndex has no child.
			break;
		}
		else if (leftIndex == this->lastIndex){
			//When the currentIndex has only a left child.
			if (strcmp(pHeapArray[currentIndex].name, pHeapArray[leftIndex].name)>0)
			{
				//Swap(Current, LeftChild)
				memcpy(&buf, pHeapArray+currentIndex, sizeof(BINARY_HEAP_NODE));
				memcpy(pHeapArray+currentIndex, pHeapArray+leftIndex, sizeof(BINARY_HEAP_NODE));
				memcpy(pHeapArray+leftIndex, &buf, sizeof(BINARY_HEAP_NODE));
			}
			break;
		}
		else if (leftIndex < this->lastIndex){
			//When the currentIndex has both left and right children.
			if (strcmp(pHeapArray[currentIndex].name, pHeapArray[leftIndex].name)<=0
				&& strcmp(pHeapArray[currentIndex].name, pHeapArray[rightIndex].name)<=0)
			{
				break;
			}

			if (strcmp(pHeapArray[leftIndex].name, pHeapArray[rightIndex].name) < 0)
			{
				//Swap with left child.
				memcpy(&buf, pHeapArray+leftIndex, sizeof(BINARY_HEAP_NODE));
				memcpy(pHeapArray+leftIndex, pHeapArray+currentIndex, sizeof(BINARY_HEAP_NODE));
				memcpy(pHeapArray+currentIndex, &buf, sizeof(BINARY_HEAP_NODE));

				currentIndex = leftIndex;
				continue;
			}
			else {
				//Swap with right child.
				memcpy(&buf, pHeapArray+rightIndex, sizeof(BINARY_HEAP_NODE));
				memcpy(pHeapArray+rightIndex, pHeapArray+currentIndex, sizeof(BINARY_HEAP_NODE));
				memcpy(pHeapArray+currentIndex, &buf, sizeof(BINARY_HEAP_NODE));

				currentIndex = rightIndex;
				continue;
			}
		}
	}

	return this;
}
