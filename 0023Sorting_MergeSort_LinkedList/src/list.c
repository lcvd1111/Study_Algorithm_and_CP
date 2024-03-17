#include "list.h"

static char letterCollection[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

//Function Definitions
void LIST_NODE_METHOD_CONSTRUCTOR(LIST_NODE *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	memset(this->name, 0, NAME_LEN);
	this->number = 0;
	this->prev = NULL;
	this->next = NULL;

	//Binding the method Functions
	this->Random = &LIST_NODE_METHOD_Random;

	return ;
}

void LIST_NODE_METHOD_DESTRUCTOR(LIST_NODE *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	return ;
}

void LIST_NODE_METHOD_Random(LIST_NODE *this)
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

void LIST_METHOD_CONSTRUCTOR(LIST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	this->begin = this->end = NULL;
	this->size = 0;

	//Binding the method functions
	this->Print = &LIST_METHOD_Print;
	this->Size = &LIST_METHOD_Size;
	this->Add_One_Random = &LIST_METHOD_Add_One_Random;
	this->Add_Random = &LIST_METHOD_Add_Random;
	this->Sort = &LIST_METHOD_Sort;
	this->Copy_to_Array = &LIST_METHOD_Copy_to_Array;

	srand((unsigned int)time(NULL));

	return ;
}

void LIST_METHOD_DESTRUCTOR(LIST *this)
{
	LIST_NODE *temp = NULL;
	LIST_NODE *temp_next = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//When the list is empty currently.
	if (this->size == 0){
		return ;
	}

	//When the list is not empty currently.
	temp = this->begin;

	while(temp != NULL){
		temp_next = temp->next;
		LIST_NODE_METHOD_DESTRUCTOR(temp);
		free(temp);
		temp = temp_next;
	}

	this->begin = this->end = NULL;

	return ;
}

LIST *LIST_METHOD_Print(LIST *this)
{
	LIST_NODE *temp = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	temp = this->begin;

	for (int i=0 ; i<this->size ; i++){
		printf("[%d] Name: %s Number: %d\n"
				, i, temp->name, temp->number);
		temp = temp->next;
	}

	return this;
}

int LIST_METHOD_Size(LIST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return -1;
	}

	return (this->size);
}

LIST *LIST_METHOD_Add_One_Random(LIST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the list is empty currently.
	if (this->size == 0){
		assert(this->begin == NULL && this->end == NULL);
		this->begin = (LIST_NODE *)malloc(sizeof(LIST_NODE));
		this->end = this->begin;
		this->size = 1;
		LIST_NODE_METHOD_CONSTRUCTOR(this->begin);
		((this->begin)->Random)(this->begin);
		return this;
	}

	//When the list is not empty currently.
	this->end->next = (LIST_NODE *)malloc(sizeof(LIST_NODE));
	this->size += 1;
	LIST_NODE_METHOD_CONSTRUCTOR(this->end->next);
	this->end->next->prev = this->end;
	this->end = this->end->next;
	(this->end->Random)(this->end);

	return this;
}

LIST *LIST_METHOD_Add_Random(LIST *this, int sizeArg)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//Exception Handling
	if (sizeArg < 0){
		PRINTF_ERROR("ERROR: sizeArg < 0.\n");
		return NULL;
	}
	
	for (int i=0 ; i<sizeArg ; i++){
		((*this).Add_One_Random)(this);
	}

	return this;
}

