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

	//Binding the method functions.
	this->Index = &LIST_METHOD_Index;
	this->Add = &LIST_METHOD_Add;
	this->Change = &LIST_METHOD_Change;
	this->Clear = &LIST_METHOD_Clear;
	this->Search = &LIST_METHOD_Search;

	return ;
}

void LIST_DESTRUCTOR(LIST *this)
{
	return ;
}

LIST *LIST_METHOD_Add(LIST *this)
{
	if (this->begin == NULL){
		this->begin = (NODE *)malloc(sizeof(NODE));
		this->end = this->begin->Random(this->begin);
		NODE_CONSTRUCTOR(this->begin);
		return this;
	}
	return this;
}

LIST *LIST_METHOD_Change(LIST *this, char *nameArg, int numArg)
{
	return this;
}

NODE *LIST_METHOD_Index(LIST *this, int indexArg)
{
	NODE *ret = NULL;
	return ret;
}

LIST *LIST_METHOD_Clear(LIST *this)
{
	return this;
}

NODE *LIST_METHOD_Search(LIST *this, char *nameArg)
{
	NODE *ret = NULL;
	return NULL;
}
