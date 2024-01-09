#include "list.h"

static const char letterCollection[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

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

	this->begin = this->end = NULL;
	this->size = 0;

	srand((unsigned int)time(NULL));

	//Binding the method functions
	this->AddRandom = &LIST_METHOD_AddRandom;
	this->ChangeRandomElement = &LIST_METHOD_ChangeRandomElement;
	this->Size = &LIST_METHOD_Size;
	this->CopyArray = &LIST_METHOD_CopyArray;
	this->Print = &LIST_METHOD_Print;
	this->Sort = &LIST_METHOD_Sort;

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

	temp = this->begin;

	while(temp->next != NULL){
		temp = temp->next;
		NODE_DESTRUCTOR(temp->prev);
		free(temp->prev);
	}

	NODE_DESTRUCTOR(temp);
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

	//When the list is empty
	if (this->begin == NULL){
		if (this->end != NULL){
			PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
			return NULL;
		}
		if (this->size != 0){
			PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
			return NULL;
		}
		this->begin = this->end = (NODE *)malloc(sizeof(NODE));
		NODE_CONSTRUCTOR(this->begin);
		(this->begin->Random)(this->begin);
		this->size = 1;
		return NULL;
	}

	//Exception Handling
	if (this->end == NULL){
		PRINTF_ERROR("ERROR: Unexpected Situation occured.\n");
		return NULL;
	}
	if (this->size == 0){
		PRINTF_ERROR("ERROR: Unexpected Situation occured.\n");
		return NULL;
	}
	if (this->end->next != NULL){
		PRINTF_ERROR("ERROR: Unexpected Situation occured.\n");
		return NULL;
	}

	//When the list is not empty
	this->end->next = (NODE *)malloc(sizeof(NODE));
	NODE_CONSTRUCTOR(this->end->next);
	this->end->next->prev = this->end;
	this->end = this->end->next;
	(this->end->Random)(this->end);
	this->size += 1;

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
	if (this->begin == NULL){
		return NULL;
	}

	index = rand()%(this->size);
	temp = this->begin;

	for (int i=0 ; i<index ; i++){
		temp = temp->next;
	}

	memcpy(temp->name, nameArg, NAME_LEN);
	temp->number = numArg;

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

LIST *LIST_METHOD_CopyArray(LIST *this, NODE **dst)
{
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

	*dst = (NODE *)malloc(sizeof(NODE)*(this->size));
	temp = this->begin;

	for (int i=0 ; i<this->size ; i++){
		memcpy((*dst+i)->name, temp->name, NAME_LEN);
		(*dst+i)->number = temp->number;
		temp = temp->next;
	}

	return this;
}

void LIST_METHOD_Print(LIST *this)
{
	NODE *temp = NULL;
	int i=0;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//When the list is empty
	if (this->begin == NULL){
		printf("\n");
		return ;
	}

	temp = this->begin;
	while(temp != NULL){
		printf("[%i] Name: %s, Number: %d\n"
				, i
				, temp->name
				, temp->number);
		temp = temp->next;
		i++;
	}

	//Exception Handling
	if (i != this->size){
		PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
		return ;
	}

	printf("\n");

	return ;
}

LIST *LIST_METHOD_Sort(LIST *this)
{
	//Selection Sort
	NODE *dst_Node = NULL,
		 *current_Node = NULL,
		 *min_Node = NULL;
	int cmpResult = 0;
	
	char charBuf[NAME_LEN] = {0,};
	int intBuf = 0;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When size of the list is smaller than 2
	if (this->size < 2){
		return NULL;
	}

	dst_Node = this->begin;
	while(dst_Node != NULL){
		min_Node = dst_Node;
		current_Node = dst_Node->next;
		while(current_Node != NULL){
			//Finding the minimum node
			cmpResult = strcmp(min_Node->name, current_Node->name);
			if (cmpResult > 0){
				min_Node = current_Node;
			}
			current_Node = current_Node->next;
		}

		//Swapping the minimum node and destination node
		memcpy(charBuf, min_Node->name, NAME_LEN);
		intBuf = min_Node->number;
		memcpy(min_Node->name, dst_Node->name, NAME_LEN);
		min_Node->number = dst_Node->number;
		memcpy(dst_Node->name, charBuf, NAME_LEN);
		dst_Node->number = intBuf;

		dst_Node = dst_Node->next;
	}

	return this;
}
