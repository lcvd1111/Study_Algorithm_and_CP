#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG( x , ... ) printf("[%d %s]" x, __LINE__, __func__, ##__VA_ARGS__)

#define STRING_LEN 64

typedef struct _QUEUE_NODE QUEUE_NODE;
struct _QUEUE_NODE {
	char data[STRING_LEN];
	unsigned int level;
	QUEUE_NODE *next;
	QUEUE_NODE *prev;
};

typedef struct _QUEUE QUEUE;
struct _QUEUE {
	QUEUE_NODE *begin;
	QUEUE_NODE *end;
	//Methods
	QUEUE *(*Enqueue)(QUEUE *self, char *, unsigned int);
	QUEUE *(*Dequeue)(QUEUE *self, QUEUE_NODE *);
	QUEUE *(*EmptyQueue)(QUEUE *self);
};

QUEUE Constructor_Queue(QUEUE *self);
int Destructor_Queue(QUEUE *self);
QUEUE *Method_Enqueue(QUEUE *self, char *, unsigned int);
QUEUE *Method_Dequeue(QUEUE *self, QUEUE_NODE *);
QUEUE *Method_EmptyQueue(QUEUE *self);

int main(int argc, char **argv)
{
	return 0;
}

QUEUE Constructor_Queue(QUEUE *self)
{
	QUEUE retQueue;
	//When the return value of constructor is used.
	if (self == NULL){
		retQueue.begin = NULL;
		retQueue.end = NULL;
		retQueue.Enqueue = &Method_Enqueue;
		retQueue.Dequeue = &Method_Dequeue;
		retQueue.EmptyQueue = &Method_EmptyQueue;

		return retQueue;
	}

	//When the side effect of constructor is used.
	memset(&retQueue, 0x00, sizeof(retQueue));
	if (self == NULL){
		DEBUG("ERROR: Unexpected Situation Occured.\n");
		return retQueue;
	}
	self->begin = NULL;
	self->end = NULL;
	self->Enqueue = &Method_Enqueue;
	self->Dequeue = &Method_Dequeue;
	self->EmptyQueue = &Method_EmptyQueue;

	return retQueue;
}

int Destructor_Queue(QUEUE *self)
{
	//Exception Handling
	if (self == NULL){
		DEBUG("ERROR: self is NULL.\n");
		return -1;
	}

	(self->EmptyQueue)(self);

	return 0;
}

QUEUE *Method_Enqueue(QUEUE *self, char *dataArg, unsigned int levelArg)
{
	//Exception Handling
	if (self == NULL){
		DEBUG("ERROR: self is NULL.\n");
		return NULL;
	}

	//When the queue is empty
	if (self->begin==NULL && self->end==NULL){
		self->begin = (QUEUE_NODE *)malloc(sizeof(QUEUE_NODE));
		self->end = self->begin;
		strncpy(self->begin->data, dataArg, STRING_LEN);
		self->begin->level = levelArg;
		self->begin->next = NULL;
		self->begin->prev = NULL;
		return self;
	}

	//Exception Handling
	if (self->end->next != NULL){
		DEBUG("ERROR: end->next is Not NULL.\n");
		return NULL;
	}
	self->end->next = (QUEUE_NODE *)malloc(sizeof(QUEUE_NODE));
	if (self->end->next == NULL){
		DEBUG("ERROR: malloc() failed.\n");
		return NULL;
	}
	strncpy(self->end->next->data, dataArg, STRING_LEN);
	self->end->next->level = levelArg;
	self->end->next->next = NULL;
	self->end->next->prev = self->end;
	self->end = self->end->next;

	return self;
}

QUEUE *Method_Dequeue(QUEUE *self, QUEUE_NODE *outputStore)
{
	//Exception Handling1
	if (self == NULL){
		DEBUG("ERROR: self is NULL.\n");
		return NULL;
	}

	//Exception Handling2
	if (outputStore == NULL){
		DEBUG("ERROR: outputStore is NULL.\n");
		return NULL;
	}

	outputStore->next = NULL;
	outputStore->prev = NULL;

	//When the queue is empty.
	if (self->begin == NULL && self->end == NULL){
		return NULL;
	}

	//When the queue has only an element.
	if (self->begin == self->end){
		strncpy(outputStore->data, self->begin->data, STRING_LEN);
		outputStore->level = self->begin->level;
		free(self->begin);
		self->begin = NULL;
		self->end = NULL;
		return self;
	}

	strncpy(outputStore->data, self->end->data, STRING_LEN);
	outputStore->level = self->end->level;
	self->end = self->end->prev;
	if (self->end == NULL){DEBUG("ERROR: Unexpected Situation Occured.\n"); return NULL;}
	free(self->end->next);
	self->end->next = NULL;
	return self;
}

QUEUE *Method_EmptyQueue(QUEUE *self)
{
	QUEUE_NODE buf;
	QUEUE *bufP;

	//Exception Handling
	if (self == NULL){
		DEBUG("ERROR: self is NULL.\n");
		return NULL;
	}

	while(1){
		bufP = self->Dequeue(self, &buf);
		if (bufP == NULL)
			break;
	}
	
	return self;
}

