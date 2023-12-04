#include "search.h"

static char letterCollection[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

//Function Definitions
//NODE class related functions
void NODE_CONSTRUCTOR(NODE *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	memset(this->name, 0, NAME_LEN);
	this->number = 0;
	this->prev = this->next = NULL;

	//Binding method functions
	this->Random = &(NODE_METHOD_Random);

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

	memset(this->name, 0, NAME_LEN);
	len = rand() % 8;
	if (len == 0){
		len++;
	}

	for (int i=0 ; i<len ; i++){
		(this->name)[i] = letterCollection[rand()%62];
	}
	(this->name)[len] = 0x00;

	this->number = rand()%10000;
	while(this->number == 777){
		this->number = rand()%10000;
	};

	return this;
}

//LIST class related functions
void LIST_CONSTRUCTOR(LIST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	srand((unsigned int)time(NULL));
	this->begin = this->end =  NULL;
	this->size = 0;

	//Binding method functions
	this->Print = &LIST_METHOD_Print;
	this->Size = &LIST_METHOD_Size;
	this->AddRandom = &LIST_METHOD_AddRandom;
	this->ChangeRandomElement = &LIST_METHOD_ChangeRandomElement;
	this->Sort = &LIST_METHOD_Sort;
	this->Search = &LIST_METHOD_Search;

	return ;
}

void LIST_DESTRUCTOR(LIST *this)
{
	NODE *temp = NULL;
	NODE *temp_next = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//When the list is empty.
	if (this->size == 0){
		if (this->begin != NULL || this->end != NULL){
			//Exception Handling
			PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
			return ;
		}
	}

	temp = this->begin;

	while(temp != NULL){
		temp_next = temp->next;
		free(temp);
		temp = temp_next;
	}

	return ;
}

void LIST_METHOD_Print(LIST *this)
{
	NODE *temp = NULL;
	int i=0;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//When the list is empty
	if (this->size == 0){
		if (this->begin != NULL || this->end != NULL){
			//Exception Handling
			PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
			return ;
		}
		printf("\n");
		return ;
	}

	temp = this->begin;
	while(temp != NULL){
		printf("[%d] Name: %s Number: %d\n", i, temp->name, temp->number);
		i++;
		temp = temp->next;
	}
	printf("\n");

	return ;
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

LIST *LIST_METHOD_AddRandom(LIST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the list is empty currently.
	if (this->size == 0){
		if (this->begin != NULL || this->end != NULL){
			//Exception Handling
			PRINTF_ERROR("ERROR: Unexpected Situation Occured.\n");
			return NULL;
		}
		this->begin = this->end = (NODE *)malloc(sizeof(NODE));
		NODE_CONSTRUCTOR(this->begin);
		(this->begin->Random)(this->begin);
		this->size += 1;
		return this;
	}

	//When the list is not empty currently.
	if (this->end->next != NULL){
		//Exception Handling
		PRINTF_ERROR("ERROR: 'this->end->next' is not NULL.\n");
		return NULL;
	}
	this->end->next = (NODE *)malloc(sizeof(NODE));
	NODE_CONSTRUCTOR(this->end->next);
	this->end->next->prev = this->end;
	(this->end->next->Random)(this->end->next);
	this->end = this->end->next;
	this->size += 1;
	return this;
}

LIST *LIST_METHOD_ChangeRandomElement(LIST *this, char *nameArg, int numArg)
{
	int index = 0;
	NODE *temp = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the list is empty currently.
	if (this->size == 0){
		return NULL;
	}

	index = rand()%(this->size);
	temp = this->begin;
	for (int i=0 ; i<index ; i++){
		temp = temp->next;
	}

	strncpy(temp->name, nameArg, NAME_LEN);
	temp->number = numArg;

	return this;
}

int Comparator(const void *front, const void *rear)
{
	if (((NODE *)front)->number > ((NODE *)rear)->number){
		return 1;
	}
	return 0;
}

LIST *LIST_METHOD_Sort(LIST *this)
{
	NODE *bufferArray = NULL; //Temporal Array for stroing the list.
	NODE *temp = NULL; //For traversing the list.

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the list is empty currently.
	if (this->size == 0){
		if (this->begin != NULL || this->end != NULL){
			//Exception Handling
			PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
			return NULL;
		}
		return this;
	}

	bufferArray = (NODE *)malloc(sizeof(NODE)*(this->size));
	temp = this->begin;

	for (int i=0 ; i<this->size ; i++){
		memcpy(bufferArray+i, temp, sizeof(NODE));
		temp = temp->next;
	}

	if (temp != NULL){
		//Exception Handling
		PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
		return NULL;
	}

	//Sorting
	qsort(bufferArray, this->size, sizeof(NODE), &Comparator);

	temp = this->begin;
	for (int i=0 ; i<this->size ; i++){
		strncpy(temp->name, bufferArray[i].name, NAME_LEN);
		temp->number = bufferArray[i].number;
		temp = temp->next;
	}

	if (temp != NULL){
		//Exception Handling
		PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
		return NULL;
	}

	free(bufferArray);

	return this;
}

NODE *LIST_METHOD_Search(LIST *this, int numArg)
{
	int beginIndex=0, endIndex=0, midIndex=0;
	NODE *beginNode=NULL, *endNode=NULL, *midNode=NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the list is empty
	if (this->size == 0){
		if (this->begin != NULL || this->end != NULL){
			PRINTF_ERROR("ERROR: Unexpected Situation Occured.\n");
			return NULL;
		}
		return NULL;
	}

	beginIndex = 0;
	endIndex = this->size - 1;
	midIndex = 0;

	if ((*this).end->number < numArg || (*this).begin->number > numArg){
		return NULL;
	}

	while(beginIndex <= endIndex){
		beginNode = this->begin;
		endNode = this->end;
		for (int i=0 ; i<beginIndex ; i++){
			beginNode = beginNode->next;
		}
		endNode = beginNode;
		for (int i=0; i<(endIndex-beginIndex) ; i++){
			endNode = endNode->next;
		}

		if (numArg < beginNode->number || numArg > endNode->number){
			return NULL;
		}

		midIndex = beginIndex + (endIndex-beginIndex)*(numArg-(beginNode->number))/((endNode->number) - (beginNode->number));

		midNode = beginNode;
		for (int i=0 ; i<midIndex-beginIndex ; i++){
			midNode = midNode->next;
		}
		
		if (midNode->number == numArg){
			return midNode;
		}
		else if (midNode->number > numArg){
			endIndex = midIndex-1;
			continue;
		}
		else if (midNode->number < numArg){
			beginIndex = midIndex+1;
			continue;
		}
	}

	return NULL;
}
