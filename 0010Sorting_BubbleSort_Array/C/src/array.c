#include "array.h"

static const char letterCollection[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

void NODE_CONSTRUCTOR(NODE *this)
{
	//Exceptoin Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	memset(this->name, 0, sizeof(char)*(NAME_LEN));
	this->number = 0;

	//Binding the method functions
	this->Random = &NODE_METHOD_Random;

	return ;
}

void NODE_DESTRUCTOR(NODE *this)
{
	//Exceptoin Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	return ;
}

NODE *NODE_METHOD_Random(NODE *this)
{
	int len = 0;

	//Exceptoin Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	memset (this->name, 0, NAME_LEN);

	len = rand()%8;
	while(len == 0){
		len = rand()%8;
	}

	for (int i=0 ; i<len ; i++){
		(this->name)[i] = letterCollection[rand()%62];
	}
	(this->name)[len] = '\0';

	this->number = rand()%10000;

	return this;
}

void ARRAY_CONSTRUCTOR(ARRAY *this, int sizeArg)
{
	//Exceptoin Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//Exception Handling
	if (sizeArg < 1){
		PRINTF_ERROR("ERROR: sizeArg < 1.\n");
		return ;
	}

	srand((unsigned int)time(NULL));

	(this->size) = sizeArg;
	this->array = (NODE *)malloc(sizeof(NODE)*sizeArg);
	for (int i=0 ; i<(this->size) ; i++){
		NODE_CONSTRUCTOR(this->array+i);
	}

	//Binding Method Functions
	this->FillRandom = &ARRAY_METHOD_FillRandom;
	this->ChangeRandomElement = &ARRAY_METHOD_ChangeRandomElement;
	this->Print = &ARRAY_METHOD_Print;
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

	//Exception Handling
	if (this->array == NULL){
		PRINTF_ERROR("ERROR: 'this->array' is NULL.\n");
		return ;
	}

	free(this->array);
	this->array = NULL;
	this->size= 0;

	return ;
}

ARRAY *ARRAY_METHOD_FillRandom(ARRAY *this)
{
	NODE *pArray = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//Exception Handling
	if (this->array == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	pArray = this->array;

	for (int i=0 ; i<this->size ; i++){
		pArray[i].Random(pArray+i);
	}

	return this;
}

ARRAY *ARRAY_METHOD_ChangeRandomElement(ARRAY *this, char *nameArg, int numberArg)
{
	int index = 0;
	NODE *pArray = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//Exception Handling
	if (this->array == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	index = rand()%(this->size);
	pArray = this->array;

	strncpy(pArray[index].name, nameArg, NAME_LEN);
	pArray[index].number = numberArg;

	return this;
}

void ARRAY_METHOD_Print(ARRAY *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	for (int i=0 ; i<(this->size) ; i++){
		printf("[%d] Name: %s, Number: %d\n", i
				, (this->array)[i].name
				, (this->array)[i].number);
	}
	printf("\n");

	return ;
}

ARRAY *ARRAY_METHOD_Sort(ARRAY *this)
{
	int numCompare = 0;
	int leftIndex=0, rightIndex=0;
	NODE *pArray = NULL;
	NODE nodeBuf;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//Exception Handling
	if (this->array == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	pArray = this->array;

	for (numCompare = (this->size)-1 ; numCompare>0 ; numCompare--){
		for (leftIndex=0 ; leftIndex<numCompare ; leftIndex++){
			rightIndex = leftIndex+1;
			if (strcmp(pArray[leftIndex].name, pArray[rightIndex].name)>0){
				//Swap.
				memcpy(&nodeBuf, &pArray[leftIndex], sizeof(NODE));
				memcpy(&pArray[leftIndex], &pArray[rightIndex], sizeof(NODE));
				memcpy(&pArray[rightIndex], &nodeBuf, sizeof(NODE));
			}
			else {
				//Don't swap.
				continue;
			}
		}
	}

	return this;
}
