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
	this->heapArray = (NODE **)malloc(sizeof(NODE *)*(this->size));
	for (int i=0 ; i<this->size ; i++){
		(this->heapArray)[i] = NULL;
	}
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

PQ *PQ_METHOD_Enqueue(PQ *this, NODE *inputArg)
{
	int currentIndex=0, parentIndex=0;
	NODE **pHeapArray = NULL;
	NODE *buf = NULL;

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
	(this->heapArray)[this->lastIndex] = inputArg;

	pHeapArray = this->heapArray;
	currentIndex = this->lastIndex;

	while(currentIndex != 0){
		parentIndex = (currentIndex-1)/2;
		if (strcmp(pHeapArray[parentIndex]->name, pHeapArray[currentIndex]->name)>0){
			//Swap
			buf = pHeapArray[parentIndex];
			pHeapArray[parentIndex] = pHeapArray[currentIndex];
			pHeapArray[currentIndex] = buf;

			currentIndex = parentIndex;
			continue;
		}
		//Don't swap
		break;
	}

	return this;
}

NODE *PQ_METHOD_Dequeue(PQ *this)
{
	NODE *ret = NULL;
	int currentIndex=0, leftIndex=0, rightIndex=0;
	NODE **pHeapArray = NULL;
	NODE *buf = NULL;

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
	ret = pHeapArray[0];
	pHeapArray[0] = pHeapArray[this->lastIndex];
	pHeapArray[this->lastIndex] = NULL;
	this->lastIndex -= 1;

	//When the heap becomes empty after the dequeueing.
	if (this->lastIndex == -1){
		return ret;
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
			if (strcmp(pHeapArray[currentIndex]->name, pHeapArray[leftIndex]->name)>0)
			{
				//Swap
				buf = pHeapArray[currentIndex];
				pHeapArray[currentIndex] = pHeapArray[leftIndex];
				pHeapArray[leftIndex] = buf;
			}
			break;
		}
		else if (leftIndex < this->lastIndex){
			//When the currentIndex has both left and right children.
			if (strcmp(pHeapArray[currentIndex]->name, pHeapArray[leftIndex]->name)<=0
				&& strcmp(pHeapArray[currentIndex]->name, pHeapArray[rightIndex]->name)<=0)
			{
				break;
			}

			if (strcmp(pHeapArray[leftIndex]->name, pHeapArray[rightIndex]->name) < 0)
			{
				//Swap with left child.
				buf = pHeapArray[leftIndex];
				pHeapArray[leftIndex] = pHeapArray[currentIndex];
				pHeapArray[currentIndex] = buf;

				currentIndex = leftIndex;
				continue;
			}
			else {
				//Swap with right child.
				buf = pHeapArray[rightIndex];
				pHeapArray[rightIndex] = pHeapArray[currentIndex];
				pHeapArray[currentIndex] = buf;

				currentIndex = rightIndex;
				continue;
			}
		}
	}

	return ret;
}
