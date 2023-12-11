#include "search.h"

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
		return this;
	}

	len = rand()%8;

	while(len == 0){
		len = rand()%8;
	}

	for (int i=0 ; i<len ; i++){
		(*this).name[i] = letterCollection[rand()%62];
	}
	(*this).name[len] = 0;

	(*this).number = rand()%10000;

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

	this->size = sizeArg;
	this->nodeArray = (NODE *)malloc(sizeof(NODE)*sizeArg);
	for (int i=0 ; i<this->size ; i++){
		NODE_CONSTRUCTOR((this->nodeArray) + i);
	}

	//Binding Method functions
	this->Print = &ARRAY_METHOD_Print;
	this->Sort = &ARRAY_METHOD_Sort;
	this->FillRandom = &ARRAY_METHOD_FillRandom;
	this->ChangeRandomElement = &ARRAY_METHOD_ChangeRandomElement;
	this->LinearSearch = &ARRAY_METHOD_LinearSearch;
	this->JumpSearch = &ARRAY_METHOD_JumpSearch;
	this->BinarySearch = &ARRAY_METHOD_BinarySearch;

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
		PRINTF_ERROR("ERROR: this->nodeArray is NULL.\n");
		return ;
	}

	free(this->nodeArray);

	return ;
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
		PRINTF_ERROR("ERROR: this->nodeArray is NULL.\n");
		return ;
	}

	for (int i=0 ; i<(this->size) ; i++){
		printf("[%d] Name: %s Number: %d\n", i, (*this).nodeArray[i].name, (*this).nodeArray[i].number);
	}

	printf("\n");

	return ;
}

int Comparator(const void *front, const void *rear)
{
	if (strcmp(((NODE *)front)->name, ((NODE *)rear)->name) > 0){
		return 1;
	}
	return 0;
}

void ARRAY_METHOD_Sort(ARRAY *this)
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
	
	qsort(this->nodeArray, (this->size), sizeof(NODE), &Comparator);

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

	for (int i=0 ; i<this->size ; i++){
		(this->nodeArray)[i].Random(this->nodeArray+i);
	}

	return this;
}

ARRAY *ARRAY_METHOD_ChangeRandomElement(ARRAY *this, char *nameArg, int numArg)
{
	int index = 0;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
	}

	//Exception Hnadling
	if (this->nodeArray == NULL){
		PRINTF_ERROR("ERROR: 'this->nodeArray' is NULL.\n");
		return NULL;
	}

	index = rand()%(this->size);

	strncpy((this->nodeArray + index)->name, nameArg, NAME_LEN);
	(this->nodeArray + index)->number = numArg;

	return this;
}

NODE *ARRAY_METHOD_LinearSearch(ARRAY *this, char *nameArg)
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

	for (int i=0 ; i<this->size ; i++){
		if (strcmp((this->nodeArray)[i].name, nameArg) == 0){
			return (this->nodeArray + i);
		}
	}

	return NULL;
}

int FindSqrt(int arg)
{
	unsigned long long int begin=0, end=0, mid=0;

	end = arg/2;
	while(begin <= end){
		mid = (begin + end)/2;

		if (mid*mid == arg){
			break;
		}
		else if (mid*mid > arg){
			end = mid-1;
			continue;
		}
		else if (mid*mid < arg){
			begin = mid+1;
			continue;
		}
	}

	if (mid*mid > arg){
		mid--;
	}

	return (int)mid;
}

NODE *ARRAY_METHOD_JumpSearch(ARRAY *this, char *nameArg)
{
	int index = 0;
	int stepSize = 0;
	NODE *pArray = NULL;
	int cmpResult = 0;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//Exception Handling
	if (this->nodeArray == NULL){
		return NULL;
	}

	stepSize = FindSqrt(this->size);
	index = 0;
	pArray = this->nodeArray;

	while(1){
		cmpResult = strcmp(pArray[index].name, nameArg);
		if (cmpResult == 0){
			return (pArray+index);
		}
		else if (cmpResult > 0){
			//Stop Jump
			break;
		}
		else if (cmpResult < 0){
			if (index + stepSize < (this->size)){
				//Jump
				index += stepSize;
				continue;
			}
			else {
				//When you can't jump anymore.
				for (int i=0 ; i<(this->size)-stepSize-1 ; i++){
					index += 1;
					cmpResult = strcmp(pArray[index].name, nameArg);
					if (cmpResult == 0){
						return (pArray+index);
					}
					else if (cmpResult > 0){
						return NULL;
					}
					else if (cmpResult < 0){
						continue;
					}
				}
				return NULL;
			}
		}
	}

	//When even the first element is bigger than the value that you are searching for.
	if (index == 0){
		return NULL;
	}

	for (int i=0 ; i<stepSize-1 ; i++){
		index = index - 1;
		cmpResult = strcmp(pArray[index].name, nameArg);
		if (cmpResult == 0){
			return (pArray+index);
		}
		else if (cmpResult > 0){
			continue;
		}
		else {
			return NULL;
		}
	}

	return NULL;
}

NODE *ARRAY_METHOD_BinarySearch(ARRAY *this, char *nameArg)
{
	int beginIndex=0, midIndex=0, endIndex=0;
	NODE *pArray = NULL;
	int cmpResult = 0;

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

	pArray = this->nodeArray;
	endIndex = this->size - 1;

	while(beginIndex <= endIndex){
		midIndex = (beginIndex + endIndex)/2;
		cmpResult = strcmp(pArray[midIndex].name, nameArg);
		if (cmpResult == 0){
			return (pArray+midIndex);
		}
		else if (cmpResult > 0){
			endIndex = midIndex - 1;
			continue;
		}
		else if (cmpResult < 0){
			beginIndex = midIndex + 1;
			continue;
		}
	}

	return NULL;
}
