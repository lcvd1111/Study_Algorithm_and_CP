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
	for (int i=0 ; i<this->level ; i++){
		this->size = (this->size)*2;
	}
	this->size -= 1;
	this->nodeArray = (NODE **)malloc(sizeof(NODE *)*(this->size));
	for (int i=0 ; i<this->size ; i++){
		(this->nodeArray)[i] = NULL;
	}
	this->lastIndex = -1;

	//Binding the method functions
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
	if (this->nodeArray == NULL){
		PRINTF_ERROR("ERROR: 'this->nodeArray' is NULL.\n");
		return ;
	}

	free(this->nodeArray);
	this->nodeArray = NULL;

	return ;
}

PQ *PQ_METHOD_Enqueue(PQ *this, NODE *inputArg)
{
	int currentIndex = 0;
	int parentIndex = 0;
	NODE *buf = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	if (this->nodeArray == NULL){
		PRINTF_ERROR("ERROR: 'this->nodeArray' is NULL.\n");
		return NULL;
	}

	//When the heap is full currently.
	if (this->lastIndex == this->size - 1){
		PRINTF_ERROR("ERROR: PQ is full currently.\n");
		return NULL;
	}

	this->lastIndex += 1;
	(this->nodeArray)[this->lastIndex] = inputArg;

	currentIndex = this->lastIndex;
	while(currentIndex != 0){
		parentIndex = (currentIndex - 1)/2;
		if (strcmp((this->nodeArray)[parentIndex]->name, (this->nodeArray)[currentIndex]->name)>0){
			//Swap
			buf = (this->nodeArray)[parentIndex];
			(this->nodeArray)[parentIndex] = (this->nodeArray)[currentIndex];
			(this->nodeArray)[currentIndex] = buf;
			currentIndex = parentIndex;
			continue;
		}
		else {
			break;
		}
	}

	return this;
}

NODE *PQ_METHOD_Dequeue(PQ *this)
{
	NODE **pNodeArray = NULL;
	NODE *ret = NULL;
	int currentIndex=0, leftChildIndex=0, rightChildIndex=0;
	NODE *buf = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	if (this->nodeArray == NULL){
		PRINTF_ERROR("ERROR: 'this->nodeArray' is NULL.\n");
		return NULL;
	}

	pNodeArray = this->nodeArray;

	//When the heap is empty currently.
	if (this->lastIndex == -1){
		PRINTF_ERROR("ERROR: PQ is empty currently.\n");
		return NULL;
	}

	ret = pNodeArray[0];
	pNodeArray[0] = pNodeArray[this->lastIndex];
	pNodeArray[this->lastIndex] = NULL;
	this->lastIndex -= 1;

	//When the heap becomes empty after the dequeueing.
	if (this->lastIndex == -1){
		return ret;
	}

	currentIndex = 0;
	while(1){
		leftChildIndex = currentIndex*2 + 1;
		rightChildIndex = leftChildIndex + 1;

		if (leftChildIndex > (this->lastIndex)){
			//Current node doens't have any child.
			return ret;
		}
		else if (leftChildIndex == (this->lastIndex)){
			//Current node only has a left child.
			if (strcmp(pNodeArray[currentIndex]->name, pNodeArray[leftChildIndex]->name)>0){
				//Swap
				buf = pNodeArray[currentIndex];
				pNodeArray[currentIndex] = pNodeArray[leftChildIndex];
				pNodeArray[leftChildIndex] = buf;
			}
			return ret;
		}
		else if (leftChildIndex < (this->lastIndex)){
			//Current node has both left and right children.
			if (strcmp(pNodeArray[currentIndex]->name, pNodeArray[leftChildIndex]->name) <0
				&&
				strcmp(pNodeArray[currentIndex]->name, pNodeArray[rightChildIndex]->name)<0)
			{
				return ret;
			}

			if (strcmp(pNodeArray[leftChildIndex]->name, pNodeArray[rightChildIndex]->name)<0)
			{
				//When the left child is smaller than the right child.
				buf = pNodeArray[leftChildIndex];
				pNodeArray[leftChildIndex] = pNodeArray[currentIndex];
				pNodeArray[currentIndex] = buf;
				currentIndex = leftChildIndex;
				continue;
			}
			else {
				buf = pNodeArray[rightChildIndex];
				pNodeArray[rightChildIndex] = pNodeArray[currentIndex];
				pNodeArray[currentIndex] = buf;
				currentIndex = rightChildIndex;
				continue;
			}
		}
	}

	return ret;
}
