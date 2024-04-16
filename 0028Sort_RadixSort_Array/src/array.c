#include "array.h"
#define UNIT_TEST_ARRAY

static const char letterCollection[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
static NODE_METHOD gNodeMethod = { .Random = &NODE_METHOD_Random };

static ARRAY_METHOD gArrayMethod =
		{ .Fill_Random = &ARRAY_METHOD_Fill_Random,
		.Print = &ARRAY_METHOD_Print,
		.Copy_to_Array = &ARRAY_METHOD_Copy_to_Array,
		.Copy_to_Raw_Array = &ARRAY_METHOD_Copy_to_Raw_Array,
		.Sort = &ARRAY_METHOD_Sort };

//Function Defitions for struct _NODE
void NODE_METHOD_CONSTRUCTOR(NODE *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//Initializing the member variables
	memset(this->name, 0, NAME_LEN);
	this->number = 0;

	//Binding the methods(=memeber functions)
	this->Method = &gNodeMethod;
}

void NODE_METHOD_DESTRUCTOR(NODE *this)
{	
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	return ;
}

void NODE_METHOD_Random(NODE *this)
{
	int len = 0;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	while(len == 0){
		len = rand()%8;
	}

	assert(len != 0);

	for (int i=0 ; i<len ; i++){
		(this->name)[i] = letterCollection[rand()%62];
	}
	(this->name)[len] = 0;

	this->number = rand()%10000;

	return ;
}


//Function Defitions for struct _ARRAY
void ARRAY_METHOD_CONSTRUCTOR(ARRAY *this, int sizeArg)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//Exception Handling
	if (sizeArg < 1){
		PRINTF_ERROR("ERROR: size is smaller than 0.\n");
		return ;
	}

	//Initializing the member variables.
	this->nodeArray = (NODE *)malloc(sizeof(NODE)*(sizeArg));
	this->size = sizeArg;
	for (int i=0 ; i<this->size ; i++){
		NODE_METHOD_CONSTRUCTOR(this->nodeArray + i);
	}
	this->currentIndex = 0;

	//Binding the methods(=member functions).
	this->Method = &gArrayMethod;

	srand((unsigned int)time(NULL));

	return ;
}

void ARRAY_METHOD_DESTRUCTOR(ARRAY *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	for (int i=0 ; i<this->size ; i++){
		NODE_METHOD_DESTRUCTOR(this->nodeArray + i);
	}

	free(this->nodeArray);
	this->nodeArray = NULL;
	this->size = 0;

	return ;
}

ARRAY *ARRAY_METHOD_Fill_Random(ARRAY *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	for (int i=0 ; i<this->size ; i++){
		((this->nodeArray)[i].Method->Random)(this->nodeArray + i);
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

	printf("\n");
	for (int i=0 ; i<this->size ; i++){
		printf("[%d] Name: %s, Number: %d\n", i
											, (this->nodeArray)[i].name
											, (this->nodeArray)[i].number);
	}

	return ;
}

ARRAY *ARRAY_METHOD_Copy_to_Array(ARRAY *this, ARRAY *dest)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//Exception Handling
	if (dest == NULL){
		PRINTF_ERROR("ERROR: 'dest' is NULL.\n");
		return NULL;
	}

	//Exception Handling
	if (this->nodeArray == NULL){
		PRINTF_ERROR("ERROR: 'this->nodeArray' is NULL.\n");
		return NULL;
	}

	if (dest->nodeArray != NULL){
		assert(dest->size != 0);
		free(dest->nodeArray);
	}

	dest->nodeArray = (NODE *)malloc(sizeof(NODE)*(this->size));
	dest->size = this->size;
	memcpy(dest->nodeArray, this->nodeArray, sizeof(NODE)*(this->size));

	return NULL;
}

ARRAY *ARRAY_METHOD_Copy_to_Raw_Array(ARRAY *this, NODE *dest)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//Exception Handling
	if (dest == NULL){
		PRINTF_ERROR("ERROR: 'dest' is NULL.\n");
		return NULL;
	}

	memcpy(dest, this->nodeArray, sizeof(NODE)*(this->size));

	return this;
}

static int FindMaximum(ARRAY *this)
{
	int ret = 0;

	for (int i=0 ; i<this->size ; i++){
		if (ret < (this->nodeArray)[i].number){
			ret = (this->nodeArray)[i].number;
		}
	}

	return ret;
}

static int FindDigitsNum(int arg)
{
	int ret = 0;

	while(arg > 0){
		arg = arg/10;
		ret ++;
	}

	return ret;
}

static ARRAY *CountSort_Base_Ten(ARRAY *this, int base)
{
	int max = 0;
	int divisor = 1;
	int countingArray[10] = {0,};
	NODE *outputArray = NULL;

	for (int i=0 ; i<base ; i++){
		divisor = divisor * 10;
	}

	//Finding the maximum value.
	for (int i=0 ; i<this->size ; i++){
		if (max < ((this->nodeArray)[i].number/divisor)%10){
			max = ((this->nodeArray)[i].number/divisor)%10;
		}
	}

	//Filling the countingArray.
	for (int i=0 ; i<this->size ; i++){
		countingArray[(((this->nodeArray)[i].number)/divisor) % 10] += 1;
	}

	//Calculating the cumulative sum of countingArray
	for (int i=0 ; i<9 ; i++){
		countingArray[i+1] += countingArray[i];
	}

	outputArray = (NODE *)malloc(sizeof(NODE)*(this->size));
	for (int i=this->size - 1 ; i>=0 ; i--){
		countingArray[(((this->nodeArray)[i].number)/divisor) % 10] -= 1;
		memcpy(&(outputArray[countingArray[(((this->nodeArray)[i].number)/divisor) % 10]]),
				&((this->nodeArray)[i]), 
				sizeof(NODE));
	}

	memcpy(this->nodeArray, outputArray, sizeof(NODE)*(this->size));
	free(outputArray);
	return this;
}

ARRAY *ARRAY_METHOD_Sort(ARRAY *this)
{
	int max = 0;
	int maxDigits = 0;

	//Test Code
#ifdef UNIT_TEST_ARRAY
	if (FindDigitsNum(12345) != 5){
		PRINTF_ERROR("ERROR: Test for FindDigitsNum(int) Failed.\n");
		return NULL;
	}
#endif

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	max = FindMaximum(this);
	maxDigits = FindDigitsNum(max);

	//Executing Counting sorting several times
	for (int i=0 ; i<maxDigits ; i++){
		if (CountSort_Base_Ten(this, i)!=this){
			PRINTF_ERROR("ERROR: CountSort_Base_Ten() Failed.\n");
			return NULL;
		}
	}

	return this;
}
