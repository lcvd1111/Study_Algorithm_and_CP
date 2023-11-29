#include "search.hh"

//File-scope variable
static const char *letterCollection = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

//Function Defintions
NODE::_NODE(void)
{
	(*this).name.clear();
	(*this).number = 0;
	(*this).prev = (*this).next = NULL;

	return ;
}

NODE::~_NODE(void)
{
	return ;
}

NODE *NODE::Random(void)
{
	int length = rand()%(NAME_LEN/2);
	length += 2;

	(this->name).clear();

	for (int i=0 ; i<length ; i++){
		this->name += letterCollection[rand()%62];
	}
	this->number = rand()%100000;

	return this;
}

LIST::_LIST(void)
{
	srand((unsigned int)time(NULL));
	this->begin = this->end = NULL;
	this->size = 0;

	return ;
}

LIST::~_LIST(void)
{
	(*this).Clear();
	return ;
}

LIST *LIST::AddRandom(void)
{
	//When the list is empty currently.
	if (this->size == 0){
		//Exception Handling
		if (this->begin != NULL || this->end != NULL){
			COUT_ERROR << "ERROR: Unexpected situation has occurred" << std::endl;
			return NULL;
		}

		this->begin = new NODE;
		this->end = begin;
		(this->begin->Random)();
		this->size += 1;
		return this;
	}

	//When the list is not empty currently.
	if (this->end->next != NULL){
		//Exception Handling
		COUT_ERROR << "ERROR: end->next is not NULL." << std::endl;
		return NULL;
	}

	this->end->next = new NODE;
	(this->end->next->Random)();
	this->end->next->prev = this->end;
	this->end = this->end->next;
	this->size += 1;

	return this;
}

LIST *LIST::AddRandom(int addSizeArg)
{
	//Exception Handling
	if (addSizeArg < 1){
		COUT_ERROR << "ERROR: addSizeArg < 1" << std::endl;
		return NULL;
	}

	for (int i=0 ; i<addSizeArg ; i++){
		(*this).AddRandom();
	}

	return this;
}

LIST *LIST::ChangeRandomElement(std::string &nameArg, int numberArg)
{
	int index = 0;

	//When the list is empty currently.
	if (this->size == 0){
		return NULL;
	}

	index = rand() % (this->size);
	(*this)[index].name = nameArg;
	(*this)[index].number = numberArg;

	return this;
}

NODE *LIST::Search(std::string &nameArg)
{
	//O(n)
	NODE *ret = NULL;

	ret = this->begin;
	while(ret != NULL){
		if (ret->name == nameArg){
			return ret;
		}
		ret = ret->next;
	}

	//O(n^2)
	/*
	for (int i=0 ; i<(this->size) ; i++){
		if ((*this)[i].name == nameArg){
			return &((*this)[i]);
		}
	}
	*/

	return NULL;
}

LIST *LIST::Clear(void)
{
	NODE *currentNode = NULL;
	NODE *nextNode = NULL;

	//When the list is empty currently.
	if (this->size == 0){
		if (this->begin != NULL || this->end != NULL){
			COUT_ERROR << "ERROR: Unexpected situation has occured." << std::endl;
			return NULL;
		}
		return NULL;
	}

	//Exception Handling
	if (this->begin == NULL || this->end == NULL){
		COUT_ERROR << "ERROR: Unexpected situation has occured.\n" << std::endl;
		return NULL;
	}

	currentNode = this->begin;
	while(currentNode != NULL){
		nextNode = currentNode->next;
		delete(currentNode);
		currentNode = nextNode;
	}

	this->size = 0;

	return this;
}

void LIST::Print(void)
{
	//When the list is empty currently.
	if (this->size == 0){
		return ;
	}

	for (int i=0 ; i<(this->size) ; i++){
		std::cout << "[" << i << "] Name: " << (*this)[i].name << " Number: " << (*this)[i].number << std::endl;
	}

	return ;
}

NODE &LIST::operator[](int indexArg)
{
	NODE *temp = NULL;

	if (indexArg >= this->size){
		COUT_ERROR << "ERROR: index is over the proper range." << std::endl;
		if (this->size == 0){
			(*this).AddRandom();
		}
		NODE &ret = *(this->end);
		return ret;
	}

	temp = this->begin;
	for (int i=0 ; i<indexArg ; i++){
		temp = temp->next;
	}

	NODE &ret = *temp;
	return ret;
}
