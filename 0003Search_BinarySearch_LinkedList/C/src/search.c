#include "search.h"

static const char* letterCollection = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

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

	//Binding method functions 
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

	len = rand()%10;
	len += 1;

	for (int i=0 ; i<len ; i++){
		(this->name)[i] = letterCollection[rand()%62];
	}
	(this->name)[len] = 0x00;
	this->number = rand()%100000;

	return this;
}

void LIST_CONSTRUCTOR(LIST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	this->begin = this->end = NULL;
	this->size = 0;

	srand((unsigned int)time(NULL));

	//Binding method functions
	this->AddRandom = &LIST_METHOD_AddRandom;
	this->ChangeRandomElement = &LIST_METHOD_ChangeRandomElement;
	this->Sort = &LIST_METHOD_Sort;
	this->Print = &LIST_METHOD_Print;
	this->Search = &LIST_METHOD_Search;

	return ;
}

void LIST_DESTRUCTOR(LIST *this)
{
	NODE *tempNode = NULL;
	NODE *tempNodeNext = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	tempNode =this->begin;
	while(tempNode != NULL){
		tempNodeNext = tempNode->next;
		free(tempNode);
		tempNode = tempNodeNext;
	}

	this->begin = this->end = NULL;
	this->size = 0;

	return ;
}

LIST *LIST_METHOD_AddRandom(LIST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the list is empty currently.
	if (this->size == 0){
		if (this->begin != NULL || this->end != NULL){
			//Exception Handling
			PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
			return NULL;
		}
		this->begin = (NODE *)malloc(sizeof(NODE));
		this->end = this->begin;
		NODE_CONSTRUCTOR(this->begin);
		this->begin->Random(this->begin);
		this->size = 1;
		return this;
	}

	//When the list is not empty currently.
	if (this->end->next != NULL){
		//Exception Handling
		PRINTF_ERROR("ERROR: end->next is not NULL.\n");
		return NULL;
	}

	this->end->next = (NODE *)malloc(sizeof(NODE));
	NODE_CONSTRUCTOR(this->end->next);
	(this->end->next->Random)(this->end->next);
	this->end->next->prev = this->end;
	this->end = this->end->next;
	this->size += 1;

	return this;
}

LIST *LIST_METHOD_ChangeRandomElement(LIST *this, char *nameArg, int numArg)
{
	int index = 0;
	NODE *currentNode = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the list is empty currently.
	if (this->size == 0){
		return NULL;
	}

	index = rand()%(this->size);
	currentNode = this->begin;
	for (int i=0 ; i<index ; i++){
		currentNode = currentNode->next;
	}

	strncpy(currentNode->name, nameArg, NAME_LEN);
	currentNode->number = numArg;

	return this;
}

static int CompareFunc(const void *front, const void *rear)
{
	if (strcmp(((NODE *)front)->name, ((NODE *)rear)->name)>0){
		return 1;
	}
	return -1;
}

LIST *LIST_METHOD_Sort(LIST *this)
{
	NODE *bufferArray = NULL;
	NODE *tempNode = NULL;

	//Exception Handling
	if (this==NULL){
		PRINTF_ERROR("ERROR: this is NULL.\n");
		return NULL;
	}

	//When the list is empty currently.
	if (this->size == 0){
		return NULL;
	}

	bufferArray = (NODE *)malloc(sizeof(NODE)*(this->size));
	tempNode = this->begin;
	for (int i=0 ; i<this->size ; i++){
		memcpy(bufferArray+i, tempNode, sizeof(NODE));
		tempNode = tempNode->next;
		if (tempNode == NULL){
			break;
		}
	}

	qsort(bufferArray, this->size, sizeof(NODE), &CompareFunc);
	tempNode = this->begin;
	for (int i=0 ; i<this->size ; i++){
		strncpy(tempNode->name, bufferArray[i].name, NAME_LEN * sizeof(char));
		tempNode->number = bufferArray[i].number;
		tempNode = tempNode->next;
	}

	free(bufferArray);

	return this;
}

void LIST_METHOD_Print(LIST *this)
{
	NODE *tempNode = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//When the list is empty currently.
	if (this->size == 0){
		return ;
	}

	tempNode = this->begin;

	while(tempNode != NULL){
		printf("[Name]: %s [Number]: %d\n", tempNode->name, tempNode->number);
		tempNode = tempNode->next;
	}
	printf("\n");

	return ;
}

NODE *LIST_METHOD_Search(LIST *this, char *nameArg)
{
	int beginIndex=0, endIndex=0, midIndex=0;
	int midIndex_next = 0;
	NODE *midNode = NULL;
	int cmpResult = 0;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the list is empty currently
	if (this->size == 0){
		return NULL;
	}

	beginIndex = 0;
	endIndex = this->size - 1;
	midIndex = 0;
	midNode = this->begin;
	while (beginIndex <= endIndex){
		midIndex_next = (beginIndex + endIndex)/2;
		if (midIndex < midIndex_next){
			for (int i=0 ; i<(midIndex_next - midIndex) ; i++){
				midNode = midNode->next;
			}
		}
		else if(midIndex > midIndex_next){
			for (int i=0 ; i<(midIndex - midIndex_next) ; i++){
				midNode = midNode->prev;
			}
		}
		else {
			PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
			return NULL;
		}

		midIndex = midIndex_next;
		cmpResult = strcmp(midNode->name, nameArg);
		if (cmpResult==0){
			return midNode;
		}
		if (cmpResult > 0){
			endIndex = midIndex - 1;
			continue;
		}
		if (cmpResult < 0){
			beginIndex = midIndex + 1;
			continue;
		}
	}

	return NULL;
}
