#include "search.h"

char letterCollection[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

//Function Defintions
void NODE_CONSTRUCTOR(NODE *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}
	memset(this->name, 0, NAME_LEN);
	this->number = 0;

	//Binding method functions
	this->Random = &NODE_METHOD_Random;

	return ;
}

void NODE_DESTRUCTOR(NODE *this)
{
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	return ;
}

NODE *NODE_METHOD_Random(NODE *this)
{
	int len = 0;

	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	memset(this->name, 0, NAME_LEN);
	len = rand() % 8;
	while(len == 0){
		len = rand() % 8;
	}

	for (int i=0 ; i<len ; i++){
		(this->name)[i] = letterCollection[rand()%62];
	}
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

	srand((unsigned int)time(NULL));

	this->nodeArray = (NODE *)malloc(sizeof(NODE)*(sizeArg));
	for (int i=0 ; i<sizeArg ; i++){
		NODE_CONSTRUCTOR((this->nodeArray)+i);
	}
	this->size = sizeArg;
	
	//Binding method functions
	this->FillRandom = &ARRAY_METHOD_FillRandom;
	this->ChangeRandomElement = &ARRAY_METHOD_ChangeRandomElement;
	this->Print = &ARRAY_METHOD_Print;
	this->Sort = &ARRAY_METHOD_Sort;
	this->Search = &ARRAY_METHOD_Search;

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
	if (this->nodeArray == NULL){
		PRINTF_ERROR("ERROR: 'this->nodeArray' is NULL.\n");
		return ;
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

	for (int i=0 ; i<(this->size) ; i++){
		(this->nodeArray)[i].Random(this->nodeArray + i);
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

	//Exception Handling
	if (this->nodeArray == NULL){
		PRINTF_ERROR("ERROR: 'this->nodeArray' is NULL.\n");
		return NULL;
	}

	index = rand()%(this->size);

	strncpy((this->nodeArray)[index].name, nameArg, NAME_LEN);
	(this->nodeArray)[index].number = numArg;

	return this;
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

	//When the array size is 0.
	if (this->size == 0){
		printf("\n");
		return ;
	}

	for (int i=0 ; i<this->size ; i++){
		printf("[%d] Name: %s Number: %d\n", i, (this->nodeArray)[i].name, (this->nodeArray)[i].number);
	}
	printf("\n");

	return ;
}

int Comparator(const void *front, const void *rear)
{
	if (strcmp(((NODE *)front)->name, ((NODE *)rear)->name) > 0 ){
		return 1;
	}
	return 0;
}

ARRAY *ARRAY_METHOD_Sort(ARRAY *this)
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

	//When the array size is 0.
	if (this->size == 0){
		return NULL;
	}

	qsort((this->nodeArray), this->size, sizeof(NODE), &Comparator);

	return this;
}

NODE *ARRAY_METHOD_Search(ARRAY *this, char *nameArg)
{
	return NULL;
}
