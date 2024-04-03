#include "heap.h"

static HEAP_METHOD gHeapMethod = {.Enqueue=&HEAP_METHOD_Enqueue, .Dequeue=&HEAP_METHOD_Dequeue };

//Function Definitions for methods
void HEAP_NODE_METHOD_CONSTRUCTOR(HEAP_NODE *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//Initializing the member variables
	memset(this->name, 0, NAME_LEN);
	this->number = 0;

	return ;
}

void HEAP_NODE_METHOD_DESTRUCTOR(HEAP_NODE *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	return ;
}

void HEAP_METHOD_CONSTRUCTOR(HEAP *this, int levelArg)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//Exception Handing
	if (levelArg < 1){
		PRINTF_ERROR("ERROR: levelArg < 0\n");
		return ;
	}

	//Initializing the member variables
	this->currentLastIndex = -1;
	this->level = levelArg;
	this->size = 1;
	for (int i=0 ; i<levelArg ; i++){
		this->size = (this->size)*2;
	}
	this->size -= 1;
	this->heapArray = (HEAP_NODE *)malloc(sizeof(HEAP_NODE)*(this->size));
	for (int i=0 ; i<(this->size) ; i++){
		HEAP_NODE_METHOD_CONSTRUCTOR(this->heapArray + i);
	}

	//Initializing the methods(=member functions)
	this->Method = &gHeapMethod;

	return ;
}

void HEAP_METHOD_DESTRUCTOR(HEAP *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	for (int i=0 ; i<(this->size) ; i++){
		HEAP_NODE_METHOD_DESTRUCTOR(this->heapArray + i);
	}
	free(this->heapArray);
	this->heapArray = NULL;

	return ;
}

int HEAP_METHOD_Enqueue(HEAP *this, char *inputName, int inputNumber)
{
	int parentIndex = 0, currentIndex = 0;
	char bufferName[NAME_LEN];
	int bufferNumber;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return -1;
	}

	//When the heap is full
	if (this->currentLastIndex == this->size){
		PRINTF_ERROR("ERROR: Heap is currently full.\n");
		return -2;
	}

	this->currentLastIndex ++ ;
	memcpy((this->heapArray)[this->currentLastIndex].name, inputName, NAME_LEN);
	(this->heapArray)[this->currentLastIndex].number = inputNumber;

	currentIndex = this->currentLastIndex;
	while(currentIndex != 0){
		parentIndex = (currentIndex - 1)/2;
		if (strcmp((this->heapArray)[parentIndex].name, (this->heapArray)[currentIndex].name) > 0){
			//Swap(Current, Parent)
			memcpy(bufferName, (this->heapArray)[currentIndex].name, NAME_LEN);
			bufferNumber = (this->heapArray)[currentIndex].number;

			memcpy((this->heapArray)[currentIndex].name, (this->heapArray)[parentIndex].name, NAME_LEN);
			(this->heapArray)[currentIndex].number = (this->heapArray)[parentIndex].number;

			memcpy((this->heapArray)[parentIndex].name, bufferName, NAME_LEN);
			(this->heapArray)[currentIndex].number = bufferNumber;

			currentIndex = parentIndex;
			continue;
		}
		else {
			break;
		}
	}

	return 0;
}

int HEAP_METHOD_Dequeue(HEAP *this, HEAP_NODE *dest)
{
	int currentIndex=0, leftChildIndex=0, rightChildIndex=0;
	char bufferName[NAME_LEN];
	int bufferNumber;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return -1;
	}

	//Exception Handling
	if (dest == NULL){
		PRINTF_ERROR("ERROR: 'dest' is NULL.\n");
		return -2;
	}

	//When the heap is empty.
	if (this->currentLastIndex == -1){
		PRINTF_ERROR("ERROR: heap is currently empty.\n");
		return -3;
	}

	memcpy(dest->name, (this->heapArray)[0].name, NAME_LEN);
	dest->number = (this->heapArray)[0].number;

	memcpy((this->heapArray)[0].name, (this->heapArray)[this->currentLastIndex].name, NAME_LEN);
	(this->heapArray)[0].number = (this->heapArray)[this->currentLastIndex].number;

	memset((this->heapArray)[this->currentLastIndex].name, 0, NAME_LEN);
	(this->heapArray)[this->currentLastIndex].number = 0;
	this->currentLastIndex -= 1;

	if (this->currentLastIndex == -1){
		return 0;
	}

	currentIndex = 0;
	while(1){
		leftChildIndex = 2*currentIndex + 1;
		rightChildIndex = 2*currentIndex + 2;
		
		//When the current node has no any child.
		if (leftChildIndex > (this->currentLastIndex)){
			break;
		}

		//When the current node has only a left child.
		if (leftChildIndex == (this->currentLastIndex)){
			if (strcmp((this->heapArray)[currentIndex].name,
						(this->heapArray)[leftChildIndex].name) <= 0)
			{
				break;
			}
			else {
				//Swap(Left, Current)
				memcpy(bufferName, (this->heapArray)[leftChildIndex].name, NAME_LEN);
				bufferNumber = (this->heapArray)[leftChildIndex].number;

				memcpy((this->heapArray)[leftChildIndex].name, (this->heapArray)[currentIndex].name, NAME_LEN);
				(this->heapArray)[leftChildIndex].number = (this->heapArray)[currentIndex].number;

				memcpy((this->heapArray)[currentIndex].name, bufferName, NAME_LEN);
				(this->heapArray)[currentIndex].number = bufferNumber;

				break;
			}
		}

		//When the current node has both left and right children.
		assert(leftChildIndex < (this->currentLastIndex));

		if (strcmp((this->heapArray)[leftChildIndex].name, (this->heapArray)[currentIndex].name) >= 0
				&&
			strcmp((this->heapArray)[rightChildIndex].name, (this->heapArray)[currentIndex].name) >= 0)
		{
			break;
		}

		if (strcmp((this->heapArray)[leftChildIndex].name, (this->heapArray)[rightChildIndex].name) > 0){
			//Swap(Right, Current)
			memcpy(bufferName, (this->heapArray)[rightChildIndex].name, NAME_LEN);
			bufferNumber = (this->heapArray)[rightChildIndex].number;

			memcpy((this->heapArray)[rightChildIndex].name, (this->heapArray)[currentIndex].name, NAME_LEN);
			(this->heapArray)[rightChildIndex].number = (this->heapArray)[currentIndex].number;

			memcpy((this->heapArray)[currentIndex].name, bufferName, NAME_LEN);
			(this->heapArray)[currentIndex].number = bufferNumber;

			currentIndex = rightChildIndex;
			continue;
		}
		else {
			//Swap(Left, Current)
			memcpy(bufferName, (this->heapArray)[leftChildIndex].name, NAME_LEN);
			bufferNumber = (this->heapArray)[leftChildIndex].number;

			memcpy((this->heapArray)[leftChildIndex].name, (this->heapArray)[currentIndex].name, NAME_LEN);
			(this->heapArray)[leftChildIndex].number = (this->heapArray)[currentIndex].number;

			memcpy((this->heapArray)[currentIndex].name, bufferName, NAME_LEN);
			(this->heapArray)[currentIndex].number = bufferNumber;

			currentIndex = leftChildIndex;
			continue;
		}
		
	}


	return 0;
}
