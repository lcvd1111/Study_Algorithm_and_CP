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

int Partition(ARRAY *this, int beginIndex, int endIndex)
{
	NODE *array = this->nodeArray;
	int leftIndex = beginIndex, rightIndex = endIndex, pivotIndex = endIndex;

	char temp_string[NAME_LEN] = {0,};
	int temp_number = 0;

	while(1){
		while(strcmp(array[leftIndex].name, array[pivotIndex].name) < 0){
			leftIndex++;
		}

		while(strcmp(array[rightIndex].name, array[pivotIndex].name) >= 0){
			rightIndex--;

			if (rightIndex < beginIndex){
				break;
			}
		}

		assert(leftIndex != rightIndex);

		if (leftIndex < rightIndex){
			memcpy(temp_string, array[leftIndex].name, NAME_LEN);
			memcpy(array[leftIndex].name, array[rightIndex].name, NAME_LEN);
			memcpy(array[rightIndex].name, temp_string, NAME_LEN);

			temp_number = array[leftIndex].number;
			array[leftIndex].number = array[rightIndex].number;
			array[rightIndex].number = temp_number;
			continue;
		}
		else if (leftIndex > rightIndex){
			break;
		}
	}

	memcpy(temp_string, array[leftIndex].name, NAME_LEN);
	memcpy(array[leftIndex].name, array[pivotIndex].name, NAME_LEN);
	memcpy(array[pivotIndex].name, temp_string, NAME_LEN);

	temp_number = array[leftIndex].number;
	array[leftIndex].number = array[pivotIndex].number;
	array[pivotIndex].number = temp_number;

	pivotIndex = leftIndex;

	return pivotIndex;
}

int DFS_Recursive(ARRAY *this, int beginIndex, int endIndex)
{
	int pivotIndex = 0;

	if (endIndex-beginIndex < 1){
		//Base Case
		return 0;
	}

	pivotIndex = Partition(this, beginIndex, endIndex);

	DFS_Recursive(this, beginIndex, pivotIndex-1); //Moving to left child node.

	DFS_Recursive(this, pivotIndex+1, endIndex); //Moving to right child node.

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
	int beginIndex = 0, endIndex = this->size - 1, pivotIndex = 0;
	STACK dfsStack;
	STACK_METHOD_CONSTRUCTOR(&dfsStack);
	STACK_NODE tempNode;

	while(1){
		if (endIndex-beginIndex >= 1){
			pivotIndex = Partition(this, beginIndex, endIndex);

			tempNode.begin_Index = beginIndex;
			tempNode.end_Index = endIndex;
			tempNode.pivot_Index = pivotIndex;
			dfsStack.Push(&dfsStack, &tempNode);

			//Moving to Left Child Node.
			endIndex = pivotIndex-1;
			continue;
		}

		assert(endIndex-beginIndex < 1);

		if (dfsStack.Size(&dfsStack) == 0){
			assert(dfsStack.begin == NULL && dfsStack.end == NULL);
			break;
		}

		//Backtracking
		dfsStack.Pop(&dfsStack, &tempNode);
		beginIndex = tempNode.begin_Index;
		endIndex = tempNode.end_Index;
		pivotIndex = tempNode.pivot_Index;

		//Moving to Right Child Node.
		beginIndex = pivotIndex+1;
		continue;
	}

	STACK_METHOD_DESTRUCTOR(&dfsStack);

	return this;
}
