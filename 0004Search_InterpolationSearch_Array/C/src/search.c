#include "search.h"

static const char letterCollection[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

void NODE_CONSTRUCTOR(NODE *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return;
	}

	memset(this->name, 0, NAME_LEN);
	this->number = 0;

	//Binding Method functions
	this->Random = &NODE_METHOD_Random;

	return ;
}

void NODE_DESTRUCTOR(NODE *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return;
	}

	return ;
}

NODE *NODE_METHOD_Random(NODE *this)
{
	int len = rand()%8;
	len++;
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	memset(this->name, 0, NAME_LEN);
	
	for (int i=0 ; i<len ; i++){
		(this->name)[i] = letterCollection[rand()%62];
	}
	this->number = rand()%10000;
	if (this->number == 777){
		this->number += 1;
	}

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

	srand((unsigned int)time(NULL));

	this->nodeArray = (NODE *)malloc(sizeof(NODE)*sizeArg);
	for (int i=0 ; i<sizeArg ; i++){
		NODE_CONSTRUCTOR(&(this->nodeArray)[i]);
	}
	this->size = sizeArg;

	//Binding method functions
	this->FillRandom = &ARRAY_METHOD_FillRandom;
	this->ChangeRandomElement = &ARRAY_METHOD_ChangeRandomElement;
	this->Sort = &ARRAY_METHOD_Sort;
	this->Size = &ARRAY_METHOD_Size;
	this->Search = &ARRAY_METHOD_Search;
	this->Print = &ARRAY_METHOD_Print;

	return ;
}

void ARRAY_DESTRUCTOR(ARRAY *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	for (int i=0 ; i<this->size ; i++){
		NODE_DESTRUCTOR(this->nodeArray + i);
	}

	free(this->nodeArray);
	this->nodeArray = NULL;
	this->size = 0;

	return ;
}

ARRAY *ARRAY_METHOD_FillRandom(ARRAY *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//Exception Handling
	if (this->nodeArray == NULL){
		PRINTF_ERROR("ERROR: 'this->nodeArray' is NULL.\n");
		return NULL;
	}

	for (int i=0 ; i<this->size ; i++){
		(this->nodeArray)[i].Random(this->nodeArray+i);
	}

	return NULL;
}

ARRAY *ARRAY_METHOD_ChangeRandomElement
(ARRAY *this, char *nameArg, int numArg)
{
	int index = 0;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//Exception Handling
	if (this->nodeArray == NULL){
		PRINTF_ERROR("ERROR: 'this->nodeArray' is NULL.\n");
		return NULL;
	}

	index = rand() % (this->size);

	strncpy((this->nodeArray)[index].name, nameArg, NAME_LEN);
	(this->nodeArray)[index].number = numArg;

	return NULL;
}

static int COMPARATOR(const void *front, const void *rear)
{
	if ( ((NODE *)front)->number - ((NODE *)rear)->number > 0){
		return 1;
	}
	return 0;
}

ARRAY *ARRAY_METHOD_Sort(ARRAY *this)
{
	//Exeption Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//Exception Handling
	if (this->nodeArray == NULL){
		PRINTF_ERROR("ERROR: 'this->nodeArray' is NULL.\n");
		return NULL;
	}

	qsort(this->nodeArray, this->size, sizeof(NODE), &COMPARATOR);

	return NULL;
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

NODE *ARRAY_METHOD_Search(ARRAY *this, int numArg)
{
	int beginIndex=0, endIndex=0, midIndex=0;
	int cmpResult = 0;
	NODE *pNodeArray = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//Exception Handling
	if (this->nodeArray == NULL){
		PRINTF_ERROR("ERROR: 'this->nodeArray 'is NULL.\n");
		return NULL;
	}


	pNodeArray = this->nodeArray;
	beginIndex = 0;
	endIndex = this->size - 1;

	if (numArg > pNodeArray[endIndex].number
		|| numArg < pNodeArray[beginIndex].number)
	{
		return NULL;
	}

	while(beginIndex <= endIndex){
		midIndex = beginIndex
					+ (endIndex-beginIndex)
					* (numArg-pNodeArray[beginIndex].number)
					/ (pNodeArray[endIndex].number-pNodeArray[beginIndex].number);

		if (numArg == pNodeArray[midIndex].number){
			return pNodeArray + midIndex;
		}
		else if (numArg < pNodeArray[midIndex].number){
			endIndex = midIndex - 1;
			continue;
		}
		else if (numArg > pNodeArray[midIndex].number){
			beginIndex = midIndex + 1;
			continue;
		}
	}

	return NULL;
}

void ARRAY_METHOD_Print(ARRAY *this)
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

	for (int i=0 ; i<this->size ; i++){
		printf("[%d] Name: %s Number: %d\n", i
				, (this->nodeArray)[i].name
				, (this->nodeArray)[i].number);
	}

	printf("\n");

	return ;
}
