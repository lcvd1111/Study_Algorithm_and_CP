#include "search.hh"

std::string searchFailString("SEARCH_FAIL");
std::string outIndexString("OUT_OF_INDEX");
NODE gSearchFail(searchFailString, -1);
NODE gOutIndex(outIndexString, -2);
static const char letterCollection[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

//Function Definitions
//NODE class's memberfunctions
NODE::NODE(void)
{
	(this->name).clear();
	this->number = 0;
	this->prev = NULL;
	this->next = NULL;

	return ;
}

NODE::NODE(std::string &nameArg, int numArg)
{
	this->name = nameArg;
	this->number = numArg;
	this->prev = NULL;
	this->next = NULL;

	return ;
}

NODE::~NODE(void)
{
	(this->name).clear();
	return ;
}


NODE *NODE::Random(void)
{
	int len = 0;

	(this->name).clear();
	len = rand() % 8;
	
	while (len == 0){
		len = rand() % 8;
	}

	for (int i=0 ; i<len ; i++){
		(this->name) += letterCollection[rand()%62];
	}
	this->number = rand()%10000;
	while (this->number == 5555){
		this->number = rand()%10000;
	}

	return NULL;
}

//LIST class's memberfunctions
LIST::LIST(void)
{
	this->size = 0;
	this->begin = this->end = NULL;

	srand((unsigned int)time(NULL));

	return ;
}

LIST::~LIST(void)
{
	NODE *temp=NULL, *temp_next=NULL;

	//When the list is empty curretly.
	if ((*this).Size() == 0){
		if (this->begin != NULL || this->end != NULL){
			//Exception Handling
			COUT_ERROR << "ERROR: Unexpected situation occured." << std::endl;
			return;
		}
		return ;
	}

	temp = this->begin;

	while(temp != NULL){
		temp_next = temp->next;
		delete temp;
		temp = temp_next;
	}

	this->size = 0;

	return ;
}

NODE &LIST::operator[](int indexArg)
{
	NODE *temp = NULL;

	//Exception Handling
	if (indexArg >= (*this).Size()){
		COUT_ERROR << "ERROR: indexArg >= size." << std::endl;
		return gOutIndex;
	}

	temp = this->begin;
	for (int i=0 ; i<indexArg ; i++){
		temp = temp->next;
	}

	return *(temp);
}

int LIST::Size(void)
{
	return (this->size);
}

LIST *LIST::AddRandom(void)
{
	//When the list is empty currently.
	if ((*this).Size() == 0){
		if (this->begin != NULL || this->end != NULL){
			//Exception Handling
			COUT_ERROR << "ERROR: Unexpected situation occured." << std::endl;
			return NULL;
		}
		this->begin = this->end = new NODE;
		(this->begin->Random)();
		this->size += 1;

		return this;
	}

	//when the list is not empty currently.
	if (this->end->next != NULL){
		//Exception Handling
		COUT_ERROR << "ERROR: Unexpected situation occured." << std::endl;
		return NULL;
	}
	this->end->next = new NODE;
	(this->end->next->Random)();
	this->end->next->prev = this->end;
	this->end = this->end->next;
	this->size += 1;

	return this;
}

LIST *LIST::AddRandom(int sizeArg)
{
	//Exception Handling
	if (sizeArg < 1){
		COUT_ERROR << "ERROR: sizeArg < 1." << std::endl;
		return NULL;
	}

	for (int i=0 ; i<sizeArg ; i++){
		(*this).AddRandom();
	}

	return NULL;
}

class Comparator {
public:
	bool operator()(NODE &front, NODE &rear){
		if (front.number < rear.number){
			return true;
		}
		return false;
	}
};

LIST *LIST::ChangeRandomElement(std::string &nameArg, int numArg)
{
	int index = 0;

	//When the list is empty currently.
	if ((*this).Size() == 0){
		return this;
	}

	index = rand()%((*this).Size());

	(*this)[index].name = nameArg;
	(*this)[index].number = numArg;

	return this;
}

LIST *LIST::Sort(void)
{
	std::vector<NODE> buffer;
	NODE *temp = NULL;

	//When the list is empty currently.
	if ((*this).Size() == 0){
		if (this->begin != NULL || this->end != NULL){
			//Exception Handling
			COUT_ERROR << "ERROR: Unexpected situation occured." << std::endl;
			return NULL;
		}
		return NULL;
	}

	temp = this->begin;
	buffer.clear();
	while(temp != NULL){
		buffer.push_back(*temp);
		temp = temp->next;
	}

	std::sort(buffer.begin(), buffer.end(), Comparator());
	temp = this->begin;
	for (std::vector<NODE>::iterator i=buffer.begin() ; i!=buffer.end() ; i++){
		temp->name = i->name;
		temp->number = i->number;
		temp = temp->next;
	}

	return this;
}

void LIST::Print(void)
{
	NODE *temp = NULL;
	int i=0;

	//When the list is empty currently.
	if ((*this).Size() == 0){
		if (this->begin != NULL || this->end != NULL){
			//Exception Handling
			COUT_ERROR << "ERROR: Unexpected situation occured." << std::endl;
			return;
		}
		std::cout << std::endl;
		return;
	}
	
	temp = this->begin;
	while (temp!=NULL){
		std::cout << "[" << i << "]" << "Name: " << temp->name << " Number: " << temp->number << std::endl;
		i++;
		temp = temp->next;
	}

	if (i != (*this).Size()){
		COUT_ERROR << "ERROR: Unexpected situation occured." << std::endl;
		return ;
	}
	
	std::cout << std::endl;

	return ;
}

NODE &LIST::Search(int numArg)
{
	int beginIndex=0, endIndex=0, midIndex=0;
	NODE *beginNode=NULL, *endNode=NULL, *midNode = NULL;

	//When the list is empty currently.
	if ((*this).Size() == 0){
		if (this->begin != NULL || this->end != NULL){
			//Exception Handling
			COUT_ERROR << "ERROR: Unexpected situation occured." << std::endl;
			return gSearchFail;
		}
		return gSearchFail;
	}
	
	beginIndex = 0;
	endIndex = (*this).Size()-1;
	midIndex = 0;

	while(beginIndex <= endIndex){
		beginNode = this->begin;
		for (int i=0 ; i<beginIndex ; i++){
			beginNode = beginNode->next;
		}

		endNode = beginNode;
		for (int i=0 ; i<(endIndex-beginIndex) ; i++){
			endNode = endNode->next;
		}

		if (numArg < beginNode->number || numArg > endNode->number){
			return gSearchFail;
		}

		midIndex = beginIndex 
					+(endIndex - beginIndex)
					*(numArg - beginNode->number)
					/(endNode->number - beginNode->number);

		midNode = beginNode;
		for (int i=0 ; i<(midIndex-beginIndex) ; i++){
			midNode = midNode->next;
		}

		if (midNode->number == numArg){
			return *midNode;
		}
		else if (midNode->number > numArg){
			endIndex = midIndex - 1;
			continue;
		}
		else if (midNode->number < numArg){
			beginIndex = midIndex + 1;
			continue;
		}
	}

	return gSearchFail;
}
