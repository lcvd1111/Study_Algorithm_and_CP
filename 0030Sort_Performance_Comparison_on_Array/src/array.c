#include "array.h"
#include "bst.h"

static const char letterCollection[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
static NODE_METHOD gNodeMethod = { .Random = &NODE_METHOD_Random };

static ARRAY_METHOD_SORT gArrayMethodSort =
		{ .Bubble_Sort = &ARRAY_METHOD_Sort_Bubble,
		.Insertion_Sort = &ARRAY_METHOD_Sort_Insertion,
		.Selection_Sort = &ARRAY_METHOD_Sort_Selection,
		.Heap_Sort = &ARRAY_METHOD_Sort_Heap,
		.Tree_Sort = &ARRAY_METHOD_Sort_Tree,
		.Quick_Sort = &ARRAY_METHOD_Sort_Quick,
		.Merge_Sort = &ARRAY_METHOD_Sort_Merge,
		.Shell_Sort = &ARRAY_METHOD_Sort_Shell };

static ARRAY_METHOD gArrayMethod =
		{ .Fill_Random = &ARRAY_METHOD_Fill_Random,
		.Print = &ARRAY_METHOD_Print,
		.Copy_to_Array = &ARRAY_METHOD_Copy_to_Array,
		.Copy_to_Raw_Array = &ARRAY_METHOD_Copy_to_Raw_Array,
		.Sort = &gArrayMethodSort };

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

ARRAY *ARRAY_METHOD_Sort_Bubble(ARRAY *this)
{
	char swapFlag = 0;
	int leftIndex = 0;
	int rightIndex = 0;
	NODE bufferNode;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	for (int i=0 ; i<(this->size)-1 ; i++){
		swapFlag = 0;
		for (int j=0 ; j<(this->size)-1-i ; j++){
			leftIndex = j;
			rightIndex = j+1;
			if (strcmp((this->nodeArray)[leftIndex].name,
						(this->nodeArray)[rightIndex].name)>0)
			{
				swapFlag = 1;
				memcpy(bufferNode.name, (this->nodeArray)[leftIndex].name, NAME_LEN);
				bufferNode.number = (this->nodeArray)[leftIndex].number;
				memcpy((this->nodeArray)[leftIndex].name, (this->nodeArray)[rightIndex].name, NAME_LEN);
				(this->nodeArray)[leftIndex].number = (this->nodeArray)[rightIndex].number;
				memcpy((this->nodeArray)[rightIndex].name, bufferNode.name, NAME_LEN);
				(this->nodeArray)[rightIndex].number = bufferNode.number;
			}
		}

		if (swapFlag == 0){
			break;
		}
	}

	return NULL;
}

ARRAY *ARRAY_METHOD_Sort_Insertion(ARRAY *this)
{
	int sorted_last_index = 0;
	int dest_element_index = 0;
	char bufferName[NAME_LEN] = {0,};
	int bufferNumber = 0;

	//Exception Handling
	if (this == NULL)
	{
		return NULL;
	}

	for (int i=0 ; i<(this->size)-1 ; i++)
	{
		sorted_last_index = i;
		dest_element_index = i+1;

		memcpy(bufferName, (this->nodeArray)[dest_element_index].name, NAME_LEN);
		bufferNumber = (this->nodeArray)[dest_element_index].number;

		for (int j=sorted_last_index ; j>=0 ; j--)
		{
			if (strcmp((this->nodeArray)[j].name, bufferName) > 0)
			{
				memcpy((this->nodeArray)[j+1].name, (this->nodeArray)[j].name, NAME_LEN);
				(this->nodeArray)[j+1].number = (this->nodeArray)[j].number;
				if (j==0){
					memcpy((this->nodeArray)[j].name, bufferName, NAME_LEN);
					(this->nodeArray)[j].number = bufferNumber;
				}
			}
			else {
				memcpy((this->nodeArray)[j+1].name, bufferName, NAME_LEN);
				(this->nodeArray)[j+1].number = bufferNumber;
				break;
			}
		}
	}

	return this;
}

ARRAY *ARRAY_METHOD_Sort_Selection(ARRAY *this)
{
	int destIndex = 0;
	int minIndex = 0;
	char bufferName[NAME_LEN] = {0,};
	int bufferNumber = 0;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	for (int i=0 ; i<(this->size)-1 ; i++){
		destIndex = i;
		minIndex = i;
		for (int j=i+1 ; j<(this->size) ; j++){
			if (strcmp((this->nodeArray)[minIndex].name, (this->nodeArray)[j].name) > 0){
				minIndex = j;
			}
		}

		//Swap
		memcpy(bufferName, (this->nodeArray)[minIndex].name, NAME_LEN);
		bufferNumber = (this->nodeArray)[minIndex].number;

		memcpy((this->nodeArray)[minIndex].name, (this->nodeArray)[destIndex].name, NAME_LEN);
		(this->nodeArray)[minIndex].number = (this->nodeArray)[destIndex].number;

		memcpy((this->nodeArray)[destIndex].name, bufferName, NAME_LEN);
		(this->nodeArray)[destIndex].number = bufferNumber;
	}

	return this;
}

ARRAY *ARRAY_METHOD_Sort_Heap(ARRAY *this)
{
	return this;
}

ARRAY *ARRAY_METHOD_Sort_Tree(ARRAY *this)
{
	return this;
}

int Partition(ARRAY *this, int leftIndexInput, int rightIndexInput)
{
	int leftEndIndex = leftIndexInput;
	int rightEndIndex = rightIndexInput;
	int pivotIndex = rightEndIndex;
	int leftCurrentIndex = leftEndIndex, rightCurrentIndex = rightEndIndex-1;

	char bufferName[NAME_LEN] = {0,};
	int bufferNumber = 0;

	//Exception Handling
	if (rightIndexInput - leftIndexInput <= 0){
		PRINTF_ERROR("ERROR: leftIndexInput == rightIndexInput.\n");
		return -2;
	}

	while(1){
		while(strcmp((this->nodeArray)[leftCurrentIndex].name, (this->nodeArray)[pivotIndex].name) < 0){
			leftCurrentIndex ++;
		}

		while(strcmp((this->nodeArray)[rightCurrentIndex].name, (this->nodeArray)[pivotIndex].name) >= 0){
			rightCurrentIndex --;
			if (rightCurrentIndex == leftEndIndex-1)
			{
				break;
			}
		}

		assert(leftCurrentIndex <= pivotIndex);

		if (leftCurrentIndex > rightCurrentIndex){
			//Swap(LEFT, PIVOT)
			memcpy(bufferName, (this->nodeArray)[pivotIndex].name, NAME_LEN);
			bufferNumber = (this->nodeArray)[pivotIndex].number;

			memcpy((this->nodeArray)[pivotIndex].name, (this->nodeArray)[leftCurrentIndex].name, NAME_LEN);
			(this->nodeArray)[pivotIndex].number = (this->nodeArray)[leftCurrentIndex].number;

			memcpy((this->nodeArray)[leftCurrentIndex].name, bufferName, NAME_LEN);
			(this->nodeArray)[leftCurrentIndex].number = bufferNumber;

			pivotIndex = leftCurrentIndex;
			break;
		}

		//Swap(LEFT, RIGHT)
		memcpy(bufferName, (this->nodeArray)[leftCurrentIndex].name, NAME_LEN);
		bufferNumber = (this->nodeArray)[leftCurrentIndex].number;

		memcpy((this->nodeArray)[leftCurrentIndex].name, (this->nodeArray)[rightCurrentIndex].name, NAME_LEN);
		(this->nodeArray)[leftCurrentIndex].number = (this->nodeArray)[rightCurrentIndex].number;
		
		memcpy((this->nodeArray)[rightCurrentIndex].name, bufferName, NAME_LEN);
		(this->nodeArray)[rightCurrentIndex].number = bufferNumber;
	}

	return pivotIndex;
}

int QuickSorting_DFS(ARRAY *this, int leftEnd, int rightEnd)
{
	int pivot_after_Partitioning = 0;
	//printf("leftEnd: %d, rightEnd: %d", leftEnd, rightEnd);

	//Base Case
	if (rightEnd - leftEnd <= 0){
		return 0;
	}

	pivot_after_Partitioning = Partition(this, leftEnd, rightEnd);

	//printf(" pivot after partitioning: %d\n", pivot_after_Partitioning);

	QuickSorting_DFS(this, leftEnd, pivot_after_Partitioning-1);
	QuickSorting_DFS(this, pivot_after_Partitioning+1, rightEnd);

	return 0;
}

ARRAY *ARRAY_METHOD_Sort_Quick(ARRAY *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	QuickSorting_DFS(this, 0, this->size - 1);

	return this;
}

int MergeFunc(ARRAY *this, int leftBeginIndex, int leftEndIndex, int rightBeginIndex, int rightEndIndex)
{
	int resultSize = rightEndIndex - leftBeginIndex + 1;
	NODE *tempResult = (NODE *)malloc(sizeof(NODE) * resultSize);
	int leftCurrentIndex=leftBeginIndex, rightCurrentIndex=rightBeginIndex;
	int strcmp_result = 0;

	for (int i=0 ; i<resultSize ; i++){
		strcmp_result = strcmp((this->nodeArray)[leftCurrentIndex].name, (this->nodeArray)[rightCurrentIndex].name);
		if (strcmp_result > 0){
			memcpy(tempResult[i].name, (this->nodeArray)[rightCurrentIndex].name, NAME_LEN);
			tempResult[i].number = (this->nodeArray)[rightCurrentIndex].number;
			rightCurrentIndex++;
			if (rightCurrentIndex > rightEndIndex){
				i++;
				memcpy(tempResult+i, (this->nodeArray)+leftCurrentIndex, sizeof(NODE)*(leftEndIndex - leftCurrentIndex + 1));
				break;
			}
			continue;
		}
		else {
			memcpy(tempResult[i].name, (this->nodeArray)[leftCurrentIndex].name, NAME_LEN);
			tempResult[i].number = (this->nodeArray)[leftCurrentIndex].number;
			leftCurrentIndex++;
			if (leftCurrentIndex > leftEndIndex){
				i++;
				memcpy(tempResult+i, (this->nodeArray)+rightCurrentIndex, sizeof(NODE)*(rightEndIndex - rightCurrentIndex + 1));
				break;
			}
			continue;
		}
	}

	memcpy((this->nodeArray)+leftBeginIndex, tempResult, sizeof(NODE)*resultSize);

	free(tempResult);
	return 0;
}

int MergeSorting_DFS(ARRAY *this, int leftEnd, int rightEnd)
{
	int left_begin_index=leftEnd, left_end_index=0, right_begin_index=0, right_end_index=rightEnd;

	//Base Case
	if (leftEnd == rightEnd){
		return 0;
	}

	left_end_index = left_begin_index + (rightEnd - leftEnd)/2;
	right_begin_index = left_end_index + 1;

	MergeSorting_DFS(this, left_begin_index, left_end_index);
	MergeSorting_DFS(this, right_begin_index, right_end_index);
	MergeFunc(this, left_begin_index, left_end_index, right_begin_index, right_end_index);

	return 0;
}

ARRAY *ARRAY_METHOD_Sort_Merge(ARRAY *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	MergeSorting_DFS(this, 0, this->size - 1);

	return this;
}

ARRAY *ARRAY_METHOD_Sort_Shell(ARRAY *this)
{
	return this;
}
