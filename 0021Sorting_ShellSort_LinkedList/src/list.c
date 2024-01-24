#include "list.h"

static char letterCollection[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
static const int stepSizeList[] = {1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 
									4095, 8191, 16383, 32767, 65535, 131071, 262143,
									524287, 1048575, 2097151, 4194303, 8388607,
									16777215, 33554431, 67108863};

void NODE_CONSTRUCTOR(NODE *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	memset(this->name, 0, NAME_LEN);
	this->number = 0;
	this->prev = this->next = NULL;

	//Binding the method functions
	this->Random = &NODE_METHOD_Random;

	return ;
}

void NODE_DESTRUCTOR(NODE *this)
{
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	return ;
}

NODE *NODE_METHOD_Random(NODE *this)
{
	int len = 0;

	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	while(len == 0){
		len = rand()%8;
	}

	for (int i=0 ; i<len ; i++){
		(this->name)[i] = letterCollection[rand()%62];
	}
	(this->name)[len] = 0;

	this->number = rand()%10000;

	return this;
}

void LIST_CONSTRUCTOR(LIST *this)
{
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	this->begin = this->end = NULL;
	this->size = 0;
	srand((unsigned int)time(NULL));

	//Binding the Method Functions
	this->AddRandom = &LIST_METHOD_AddRandom;
	this->Print = &LIST_METHOD_Print;
	this->CopyRawArray = &LIST_METHOD_CopyRawArray;
	this->Sort = &LIST_METHOD_Sort;

	return ;
}

void LIST_DESTRUCTOR(LIST *this)
{
	NODE *temp = NULL;

	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//When the list is empty currently.
	if (this->begin==NULL){
		if (this->end != NULL){
			PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
			return ;
		}
		if (this->size != 0){
			PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
			return ;
		}
		return ;
	}

	//When the list is not empty currently.
	if (this->end == NULL || this->size == 0){
		PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
		return ;
	}

	temp = this->begin;
	while(temp->next != NULL){
		temp = temp->next;
		NODE_DESTRUCTOR(temp->prev);
		free(temp->prev);
	}
	NODE_DESTRUCTOR(temp);
	free(temp);

	this->begin = this->end = NULL;
	this->size = 0;

	return ;
}

LIST *LIST_METHOD_AddRandom(LIST *this)
{
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the list is empty currently.
	if (this->begin == NULL){
		if (this->end != NULL || this->size != 0){
			PRINTF_ERROR("ERROR: Unexepcetd situation occured.\n");
			return NULL;
		}
		this->begin = this->end = (NODE *)malloc(sizeof(NODE));
		NODE_CONSTRUCTOR(this->begin);
		this->size = 1;
		(this->begin->Random)(this->begin);
		return this;
	}

	//When the list is not empty currently.
	this->end->next = (NODE *)malloc(sizeof(NODE));
	NODE_CONSTRUCTOR(this->end->next);
	this->end->next->prev = this->end;
	this->end = this->end->next;
	(this->end->Random)(this->end);
	this->size += 1;

	return this;
}

void LIST_METHOD_Print(LIST *this)
{
	NODE *temp = NULL;
	int index = 0;

	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//When the list is empty.
	if (this->begin == NULL){
		if (this->end != NULL || this->size != 0){
			PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
			return ;
		}
		printf("\n");
		return ;
	}

	temp = this->begin;
	while(temp != NULL){
		printf("[%d] Name: %s, Number: %d\n", index, temp->name, temp->number);
		index++;
		temp = temp->next;
	}
	printf("\n");

	return ;
}

LIST *LIST_METHOD_CopyRawArray(LIST *this, NODE **dst)
{
	NODE *temp = NULL;

	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	if (dst == NULL){
		PRINTF_ERROR("ERROR: 'dst' is NULL.\n");
		return NULL;
	}

	//When the list is empty.
	if (this->size == 0){
		return NULL;
	}

	*dst = (NODE *)malloc(sizeof(NODE)*(this->size));

	temp = this->begin;
	for (int i=0 ; i<this->size ; i++){
		memcpy((*dst)+i, temp, sizeof(NODE));
		temp = temp->next;
	}

	return this;
}

LIST *LIST_METHOD_Sort(LIST *this)
{
	int stepSize = 0;
	int stepSizeIndex = 0;
	NODE *beginNode = NULL, *currentNode = NULL, *next_of_currentNode = NULL;
	NODE *sorted_LastNode = NULL, *unsorted_FirstNode = NULL;
	NODE operandForSorting;

	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the number of elements is less than 2.
	if (this->size < 2){
		PRINTF_ERROR("ERROR: 'this->size' is less than 2.\n");
		return NULL;
	}

	//Finding proper step size
	while(stepSizeList[stepSizeIndex]*2 < this->size){
		stepSizeIndex ++ ;
	}
	stepSizeIndex--;

	for ( ; stepSizeIndex>=0 ; stepSizeIndex--){
		stepSize = stepSizeList[stepSizeIndex];
		beginNode = this->begin;
		for (int beginIndex = 0; beginIndex < stepSize ; beginIndex ++){
			sorted_LastNode = beginNode;
			while(1){
				//Finding unsorted_FirstNode
				unsorted_FirstNode = sorted_LastNode;
				for (int i=0 ; i<stepSize ; i++){
					unsorted_FirstNode = unsorted_FirstNode->next;
					if (unsorted_FirstNode == NULL){
						//When the insertion sort is completed
						//Breaking the while loop.
						goto INSERTION_SORTING_COMPLETE;
					}
				}

				memcpy(&operandForSorting, unsorted_FirstNode, sizeof(NODE));
				currentNode = sorted_LastNode;
				next_of_currentNode = unsorted_FirstNode;

				while(1){
					if (strcmp(currentNode->name, operandForSorting.name) > 0){
						memcpy(next_of_currentNode->name, currentNode->name, NAME_LEN);
						next_of_currentNode->number = currentNode->number;
						if (currentNode != beginNode){
							next_of_currentNode = currentNode;
							for (int i=0 ; i<stepSize ; i++){
								currentNode = currentNode->prev;
							}
							continue;
						}
						else if (currentNode == beginNode){
							memcpy(currentNode->name, operandForSorting.name, NAME_LEN);
							currentNode->number = operandForSorting.number;
							break;
						}
					}
					else {
						memcpy(next_of_currentNode->name, operandForSorting.name, NAME_LEN);
						next_of_currentNode->number = operandForSorting.number;
						break;
					}
				}

				sorted_LastNode = unsorted_FirstNode;
			}

INSERTION_SORTING_COMPLETE:
			beginNode = beginNode->next;
		}
	}

	return this;
}
