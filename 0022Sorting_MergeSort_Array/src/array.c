#include "array.h"
#include "stack.h"

static const char letterCollection[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

//Function Defitions for struct _NODE
void NODE_METHOD_CONSTRUCTOR(NODE *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//Initializing the data
	memset(this->name, 0, NAME_LEN);
	this->number = 0;

	//Binding the member functions
	this->Random = &NODE_METHOD_Random;

	return ;
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

	//Initializing the data values
	this->nodeArray = (NODE *)malloc(sizeof(NODE)*(sizeArg));
	this->size = sizeArg;
	for (int i=0 ; i<this->size ; i++){
		NODE_METHOD_CONSTRUCTOR(this->nodeArray + i);
	}

	//Binding the method functions
	this->Fill_Random = &ARRAY_METHOD_Fill_Random;
	this->Print = &ARRAY_METHOD_Print;
	this->Copy_to_Raw_Array = &ARRAY_METHOD_Copy_to_Raw_Array;
	this->Sort = &ARRAY_METHOD_Sort;
	this->Sort2 = &ARRAY_METHOD_Sort_Iterative;

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
		(this->nodeArray)[i].Random(this->nodeArray + i);
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
		printf("[%d] Name: %s, Number: %d\n", i
											, (this->nodeArray)[i].name
											, (this->nodeArray)[i].number);
	}

	return ;
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

int MergeFunc(ARRAY *this, 
				int begin_A, int end_A,
				int begin_B, int end_B)
{
	int index_A = 0, index_B = 0, index_Res = 0;
	int length = (end_A - begin_A + 1) + (end_B - begin_B + 1);

	//Exception Handling
	assert(end_A+1 == begin_B);
	
	NODE *given_Arr = this->nodeArray;

	NODE *temp_Res = (NODE *)malloc(sizeof(NODE)*(length)); //Temporary result array

	int cmpResult = 0;

	for(index_Res = 0 ; index_Res < length ; index_Res++){
		cmpResult = strcmp(given_Arr[begin_A + index_A].name
							,given_Arr[begin_B + index_B].name);

		if (cmpResult > 0){
			memcpy(temp_Res + index_Res
					, given_Arr + begin_B + index_B
					, sizeof(NODE));
			index_B ++;

			if (begin_B + index_B > end_B){
				index_Res++;
				memcpy(temp_Res + index_Res
						, given_Arr + begin_A + index_A
						, sizeof(NODE) * (end_A - (begin_A + index_A) + 1));
				memcpy(given_Arr + begin_A
						, temp_Res
						, sizeof(NODE)*length);
				break;
			}
			else {
				continue;
			}
		}

		memcpy(temp_Res + index_Res
				, given_Arr + begin_A + index_A
				, sizeof(NODE));
		index_A ++;

		if (begin_A + index_A > end_A){
			index_Res++;
			memcpy(temp_Res + index_Res
					, given_Arr + begin_B + index_B
					, sizeof(NODE) * (end_B - (begin_B + index_B) + 1));
			memcpy(given_Arr + begin_A
					, temp_Res
					, sizeof(NODE)*length);
			break;
		}
		else {
			continue;
		}
	}

	free(temp_Res);

	return 0;
}

int DFS_Recursive(ARRAY *this, int begin_Index, int end_Index)
{
	//Binary Tree Recursive DFS traversal function for Merge Sorting.

	int middle_Num = 0;

	//printf("Visited Node: (%d, %d)\n", begin_Index, end_Index);

	if (begin_Index == end_Index){
		return 0;
	}

	middle_Num = (begin_Index + end_Index)/2;

	if(DFS_Recursive(this, begin_Index, middle_Num)){
		PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
		return -1;
	}

	if(DFS_Recursive(this, middle_Num+1, end_Index)){
		PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
		return -2;
	}

	if(MergeFunc(this, begin_Index, middle_Num
			, middle_Num+1, end_Index))
	{
		PRINTF_ERROR("ERROR: 'MergeFunc()' Failed.\n");
		return -3;
	}

	return 0;
}

ARRAY *ARRAY_METHOD_Sort(ARRAY *this)
{
	//Exception Handling
	if (this == NULL)
	{
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	if (DFS_Recursive(this, 0, this->size-1)){
		PRINTF_ERROR("ERROR: DFS_Recursive() failed.\n");
		return NULL;
	}

	return this;
}

ARRAY *ARRAY_METHOD_Sort_Iterative(ARRAY *this)
{
	int beginIndex=0, endIndex=0;
	STACK dfsStack;
	STACK_METHOD_CONSTRUCTOR(&dfsStack);
	STACK_NODE tempStackNode;
	int loopCtl = 0;

	//Exception Handling
	if (this == NULL)
	{
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	endIndex = this->size - 1;

	loopCtl = 1;
	while(loopCtl){
		if (beginIndex != endIndex){
			tempStackNode.begin_Index = beginIndex;
			tempStackNode.end_Index = endIndex;
			tempStackNode.status = 1;
			dfsStack.Push(&dfsStack, &tempStackNode);

			endIndex = (beginIndex + endIndex)/2;
			continue;
		}
		
		assert(beginIndex == endIndex);

		while(1){
			if (dfsStack.Size(&dfsStack) == 0){
				loopCtl = 0;
				break;
			}

			dfsStack.Pop(&dfsStack, &tempStackNode);
			beginIndex = tempStackNode.begin_Index;
			endIndex = tempStackNode.end_Index;

			if (tempStackNode.status == 1){
				tempStackNode.status = 2;
				dfsStack.Push(&dfsStack, &tempStackNode);
				beginIndex = (beginIndex + endIndex)/2 + 1;
				break;
			}
			else if (tempStackNode.status == 2){
				MergeFunc(this, beginIndex, (beginIndex+endIndex)/2, (beginIndex+endIndex)/2 + 1, endIndex);
			}
			else {
				PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
				return NULL;
			}
		}
	}

	STACK_METHOD_DESTRUCTOR(&dfsStack);

	return this;
}