int MergeFunc(LIST *this, LIST_NODE *beginNode, int elementNum)
{
	LIST_NODE *leftCurrentNode = beginNode;
	int leftElementNum = (elementNum+1)/2;
	int leftCurrentIndex = 0;

	LIST_NODE *rightCurrentNode = beginNode; for (int i=0 ; i<leftElementNum ; i++){rightCurrentNode = rightCurrentNode->next;}
	int rightElementNum = elementNum - leftElementNum;
	int rightCurrentIndex = 0;

	int cmpResult = 0;
	LIST_NODE *temp = NULL;

	LIST_NODE *resultArray = (LIST_NODE *)malloc(sizeof(LIST_NODE) * elementNum);
	for (int i=0 ; i<elementNum ; i++){
		LIST_NODE_METHOD_CONSTRUCTOR(resultArray + i);
	}
	int resultCurrentIndex = 0;

	while(1){
		cmpResult = strcmp(leftCurrentNode->name, rightCurrentNode->name);
		if (cmpResult < 0){
			memcpy((resultArray[resultCurrentIndex]).name, leftCurrentNode->name, NAME_LEN);
			(resultArray[resultCurrentIndex]).number = leftCurrentNode->number;
			leftCurrentIndex ++;
			leftCurrentNode = leftCurrentNode->next;

			if (leftCurrentIndex == leftElementNum){
				for (int i=0 ; i<rightElementNum-rightCurrentIndex ; i++){
					resultCurrentIndex++;
					memcpy(resultArray[resultCurrentIndex].name, rightCurrentNode->name, NAME_LEN);
					resultArray[resultCurrentIndex].number = rightCurrentNode->number;
					rightCurrentNode = rightCurrentNode->next;
				}
				break;
			}
		}
		else {
			memcpy(resultArray[resultCurrentIndex].name, rightCurrentNode->name, NAME_LEN);
			(resultArray[resultCurrentIndex]).number = rightCurrentNode->number;
			rightCurrentIndex ++;
			rightCurrentNode = rightCurrentNode->next;
			
			if (rightCurrentIndex == rightElementNum){
				for (int i=0 ; i<leftElementNum-leftCurrentIndex ; i++){
					resultCurrentIndex++;
					memcpy(resultArray[resultCurrentIndex].name, leftCurrentNode->name, NAME_LEN);
					resultArray[resultCurrentIndex].number = leftCurrentNode->number;
					leftCurrentNode = leftCurrentNode->next;
				}
				break;
			}

		}
		resultCurrentIndex++;
	}

	assert (resultCurrentIndex == elementNum-1);

	temp = beginNode;
	for (int i=0 ; i<elementNum ; i++){
		memcpy(temp->name, resultArray[i].name, NAME_LEN);
		temp->number = resultArray[i].number;
		temp = temp->next;
	}

	return 0;
}

int DFS_Recursive(LIST *this, LIST_NODE *beginNode, int elementNum)
{
	int leftChildElementNum = 0;
	int rightChildElementNum = 0;
	LIST_NODE *rightChildBeginNode = NULL;

	//Exception Handling
	if (beginNode == NULL){
		PRINTF_ERROR("ERROR: beginNode is NULL.\n");
		return -1;
	}

	//Base Case
	if (elementNum == 1){
		return 0;
	}

	leftChildElementNum = (elementNum+1)/2;

	DFS_Recursive(this, beginNode, leftChildElementNum);//Going to left child Node.

	//Backtracking to parent node is done.

	rightChildBeginNode = beginNode;
	for (int i=0 ; i<leftChildElementNum ; i++){
		rightChildBeginNode = rightChildBeginNode->next;
	}
	rightChildElementNum = elementNum - leftChildElementNum;

	DFS_Recursive(this, rightChildBeginNode, rightChildElementNum);//Going to right child Node.

	//Backtracking to parent node is done.

	MergeFunc(this, beginNode, elementNum);
	
	return 0;
}

LIST *LIST_METHOD_Sort(LIST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
	}

	DFS_Recursive(this, this->begin, this->size);

	return this;
}

LIST *LIST_METHOD_Copy_to_Array(LIST *this, LIST_NODE *dest)
{
	LIST_NODE *temp = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
	}

	//When the list is empty
	if (this->size == 0){
		return this;
	}

	temp = this->begin;

	for (int i=0 ; i<this->size ; i++){
		memcpy(dest+i, temp, sizeof(LIST_NODE));
		temp = temp->next;
	}

	return this;
}

