#include "array.h"

const char letterCollection[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

//Function Definitions
void NODE_CONSTRUCTOR(NODE *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	memset(this->name, 0, NAME_LEN);
	this->number = 0;

	//Binding the method functions
	this->Random = &NODE_METHOD_Random;

	return ;
}

void NODE_DESTRUCTOR(NODE *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	return ;
}

NODE *NODE_METHOD_Random(NODE *this)
{
	int len = 0;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	while (len == 0){
		len = rand()%8;
	}

	for (int i=0; i<len ; i++){
		(this->name)[i] = letterCollection[rand()%62];
	}
	(this->name)[len] = 0;
	this->number = rand()%10000;

	return this;
}

void ARRAY_CONSTRUCTOR(ARRAY *this, int sizeArg)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//Exception Handling
	if (sizeArg < 1){
		PRINTF_ERROR("ERROR: sizeArg < 1.\n");
		return ;
	}

	this->size = sizeArg;
	this->nodeArray = (NODE *)malloc(sizeof(NODE)*(sizeArg));
	for (int i=0 ; i<this->size ; i++){
		NODE_CONSTRUCTOR((this->nodeArray)+i);
	}
	srand((unsigned int)time(NULL));

	//Binding method functions
	this->FillRandom = &ARRAY_METHOD_FillRandom;
	this->ChangeRandomElement = &ARRAY_METHOD_ChangeRandomElement;
	this->Print = &ARRAY_METHOD_Print;
	this->Size = &ARRAY_METHOD_Size;
	this->Sort = &ARRAY_METHOD_Sort;

	return ;
}

void ARRAY_DESTRUCTOR(ARRAY *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	for (int i=0 ; i<(*this).Size(this) ; i++){
		NODE_DESTRUCTOR(this->nodeArray + i);
	}
	free(this->nodeArray);

	return ;
}

ARRAY *ARRAY_METHOD_FillRandom(ARRAY *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	for (int i=0 ; i<(*this).Size(this) ; i++){
		(*this).nodeArray[i].Random(this->nodeArray + i);
	}

	return this;
}

ARRAY *ARRAY_METHOD_ChangeRandomElement(ARRAY *this, char *nameArg, int numArg)
{
	int index = 0;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	index = rand()%(this->size);

	memcpy((this->nodeArray + index)->name, nameArg, NAME_LEN);
	(this->nodeArray + index)->number = numArg;

	return this;
}

void ARRAY_METHOD_Print(ARRAY *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	for (int i=0 ; i<(*this).Size(this) ; i++){
		printf("[%d] Name: %s, Number: %d\n"
				, i
				, (this->nodeArray + i)->name
				, (this->nodeArray + i)->number);
	}
	printf("\n");
	return ;
}

int ARRAY_METHOD_Size(ARRAY *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return -1;
	}

	return (this->size);
}

ARRAY *ARRAY_METHOD_Sort(ARRAY *this)
{
	int dst_Index = 0
		, current_Index = 0
		, min_Index = 0;
	int cmpResult = 0;
	NODE swapBuf;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the size is smaller than 2.
	if ((*this).Size(this) < 2){
		PRINTF_ERROR("ERROR: The size is smaller than 2.\n");
		return NULL;
	}

	for (dst_Index=0 ; dst_Index<(this->size) ; dst_Index++){
		min_Index = dst_Index;
		for (current_Index = dst_Index ; current_Index<(this->size) ; current_Index++){
			cmpResult = strcmp((*this).nodeArray[current_Index].name, (*this).nodeArray[min_Index].name);
			if (cmpResult >= 0){
				continue;
			}
			else {
				min_Index = current_Index;
				continue;
			}
		}
		
		//Swapping array[dst_Index] and array[min_Index]
		memcpy(&swapBuf, (*this).nodeArray+dst_Index, sizeof(NODE));
		memcpy((*this).nodeArray+dst_Index, (*this).nodeArray+min_Index, sizeof(NODE));
		memcpy((*this).nodeArray+min_Index, &swapBuf, sizeof(NODE));
	}

	return this;
}
