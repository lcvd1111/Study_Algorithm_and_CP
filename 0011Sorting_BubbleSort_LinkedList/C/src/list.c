#include "list.h"

static const char letterCollection[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

void NODE_CONSTRUCTOR(NODE *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	memset(this->name, 0, sizeof(char)*NAME_LEN);
	this->number = 0;
	this->prev = this->next = NULL;

	//Binding Method Functions
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

	while(len == 0){
		len = rand()%8;
	}
	memset(this->name, 0, sizeof(char)*NAME_LEN);

	for (int i=0 ; i<len ; i++){
		(this->name)[i] = letterCollection[rand()%62];
	}
	(this->name)[len] = 0;

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
	
	srand((unsigned int)time(NULL));

	this->begin = this->end = NULL;
	this->size = 0;

	//Binding Method functions
	this->Size = &LIST_METHOD_Size;
	this->Push = &LIST_METHOD_Push;
	this->AddRandom = &LIST_METHOD_AddRandom;
	this->ChangeRandomElement = &LIST_METHOD_ChangeRandomElement;
	this->Print = &LIST_METHOD_Print;
	this->Sort = &LIST_METHOD_Sort;
	this->Swap = &LIST_METHOD_Swap;

	return ;
}

void LIST_DESTRUCTOR(LIST *this)
{
	NODE *temp = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	if (this->begin == NULL){
		if (this->end != NULL){
			//Exception Handling
			PRINTF_ERROR("ERROR: Unexepected situation occured.\n");
		}
		return ;
	}

	//Exception Handling
	if (this->end == NULL){
		PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
	}

	temp = this->begin;
	while(temp->next != NULL){
		temp = temp->next;
		free(temp->prev);
	}
	free(temp);

	this->begin = this->end = NULL;
	this->size = 0;

	return ;
}

int LIST_METHOD_Size(LIST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return -1;
	}

	return (this->size);
}

LIST *LIST_METHOD_Push(LIST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the list is empty.
	if (this->begin == NULL){
		if (this->end != NULL){
			//Exception Handling
			PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
			return NULL;
		}
		this->begin = this->end = (NODE *)malloc(sizeof(NODE));
		NODE_CONSTRUCTOR(this->begin);
		this->size = 1;
		return this;
	}

	//When the list is not empty.
	if (this->end == NULL){
		//Exception Handling
		PRINTF_ERROR("ERROR: Unexpected sitaution occured.\n");
		return NULL;
	}
	this->end->next = (NODE *)malloc(sizeof(NODE));
	NODE_CONSTRUCTOR(this->end->next);
	this->end->next->prev = this->end;
	this->end = this->end->next;
	this->size += 1;

	return this;
}

LIST *LIST_METHOD_AddRandom(LIST *this, int sizeArg)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//Exception Handling
	if (sizeArg < 1){
		PRINTF_ERROR("ERROR: sizeArg < 1.\n");
		return NULL;
	}

	for (int i=0 ; i<sizeArg ; i++){
		(*this).Push(this);
		(*(*this).end).Random((*this).end);
	}

	return this;
}

LIST *LIST_METHOD_ChangeRandomElement(LIST *this, char *nameArg, int numArg)
{
	int index = 0;
	NODE *temp = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the list is empty
	if (this->size == 0){
		return NULL;
	}

	index = rand()%(this->size);
	temp = this->begin;
	for (int i=0 ; i<index ; i++){
		temp = temp->next;
	}

	memset(temp->name, 0, NAME_LEN);
	strncpy(temp->name, nameArg, NAME_LEN);
	temp->number = numArg;

	return this;
}

void LIST_METHOD_Print(LIST *this)
{
	NODE *temp = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//When the list is empty
	if (this->size == 0){
		printf("\n");
		return ;
	}

	temp = this->begin;
	for (int i=0 ; i<this->size; i++){
		printf("[%d] Name: %s Number: %d\n", i, temp->name, temp->number);
		temp = temp->next;
	}

	if (temp != NULL){
		//Exception Handling
		PRINTF("ERROR: Unexpected situation occured\n");
	}
	printf("\n");

	return ;
}

LIST *LIST_METHOD_Swap(LIST *this, NODE *nodeA, NODE *nodeB)
{
	NODE buf;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the size of list is less than 2.
	if (this->size < 2){
		return NULL;
	}

	memcpy(&buf, nodeA, sizeof(NODE));
	strncpy(nodeA->name, nodeB->name, sizeof(char)*NAME_LEN);
	nodeA->number = nodeB->number;
	strncpy(nodeB->name, buf.name, sizeof(char)*NAME_LEN);
	nodeB->number = buf.number;

	return this;
}

LIST *LIST_METHOD_Sort(LIST *this)
{
	NODE *left=NULL, *right=NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the list size is smaller than 2.
	if (this->size < 2){
		return NULL;
	}

	for (int numberOfCompare = this->size-1
		; numberOfCompare>0 
		; numberOfCompare--)
	{
		left = this->begin;

		for (int i=0 ; i<numberOfCompare ; i++){
			right = left->next;
			if (strcmp(left->name, right->name) > 0){
				(*this).Swap(this, left, right);
			}
			left = left->next;
		}
	}

	return this;
}
