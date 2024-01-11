#include "list.h"

void LIST_CONSTRUCTOR(LIST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	this->begin = this->end = NULL;
	this->size = 0;

	//Binding the method functions
	this->AddRandom = &LIST_METHOD_AddRandom;
	this->Print = &LIST_METHOD_Print;
	this->Sort = &LIST_METHOD_Sort;
	this->CopyArray = &LIST_METHOD_CopyArray;
	this->Size = &LIST_METHOD_Size;

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

	//When the list is empty currently.
	if (this->begin == NULL){
		if (this->end != NULL){
			PRINTF_ERROR("ERROR: 'this->end' is not NULL.\n");
			return ;
		}
		if (this->size != 0){
			PRINTF_ERROR("ERROR: 'this->size' is not 0.\n");
			return ;
		}
		return ;
	}

	temp = this->begin;

	while(temp->next != NULL){
		temp = temp->next;
		free(temp->prev);
	}
	free(temp);

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
	if (this->begin == NULL){
		if (this->end != NULL){
			PRINTF_ERROR("ERROR: 'this->end' is not NULL.\n");
			return NULL;
		}
		if (this->size != 0){
			PRINTF_ERROR("ERROR: 'this->size' is not 0.\n");
			return NULL;
		}
		this->begin = this->end = (NODE *)malloc(sizeof(NODE));
		NODE_CONSTRUCTOR(this->begin);
		this->begin->Random(this->begin);
		this->size = 1;
		return this;
	}

	//When the list is not empty currently.
	if (this->end->next != NULL){
		PRINTF_ERROR("ERROR: 'this->end->next' is not NULL.\n");
		return NULL;
	}

	this->end->next = (NODE *)malloc(sizeof(NODE));
	NODE_CONSTRUCTOR(this->end->next);
	this->end->next->prev = this->end;
	this->end = this->end->next;
	this->end->Random(this->end);
	this->size += 1;

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

	//When the list is empty.
	if (this->begin == NULL){
		if (this->end != NULL){
			PRINTF_ERROR("ERROR: 'this->end' is not NULL.\n");
			return ;
		}
		if (this->size != 0){
			PRINTF_ERROR("ERROR: 'this->size' is not 0.\n");
			return ;
		}
		printf("\n");
	}

	temp = this->begin;
	for (int i=0 ; i<this->size ; i++){
		printf("[%d] Name: %s, Number: %d\n", i, temp->name, temp->number);
		temp = temp->next;
	}
	printf("\n");

	return ;
}

LIST *LIST_METHOD_Sort(LIST *this)
{
	PQ sortingPQ;
	int level = 0;
	int size = 0;
	NODE *temp = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	level = 0;
	size = 1;
	while (size < this->size){
		level++;
		size *= 2;
	}

	PQ_CONSTRUCTOR(&sortingPQ, level);

	temp = this->begin;
	for (int i=0 ; i<this->size ; i++){
		sortingPQ.Enqueue(&sortingPQ, temp);
		temp = temp->next;
	}

	this->begin = sortingPQ.Dequeue(&sortingPQ);
	temp = this->begin;
	for (int i=0 ; i<((this->size)-1) ; i++){
		temp->next = sortingPQ.Dequeue(&sortingPQ);
		temp->next->prev = temp;
		temp = temp->next;
	}
	temp->next = NULL;
	this->end = temp;

	PQ_DESTRUCTOR(&sortingPQ);

	return this;
}

LIST *LIST_METHOD_CopyArray(LIST *this, NODE **arrayArg)
{
	NODE *temp = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	*arrayArg = (NODE *)malloc(sizeof(NODE)*(this->size));
	temp = this->begin;
	for (int i=0 ; i<this->size ; i++){
		memcpy((*arrayArg)+i, temp, sizeof(NODE));
		temp = temp->next;
	}

	return this;
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
