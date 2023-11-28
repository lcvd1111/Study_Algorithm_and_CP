#include "search.h"

//Function Definitions
void NODE_CONSTRUCTOR(NODE *this)
{
	memset(this->name, 0, NAME_LEN);
	return ;
}

void NODE_DESTRUCTOR(NODE *this)
{
	return ;
}

NODE *NODE_METHOD_Random(NODE *this)
{
	return this;
}

void LIST_CONSTRUCTOR(LIST *this)
{
	return ;
}

void LIST_DESTRUCTOR(LIST *this)
{
	return ;
}

LIST *LIST_METHOD_Add(LIST *this)
{
	return this;
}

LIST *LIST_METHOD_Change(LIST *this, char *nameArg, int numArg)
{
	return this;
}

NODE *LIST_METHOD_Index(LIST *this, int indexArg)
{
	NODE *ret = NULL;
	return ret;
}
