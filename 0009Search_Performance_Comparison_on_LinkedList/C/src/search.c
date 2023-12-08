#include "search.h"

static const char letterCollection[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

void NODE_CONSTRUCTOR(NODE *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	memset(this->name, 0, sizeof(char)*NAME_LEN);
	this->number = 0;
	this->prev = this->next = NULL;

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

	len = rand()%8;
	while (len == 0){
		len = rand()%8;
	}

	memset(this->name, 0, sizeof(char)*NAME_LEN);
	for (int i=0 ; i<len ; i++){
		(this->name)[i] = letterCollection[rand()%62];
	}
	this->number = rand()%10000; 

	return this;
}

void LIST_CONSTRUCTOR(LIST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	srand((unsigned int)time(NULL));

	this->begin = this->end = NULL;
	this->size = 0;

	//Binding the method functions
	this->AddRandom = &LIST_METHOD_AddRandom;
	this->ChangeRandomElement = &LIST_METHOD_ChangeRandomElement;
	this->Sort = &LIST_METHOD_Sort;
	this->Print = &LIST_METHOD_Print;
	this->Size = &LIST_METHOD_Size;
	this->LinearSearch = &LIST_METHOD_LinearSearch;
	this->JumpSearch = &LIST_METHOD_JumpSearch;
	this->BinarySearch = &LIST_METHOD_BinarySearch;

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

	if (this->size == 0){
		if (this->begin != NULL || this->end != NULL){
			PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
			return ;
		}
		return ;
	}

	temp = this->begin;
	while(temp != NULL){
		temp_next = temp->next;
		free(temp);
		temp = temp_next;
	}

	return ;
}

LIST *LIST_METHOD_AddRandom(LIST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the list is empty.
	if (this->size == 0){
		if (this->begin != NULL || this->end != NULL){
			//Exception Handling
			PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
			return NULL;
		}
		this->begin = this->end = (NODE *)malloc(sizeof(NODE));
		NODE_CONSTRUCTOR(this->begin);
		(this->begin->Random)(this->begin);
		this->size = 1;
		return this;
	}

	//When the list is noty empty.
	if (this->end->next != NULL){
		//Exception Handling
		PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
		return NULL;
	}
	this->end->next = (NODE *)malloc(sizeof(NODE));
	NODE_CONSTRUCTOR(this->end->next);
	(this->end->next->Random)(this->end->next);
	this->end->next->prev = this->end;
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
	if (strcmp(((NODE *)front)->name, ((NODE *)rear)->name) > 0){
		return 1;
	}
	return 0;
}

LIST *LIST_METHOD_Sort(LIST *this)
{
	NODE *buffer = NULL;
	NODE *temp = NULL;

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
	}

	buffer = (NODE *)malloc(sizeof(NODE)*(this->size));
	temp = this->begin;
	for (int i=0 ; i<this->size ; i++){
		strncpy(buffer[i].name, temp->name, NAME_LEN);
		buffer[i].number = temp->number;
		temp = temp->next;
	}

	qsort(buffer, (size_t)(this->size), sizeof(NODE), Comparator);

	temp = this->begin;
	for (int i=0 ; i<this->size ; i++){
		strncpy(temp->name, buffer[i].name, NAME_LEN);
		temp->number = buffer[i].number;
		temp = temp->next;
	}

	free(buffer);

	return this;
}

void LIST_METHOD_Print(LIST *this)
{
	NODE *temp=NULL;
	int index = 0;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//When the list is empty currently.
	if (this->size == 0){
		if (this->begin != NULL || this->end != NULL){
			//Exception Handling
			PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
			return ;
		}
		printf("\n");
		return ;
	}

	index = 0;
	temp = this->begin;
	while (temp != NULL){
		printf("[%d] Name: %s Number: %d\n", index, temp->name, temp->number);
		index ++;
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
	return this->size;
}

NODE *LIST_METHOD_LinearSearch(LIST *this, char *nameArg)
{
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

	temp = this->begin;
	while(temp != NULL){
		if (strcmp(temp->name, nameArg) == 0){
			return temp;
		}
		temp = temp->next;
	}

	return NULL;
}

int FindSqrt(int arg)
{
	int ret = 0;
	unsigned long long int begin=0, end=0, mid=0;
	unsigned long long int longArg = (unsigned long long int)(arg);

	begin = 0;
	end = (longArg)/2;

	while(begin <= end){
		mid = (begin + end)/2;
		if (mid*mid == longArg){
			return (int)mid;
		}
		else if (mid*mid > longArg){
			end = mid - 1;
			continue;
		}
		else if (mid*mid < longArg){
			begin = mid + 1;
			continue;
		}
	}

	if (mid*mid > longArg){
		mid --;
	}

	return (int)mid;
}

NODE *LIST_METHOD_JumpSearch(LIST *this, char *nameArg)
{
	NODE *temp = NULL;
	int index = 0;
	int stepSize = 0;
	int cmpResult = 0;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the list is empty currently.
	if (this->size == 0){
		return NULL;
	}

	stepSize = FindSqrt(this->size);
	temp = this->begin;

	while(1){
		cmpResult = strcmp(temp->name, nameArg);
		if (cmpResult == 0){
			return temp;
		}
		if (cmpResult < 0){
			if (index + stepSize < (*this).size){
				//Jump!
				index = index + stepSize;
				for (int i=0 ; i<stepSize ; i++){
					temp = temp->next;
				}
				continue;
			}
			else {
				//When you can't jump.
				for (int i=0 ; i<(*this).size-index-1 ; i++){
					temp = temp->next;
					cmpResult = strcmp(temp->name, nameArg);
					if (cmpResult == 0){
						return temp;
					}
					else if (cmpResult > 0){
						return NULL;
					}
					else if (cmpResult < 0){
						continue;
					}
				}
			}
		}
		if (cmpResult > 0){
			//Stop Jump!
			break;
		}
	}

	//When the first element is bigger than the value that you are searching for.
	if (index == 0){
		return NULL;
	}

	for (int i=0 ; i<stepSize-1 ; i++){
		temp = temp->prev;
		cmpResult = strcmp(temp->name, nameArg);
		if (cmpResult == 0){
			return temp;
		}
		else if (cmpResult > 0){
			continue;
		}
		else if (cmpResult < 0){
			return NULL;
		}
	}

	return NULL;
}

NODE *LIST_METHOD_BinarySearch(LIST *this, char *nameArg)
{
	NODE *temp = NULL;
	int beginIndex=0, endIndex=0, midIndex=0;
	int midIndex_next;
	int cmpResult = 0;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	beginIndex = 0;
	endIndex = (this->size)-1;
	midIndex = 0;
	temp = this->begin;

	while(beginIndex <= endIndex){
		midIndex_next = (beginIndex + endIndex)/2;
		if (midIndex_next < midIndex){
			for (int i=0 ; i<midIndex-midIndex_next ; i++){
				temp = temp->prev;
			}
		}
		else if (midIndex_next > midIndex){
			for (int i=0 ; i<midIndex_next-midIndex ; i++){
				temp = temp->next;
			}
		}
		else if (midIndex_next == midIndex){
			PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
			return NULL;
		}

		midIndex = midIndex_next;
		cmpResult = strcmp(temp->name, nameArg);
		if (cmpResult == 0){
			return temp;
		}
		if (cmpResult > 0){
			endIndex = midIndex - 1;
			continue;
		}
		if (cmpResult < 0){
			beginIndex = midIndex + 1;
			continue;
		}
	}

	return NULL;
}
