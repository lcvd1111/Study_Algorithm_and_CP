#include "array.h"

static const char letterCollection[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

//Function Definitions
void NODE_CONSTRUCTOR(NODE *this)
{
	//Exception Handling
	if (this==NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	memset(this->name, 0, sizeof(char)*NAME_LEN);
	this->number = 0;

	//Binding the method functions
	this->Random = NODE_METHOD_Random;

	return ;
}

void NODE_DESTRUCTOR(NODE *this)
{
	//Exception Handling
	if (this==NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	return ;
}

NODE *NODE_METHOD_Random(NODE *this)
{
	int len = 0;

	//Exception Handling
	if (this==NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	memset(this->name, 0, sizeof(char)*NAME_LEN);
	while (len == 0){
		len = rand()%8;
	}

	for (int i=0 ; i<len ; i++){
		(this->name)[i] = letterCollection[rand()%62];
	}

	this->number = rand()%10000;

	return NULL;
}

void ARRAY_CONSTRUCTOR(ARRAY *this, int sizeArg)
{
	//Exception Handling
	if (this==NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	srand((unsigned int)time(NULL));

	this->nodeArray = (NODE *)malloc(sizeof(NODE)*sizeArg);
	for (int i=0 ; i<sizeArg ; i++){
		NODE_CONSTRUCTOR(this->nodeArray + i);
	}
	this->size = sizeArg;

	//Binding the method functions
	this->FillRandom = ARRAY_METHOD_FillRandom;
	this->ChangeRandomElement = ARRAY_METHOD_ChangeRandomElement;
	this->Size = ARRAY_METHOD_Size;
	this->Print = ARRAY_METHOD_Print;
	this->Sort = ARRAY_METHOD_Sort;

	return ;
}

void ARRAY_DESTRUCTOR(ARRAY *this)
{
	//Exception Handling
	if (this==NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	free(this->nodeArray);

	return ;
}

ARRAY *ARRAY_METHOD_FillRandom(ARRAY *this)
{
	//Exception Handling
	if (this==NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	for (int i=0 ; i<(*this).Size(this) ; i++){
		(this->nodeArray)[i].Random((this->nodeArray)+i);
	}

	return NULL;
}

ARRAY *ARRAY_METHOD_ChangeRandomElement(ARRAY *this, char *nameArg, int numArg)
{
	NODE *temp = NULL;
	int index = 0;

	//Exception Handling
	if (this==NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	index = rand()%((*this).Size(this));

	strncpy((this->nodeArray)[index].name, nameArg, NAME_LEN);
	(this->nodeArray)[index].number = numArg;

	return NULL;
}

int ARRAY_METHOD_Size(ARRAY *this)
{
	//Exception Handling
	if (this==NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return -1;
	}

	return (this->size);
}

void ARRAY_METHOD_Print(ARRAY *this)
{
	//Exception Handling
	if (this==NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return;
	}

	for (int i=0 ; i<(*this).Size(this) ; i++){
		printf("[%d] Name: %s, Number: %d\n"
				, i
				, (*this).nodeArray[i].name
				, (*this).nodeArray[i].number);
	}

	return;
}

ARRAY *ARRAY_METHOD_Sort(ARRAY *this)
{
	int sorted_LastIndex = 0;
	int unsorted_BeginIndex = 0;
	char operand_ForSorting[NAME_LEN] = {0,};
	int cmpResult = 0;

	//Exception Handling
	if (this==NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	for (sorted_LastIndex=0 ; sorted_LastIndex<(this->size)-1 ; sorted_LastIndex++){
		unsorted_BeginIndex = sorted_LastIndex + 1;
		memcpy(operand_ForSorting, (this->nodeArray)[unsorted_BeginIndex].name, NAME_LEN);

		for (int currentIndex = sorted_LastIndex ; currentIndex >= 0 ; currentIndex--){
			cmpResult = strcmp(operand_ForSorting, (this->nodeArray)[currentIndex].name);
			if (cmpResult >= 0){
				memcpy((this->nodeArray)[currentIndex + 1].name, operand_ForSorting, NAME_LEN);
				break;
			}
			else if (cmpResult < 0){
				memcpy((this->nodeArray)[currentIndex + 1].name, (this->nodeArray)[currentIndex].name, NAME_LEN);
				if (currentIndex == 0){
					memcpy((this->nodeArray)[currentIndex].name, operand_ForSorting, NAME_LEN);
					break;
				}
				continue;
			}
		}
	}

	return NULL;
}
