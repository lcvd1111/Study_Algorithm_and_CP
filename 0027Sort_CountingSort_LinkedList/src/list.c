#include "list.h"

static char letterCollection[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
static LIST_NODE_METHOD gListNodeMethod = {.Random = &LIST_NODE_METHOD_Random };
static LIST_METHOD gListMethod = {.Print = &LIST_METHOD_Print,
							.Size = &LIST_METHOD_Size,
							.Add_One_Random = &LIST_METHOD_Add_One_Random,
							.Add_Random = &LIST_METHOD_Add_Random,
							.Copy_to_Array = &LIST_METHOD_Copy_to_Array,
							.Copy_to_List = &LIST_METHOD_Copy_to_List,
							.Sort = &LIST_METHOD_Sort};

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
	this->Method = &gListNodeMethod;

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
	this->Method = &gListMethod;

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
		this->size -= 1;
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

	printf("\n");
	for (int i=0 ; i<this->size ; i++){
		printf("[%d] Name: %s Number: %d\n"
				, i, temp->name, temp->number);
		temp = temp->next;
	}
	printf("\n");

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
		((this->begin)->Method->Random)(this->begin);
		return this;
	}

	//When the list is not empty currently.
	assert(this->end->next == NULL);
	this->end->next = (LIST_NODE *)malloc(sizeof(LIST_NODE));
	this->size += 1;
	LIST_NODE_METHOD_CONSTRUCTOR(this->end->next);
	this->end->next->prev = this->end;
	this->end = this->end->next;
	(this->end->Method->Random)(this->end);

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
		((*this).Method->Add_One_Random)(this);
	}

	return this;
}

LIST *LIST_METHOD_Copy_to_Array(LIST *this, LIST_NODE *dest)
{
	LIST_NODE *temp = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
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

LIST *LIST_METHOD_Copy_to_List(LIST *this, LIST *dest)
{
	LIST_NODE *temp = NULL;
	LIST_NODE *temp_dest = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	if (dest == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
	}

	//When the list is empty
	if (this->size == 0){
		return this;
	}

	LIST_METHOD_DESTRUCTOR(dest);
	assert(dest->begin == NULL);
	assert(dest->end == NULL);
	assert(dest->size == 0);

	temp = this->begin;
	dest->begin = (LIST_NODE *)malloc(sizeof(LIST_NODE));
	LIST_NODE_METHOD_CONSTRUCTOR(dest->begin);
	dest->size ++;
	temp_dest = dest->begin;
	for (int i=0 ; i<this->size ; i++){
		memcpy(temp_dest->name, temp->name, NAME_LEN);
		temp_dest->number = temp->number;
		temp = temp->next;
		temp_dest->next = (LIST_NODE *)malloc(sizeof(LIST_NODE));
		LIST_NODE_METHOD_CONSTRUCTOR(temp_dest->next);
		temp_dest->next->prev = temp_dest;
		dest->size ++;
		temp_dest = temp_dest->next;
	}

	assert(dest->size == this->size + 1);
	temp_dest = temp_dest->prev;
	LIST_NODE_METHOD_DESTRUCTOR(temp_dest->next);
	free(temp_dest->next);
	temp_dest->next = NULL;
	dest->size -= 1;

	return this;
}

static int FindMax(LIST *this)
{
	int ret = 0;
	LIST_NODE *currentNode = NULL;

	currentNode = this->begin;
	for (int i=0 ; i<this->size ; i++){
		if (ret < currentNode->number){
			ret = currentNode->number;
		}
		currentNode = currentNode->next;
	}

	return ret;
}

LIST *LIST_METHOD_Sort(LIST *this)
{
	int *countingArray = NULL;
	LIST_NODE *outputArray = NULL;
	LIST_NODE *currentNode = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	if (this->size < 2){
		PRINTF_ERROR("ERROR: size < 2\n");
		return NULL;
	}

	int max = FindMax(this);

	//Filling the Counting Array
	countingArray = (int *)malloc(sizeof(int)*(max+1));
	memset(countingArray, 0, sizeof(int)*(max+1));
	currentNode = this->begin;
	for (int i=0 ; i<this->size ; i++){
		countingArray[currentNode->number] += 1;
		currentNode = currentNode->next;
	}

	//Calculating the cumulative sum of counting array
	for (int i=0 ; i<max ; i++){
		countingArray[i+1] += countingArray[i];
	}

	//Countsorting using the cumulative sum of the countingarray
	outputArray = (LIST_NODE *)malloc(sizeof(LIST_NODE)*(this->size));
	currentNode = this->end;
	for (int i=0 ; i<this->size ; i++){
		countingArray[currentNode->number] -= 1;
		memcpy(&(outputArray[countingArray[currentNode->number]]), currentNode, sizeof(LIST_NODE));
		currentNode = currentNode->prev;
	}

	currentNode = this->begin;
	for (int i=0 ; i<this->size ; i++){
		memcpy(currentNode->name, outputArray[i].name, NAME_LEN);
		currentNode->number = outputArray[i].number;
		currentNode = currentNode->next;
	}

	free(outputArray);
	free(countingArray);

	return this;
}
