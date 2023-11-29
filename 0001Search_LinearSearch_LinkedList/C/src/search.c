#include "search.h"

static const char letterCollection[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

//Function Definitions
void NODE_CONSTRUCTOR(NODE *this)
{
	memset(this->name, 0, NAME_LEN);
	this->number = 0;
	this->next = NULL;
	this->prev = NULL;

	this->Random = &NODE_METHOD_Random;
	return ;
}

void NODE_DESTRUCTOR(NODE *this)
{
	return ;
}

NODE *NODE_METHOD_Random(NODE *this)
{
	int len = 0;
	len = rand()%10;
	len += 2;

	for (int i=0 ; i<len ; i++){
		(this->name)[i] = letterCollection[rand()%62];
	}

	(this->name)[len] = 0x00;
	this->number = rand()%10000;

	return this;
}

void LIST_CONSTRUCTOR(LIST *this)
{
	srand((unsigned int)time(NULL));
	this->begin = NULL;
	this->end = NULL;
	this->size = 0;

	//Binding the method functions.
	this->Index = &LIST_METHOD_Index;
	this->AddRandom = &LIST_METHOD_AddRandom;
	this->Change = &LIST_METHOD_Change;
	this->Clear = &LIST_METHOD_Clear;
	this->Search = &LIST_METHOD_Search;
	this->Print = &LIST_METHOD_Print;

	return ;
}

void LIST_DESTRUCTOR(LIST *this)
{
	(*this).Clear(this);
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
		if (this->size != 0){
			PRINTF_ERROR("ERROR: Unexpected Situation Occured.\n");
			return NULL;
		}
		this->begin = (NODE *)malloc(sizeof(NODE));
		this->end = this->begin;
		NODE_CONSTRUCTOR(this->begin);
		this->begin->Random(this->begin);
		this->size += 1;
		return this;
	}

	//When the list is not empty currently.
	if (this->end->next != NULL){
		PRINTF_ERROR("ERROR: end->next is not NULL.\n");
		return NULL;
	}
	this->end->next = (NODE *)malloc(sizeof(NODE));
	NODE_CONSTRUCTOR(this->end->next);
	this->end->next->Random(this->end->next);
	this->end->next->prev = this->end;
	this->end = this->end->next;
	this->size += 1;

	return this;
}

LIST *LIST_METHOD_Change(LIST *this, char *nameArg, int numArg)
{
	int indexNum = 0;
	NODE *selectedPos = NULL;

	//Exception Handing
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the list is empty.
	if (this->size == 0){
		return NULL;
	}

	indexNum = rand()%(this->size);
	selectedPos = (*this).Index(this, indexNum);

	strncpy(selectedPos->name, nameArg, NAME_LEN);
	selectedPos->number = numArg;

	return this;
}

NODE *LIST_METHOD_Index(LIST *this, int indexArg)
{
	NODE *ret = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//Exception Handling
	if (indexArg >= this->size){
		PRINTF_ERROR("ERROR: Out of Index.\n");
		return NULL;
	}

	//When the list is empty.
	if (this->begin == NULL){
		return NULL;
	}

	ret = this->begin;
	for (int i=0 ; i<indexArg ; i++){
		ret = ret->next;
	}

	return ret;
}

LIST *LIST_METHOD_Clear(LIST *this)
{
	NODE *tempNode = NULL;
	NODE *tempNode_next = NULL;
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the list is empty currently.
	if (this->size == 0){
		if (this->begin != NULL || this->end != NULL){
			PRINTF_ERROR("ERROR: Something unexpected thing has happened.\n");
		}
		return NULL;
	}

	tempNode = this->begin;
	while(tempNode != NULL){
		tempNode_next = tempNode->next;
		free(tempNode);
		tempNode = tempNode_next;
	}

	this->begin = NULL;
	this->end = NULL;
	this->size = 0;

	return this;
}

NODE *LIST_METHOD_Search(LIST *this, char *nameArg)
{
	NODE *ret = NULL;

	//Exception Handling
	if (this==NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the list is empty currently
	if (this->size == 0){
		return NULL;
	}

	ret = this->begin;
	while(ret != NULL){
		if (strcmp(ret->name, nameArg) == 0){
			return ret;
		}

		ret = ret->next;
	}

	return NULL;
}

void LIST_METHOD_Print(LIST *this)
{
	NODE *temp = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//When the list is empty currently.
	if (this->begin == NULL){
		return ;
	}

	temp = this->begin;

	for (int i=0 ; i<this->size ; i++){
		printf("[%d]Name:%s Number:%d\n", i, temp->name, temp->number);
		temp = temp->next;
	}

	return ;
}
