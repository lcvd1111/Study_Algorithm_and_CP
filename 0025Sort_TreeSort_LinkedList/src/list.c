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
	this->currentNode = NULL;

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

int Recursive_DFS_Inorder_Traversal
(LIST *this, BST *inputBST, BST_NODE *inputBSTnode)
{
	BST_NODE *current_Node = inputBSTnode;
	BST_NODE *tempNode = NULL;

	//Moving to left child node.
	if (current_Node->leftChild != NULL){
		Recursive_DFS_Inorder_Traversal(this, inputBST, current_Node->leftChild);
	}

	//Visit Checking.
	tempNode = current_Node;
	while(tempNode->nextFriend != NULL){
		memcpy(this->currentNode->name, tempNode->key, NAME_LEN);
		this->currentNode->number = tempNode->data;
		this->currentNode = this->currentNode->next;
		tempNode = tempNode->nextFriend;
	}
	memcpy(this->currentNode->name, tempNode->key, NAME_LEN);
	this->currentNode->number = tempNode->data;
	this->currentNode = this->currentNode->next;

	//Moving to right child node.
	if (current_Node->rightChild != NULL){
		Recursive_DFS_Inorder_Traversal(this, inputBST, current_Node->rightChild);
	}
	
	return 0;
}

LIST *LIST_METHOD_Sort(LIST *this)
{
	LIST_NODE *tempNode = NULL;
	BST sortBST;
	BST_METHOD_CONSTRUCTOR(&sortBST);

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	tempNode = this->begin;
	for (int i=0 ; i<this->size ; i++){
		sortBST.Insert(&sortBST, tempNode->name, tempNode->number);
		tempNode = tempNode->next;
	}

	assert(tempNode == NULL);

	this->currentNode = this->begin;
	Recursive_DFS_Inorder_Traversal(this, &sortBST, sortBST.root);
	this->currentNode = NULL;

	BST_METHOD_DESTRUCTOR(&sortBST);
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

