#include "stack.h"

void STACK_METHOD_CONSTRUCTOR(STACK *this)
{
	//Exception Handing
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//Initializing the member variables
	this->begin = this->end = NULL;
	this->size = 0;

	//Binding the method functions
	this->Push = &STACK_METHOD_Push;
	this->Pop = &STACK_METHOD_Pop;
	this->Size = &STACK_METHOD_Size;

	return ;
}

void STACK_METHOD_DESTRUCTOR(STACK *this)
{
	STACK_NODE *temp = NULL;
	STACK_NODE *temp_next = NULL;

	//Exception Handing
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//When the stack is empty.
	if (this->size == 0){
		return ;
	}

	//When the stack is not empty.
	temp = this->begin;
	while(temp != NULL){
		temp_next = temp->next;
		free(temp);
		temp = temp->next;
	}

	return ;
}

STACK *STACK_METHOD_Push(STACK *this, STACK_NODE *inputArg)
{
	//Exception Handing
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//Exception Handing
	if (inputArg == NULL){
		PRINTF_ERROR("ERROR: 'inputArg' is NULL.\n");
		return NULL;
	}

	//When the stack is empty currently.
	if (this->begin == NULL){
		assert(this->end == NULL && this->size == 0);
		this->begin = this->end = (STACK_NODE *)malloc(sizeof(STACK_NODE));
		this->size += 1;
		this->end->begin_Index = inputArg->begin_Index;
		this->end->end_Index = inputArg->end_Index;
		this->end->status = inputArg->status;
		this->end->prev = this->end->next = NULL;

		return this;
	}

	//When the stack is not empty currently.
	this->end->next = (STACK_NODE *)malloc(sizeof(STACK_NODE));
	this->end->next->prev = this->end;
	this->end->next->next = NULL;
	this->end = this->end->next;
	this->end->begin_Index = inputArg->begin_Index;
	this->end->end_Index = inputArg->end_Index;
	this->end->status = inputArg->status;
	this->size += 1;

	return NULL;
}

STACK *STACK_METHOD_Pop(STACK *this, STACK_NODE *outputDest)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//Exception Handing
	if (outputDest == NULL){
		PRINTF_ERROR("ERROR: 'outputDest' is NULL.\n");
		return NULL;
	}

	//When the stack is empty.
	if (this->begin == NULL){
		assert(this->end == NULL && this->size == 0);
		return NULL;
	}

	//When the stack has only an element currently.
	if (this->begin == this->end){
		assert(this->size == 1);
		memcpy(outputDest, this->end, sizeof(STACK_NODE));
		free(this->begin);
		this->begin = this->end = NULL;
		this->size = 0;
		return this;
	}

	memcpy(outputDest, this->end, sizeof(STACK_NODE));
	this->end = this->end->prev;
	free(this->end->next);
	this->end->next = NULL;
	this->size -= 1;

	return this;
}

int STACK_METHOD_Size(STACK *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return -1;
	}

	return (this->size);
}

