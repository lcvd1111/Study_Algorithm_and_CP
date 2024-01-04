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

	while(len==0){
		len = rand()%8;
	}

	memset(this->name, 0, NAME_LEN);
	for (int i=0 ; i<len ; i++){
		(this->name)[i] = letterCollection[rand()%62];
	}
	this->number = rand()%10000;

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

	//Binding Method Functions
	this->AddRandom = &LIST_METHOD_AddRandom;
	this->ChangeRandomElement = &LIST_METHOD_ChangeRandomElement;
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

	//When the list is empty
	if (this->begin == NULL){
		if (this->end != NULL){
			PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
			return ;
		}
		return ;
	}

	//Exception Handling
	if (this->end == NULL){
		PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
		return ;
	}

	temp = this->begin;
	while(temp->next!=NULL){
		temp = temp->next;
		NODE_DESTRUCTOR(temp->prev);
		free(temp->prev);
		this->size -= 1;
	}
	NODE_DESTRUCTOR(temp);
	free(temp);
	this->size -= 1;

	this->begin = this->end = NULL;

	//Exception Handling
	if (this->size != 0){
		PRINTF_ERROR("ERROR: 'this->size' is not 0.\n");
		return ;
	}

	return ;
}

LIST *LIST_METHOD_AddRandom(LIST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the list is empty.
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
		return this;
	}

	//When the list is not empty
	if (this->end == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}
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

	//When the list is empty.
	if (this->begin == NULL){
		if (this->end != NULL){
			PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
			return NULL;
		}
		return NULL;
	}

	//Exception Handling
	if (this->end == NULL){
		PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
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

int LIST_METHOD_CopyArray(LIST *this, NODE **memDst)
{
	NODE *temp = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return -1;
	}

	//When the list is empty
	if (this->size == 0){
		return -2;
	}

	*memDst = (NODE *)malloc(sizeof(NODE)*(this->size));
	temp = this->begin;
	for (int i=0 ; i<this->size ; i++){
		memcpy((*memDst)+i, temp, sizeof(NODE));
		temp = temp->next;
	}

	return 0;
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
	if (this->size == 0){
		printf("\n");
		return ;
	}

	temp = this->begin;
	for (int i=0 ; i<(this->size) ; i++){
		printf("[%d] Name: %s, Number: %d\n"
				, i
				, temp->name
				, temp->number);
		temp = temp->next;
	}
	printf("\n");

	return ;
}

LIST *LIST_METHOD_Sort(LIST *this)
{
	NODE *sorted_Last_Node = NULL,
		 *unsorted_First_Node = NULL,
		 *currentNode = NULL;
	NODE operand_For_Sorting;
	int cmpResult = 0;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the size is smaller than 2
	if (this->size < 2){
		return NULL;
	}

	sorted_Last_Node = this->begin;
	for (int i=0 ; i<(this->size - 1) ; i++){
		unsorted_First_Node = sorted_Last_Node->next;
		memcpy(operand_For_Sorting.name, unsorted_First_Node->name, NAME_LEN);
		operand_For_Sorting.number = unsorted_First_Node->number;

		currentNode = sorted_Last_Node;

		while(currentNode != NULL){
			cmpResult = strcmp(currentNode->name, operand_For_Sorting.name);
			if (cmpResult > 0){
				memcpy(currentNode->next->name, currentNode->name, NAME_LEN);
				currentNode->next->number = currentNode->number;
				currentNode = currentNode->prev;
				continue;
			}
			else {
				memcpy(currentNode->next->name, operand_For_Sorting.name, NAME_LEN);
				currentNode->next->number = operand_For_Sorting.number;
				break;
			}
		}

		if (currentNode == NULL){
			memcpy(this->begin->name, operand_For_Sorting.name, NAME_LEN);
			this->begin->number = operand_For_Sorting.number;
		}

		sorted_Last_Node = sorted_Last_Node->next;
	}

	return this;
}
