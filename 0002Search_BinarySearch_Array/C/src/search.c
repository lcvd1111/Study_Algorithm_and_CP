#include "search.h"

static const char letterCollection[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

//Function Definitions
void NODE_CONSTRUCTOR(NODE *this)
{
	memset(this->name, 0x00, NAME_LEN);
	this->number = 0;

	//Binding method functions
	this->Random = &NODE_METHOD_Random;

	return ;
}

void NODE_DESTRUCTOR(NODE *this)
{
	return ;
}

NODE *NODE_METHOD_Random(NODE *this)
{
	int length = 0;
	length = rand()%(NAME_LEN/2);
	length += 2;

	for (int i=0 ; i<length ; i++){
		(this->name)[i] = letterCollection[rand()%62];
	}

	(this->name)[length] = 0x00; //NULL Character
	this->number = rand()%10000;

	return this;
}

void ARRAY_CONSTRUCTOR(ARRAY *this, int sizeArg)
{
	//Exception Handling
	if (sizeArg < 1){
		PRINTF_ERROR("ERROR: sizeArg is smaller than 1.\n");
		return ;
	}

	srand((unsigned int)time(NULL));

	this->size = sizeArg;
	this->nodeArray = (NODE *)malloc(sizeof(NODE)*sizeArg);
	for (int i=0 ; i<this->size ; i++){
		NODE_CONSTRUCTOR((this->nodeArray)+i);
	}

	//Binding method functions
	this->FillRandom = &ARRAY_METHOD_FillRandom;
	this->ChangeRandomElement = &ARRAY_METHOD_ChangeRandomElement;
	this->Size = &ARRAY_METHOD_Size;
	this->Sort = &ARRAY_METHOD_Sort;
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

	//Exception Handling
	if (this->nodeArray == NULL){
		PRINTF_ERROR("ERROR: 'this->nodeArray' is NULL.\n");
		return ;
	}

	free(this->nodeArray);
	this->size = 0;

	return ;
}

ARRAY *ARRAY_METHOD_FillRandom(ARRAY *this)
{
	NODE *nodeArray_local = NULL;

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

	nodeArray_local = this->nodeArray;

	for (int i=0 ; i<(this->size) ; i++){
		nodeArray_local[i].Random(nodeArray_local + i);
	}

	return this;
}

NODE *ARRAY_METHOD_ChangeRandomElement(ARRAY *this, char *nameArg, int numArg)
{
	NODE *currentNode = NULL;
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
	currentNode = (this->nodeArray)+index;
	strncpy(currentNode->name, nameArg, NAME_LEN);
	currentNode->number = numArg;

	return currentNode;
}

int ARRAY_METHOD_Size(ARRAY *this)
{
	int ret = 0;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return -1;
	}

	//Exception Handling
	if (this->nodeArray == NULL){
		PRINTF_ERROR("ERROR: 'this->nodeArray' is NULL.\n");
		return -2;
	}

	ret = this->size;

	return ret;
}

int static ARRAY_PRIVATE_Compare(const void *front, const void *rear)
{
	int strcmp_ret = strcmp(front, rear);

	if (strcmp_ret == 0){
		return 0;
	}
	if (strcmp_ret > 0){
		return 1;
	}
	return -1;
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

	qsort(this->nodeArray, this->size, sizeof(NODE), &ARRAY_PRIVATE_Compare);

	return this;
}

NODE *ARRAY_METHOD_Search(ARRAY *this, char *nameArg)
{
	NODE *ret = NULL;
	int begin=0, end=0, mid=0;
	NODE *nodeArray_local = NULL;
	int compareRet = 0;

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

	nodeArray_local = this->nodeArray;
	begin = 0;
	end = this->size - 1;

	while(begin <= end){
		mid = (begin + end)/2;
		compareRet = strcmp(nodeArray_local[mid].name, nameArg);

		if (compareRet == 0){
			ret = nodeArray_local + mid;
			return ret;
		}
		else if(compareRet < 0){
			begin = mid + 1;
			continue;
		}
		else if(compareRet > 0){
			end = mid - 1;
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
		printf("[%d] Name: %s Number: %d\n", i, (this->nodeArray)[i].name, (this->nodeArray)[i].number);
	}

	return ;
}
