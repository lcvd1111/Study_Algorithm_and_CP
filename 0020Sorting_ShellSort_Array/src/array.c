#include "array.h"

static const int stepSizeList[] = {1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 
									4095, 8191, 16383, 32767, 65535, 131071, 262143,
									524287, 1048575, 2097151, 4194303, 8388607,
									16777215, 33554431, 67108863};
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

	memset(this->name, 0, NAME_LEN);
	for (int i=0 ; i<len ; i++){
		(this->name)[i] = letterCollection[rand()%62];
	}
	(this->name)[len] = 0;

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

	this->nodeArray = (NODE *)malloc(sizeof(NODE)*(sizeArg));
	for (int i=0 ; i<sizeArg ; i++){
		NODE_CONSTRUCTOR(this->nodeArray + i);
	}
	this->size = sizeArg;
	srand((unsigned int)time(NULL));

	//Binding the method functions
	this->FillRandom = &ARRAY_METHOD_FillRandom;
	this->Print = &ARRAY_METHOD_Print;
	this->CopyRawArray = &ARRAY_METHOD_CopyRawArray;
	this->Sort = &ARRAY_METHOD_Sort;

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
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	for (int i=0 ; i<this->size ; i++){
		((this->nodeArray)[i].Random)(this->nodeArray + i);
	}

	return this;
}

void ARRAY_METHOD_Print(ARRAY *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	for (int i=0 ; i<this->size ; i++){
		printf("[%d] Name: %s, Number: %d\n"
				, i
				, (this->nodeArray)[i].name
				, (this->nodeArray)[i].number);
	}
	printf("\n");

	return ;
}

ARRAY *ARRAY_METHOD_CopyRawArray(ARRAY *this, NODE **dst)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//Exception Handling
	if (dst == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	*dst = (NODE *)malloc(sizeof(NODE)*(this->size));
	memcpy(*dst, this->nodeArray, sizeof(NODE)*(this->size));

	return this;
}

int FindStepSizeIndex(int sizeArg)
{
	int ret = 0;

	for (ret=0 ; stepSizeList[ret]*2<sizeArg ; ret++){
	}

	ret--;

	return ret;
}

ARRAY *ARRAY_METHOD_Sort(ARRAY *this)
{
	int stepSize=0, stepSizeIndex=0;
	int beginIndex = 0;
	int sorted_LastIndex=0, current_Index=0;
	NODE operand_For_Sorting;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	stepSizeIndex = FindStepSizeIndex(this->size);

	for ( ; stepSizeIndex >= 0 ; stepSizeIndex--){
		stepSize = stepSizeList[stepSizeIndex];
		for (beginIndex=0 ; beginIndex<stepSize ; beginIndex++){
			sorted_LastIndex = beginIndex;
			while(1){
				if (sorted_LastIndex + stepSize >= this->size){
					break;
				}
				memcpy(&operand_For_Sorting, (this->nodeArray)+sorted_LastIndex + stepSize, sizeof(NODE));

				for (current_Index=sorted_LastIndex ; current_Index>=beginIndex ; current_Index -= stepSize)
				{
					if(strcmp((this->nodeArray)[current_Index].name, operand_For_Sorting.name) > 0){
						memcpy(this->nodeArray+current_Index+stepSize, this->nodeArray+current_Index, sizeof(NODE));
						if (current_Index-stepSize < 0){
							if (current_Index != beginIndex){
								PRINTF_ERROR("ERROR: Wrong\n");
								PRINTF_ERROR("CurrentIndex: %d, StepSize: %d, beginIndex: %d\n",
											current_Index, stepSize, beginIndex);
								return NULL;
							}
							memcpy(this->nodeArray+current_Index, &operand_For_Sorting, sizeof(NODE));
							break;
						}
					}
					else {
						memcpy(this->nodeArray+current_Index+stepSize, &operand_For_Sorting, sizeof(NODE));
						break;
					}
				}
				sorted_LastIndex += stepSize;
			}
		}
	}

	return this;
}

