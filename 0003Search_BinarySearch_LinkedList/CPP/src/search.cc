#include "search.hh"
NODE gSearchFail; 
NODE gOutIndex; 
static const char letterCollection[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

NODE::NODE(void)
{
	(this->name).clear();
	this->number = 0;
	this->prev = this->next = NULL;

	return ;
}

NODE::~NODE(void)
{
	(this->name).clear();
	this->number = 0;

	return ;
}

NODE *NODE::Random(void)
{
	int len = random()%6;
	len += 1;

	(this->name).clear();
	for (int i=0 ; i<len ; i++){
		(this->name) += letterCollection[rand()%62];
	}
	this->number = rand() % 10000;

	return this;
}

LIST::LIST(void)
{
	srand((unsigned int)time(NULL));

	gSearchFail.name = "SEARCH_FAIL";
	gSearchFail.number = -1;
	gOutIndex.name = "OUT_OF_INDEX";
	gOutIndex.number = -2;

	this->begin = this->end = NULL;
	this->size = 0;

	return ;
}

LIST::~LIST(void)
{
	NODE *temp = NULL;
	NODE *temp_next = NULL;

	if (this->size == 0){
		return ;
	}

	temp = this->begin;
	while (temp != NULL){
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
	if (indexArg >= this->size){
		return gOutIndex;
	}

	temp = this->begin;
	for (int i=0 ; i<indexArg ; i++){
		temp = temp->next;
	}

	return *temp;
}

void LIST::Print(void)
{
	NODE *temp = NULL;

	//When the list is currently empty.
	/*
	if (this->size == 0){
		return ;
	}
	*/

	temp = this->begin;
	while(temp != NULL){
		std::cout << "[Name]: " << temp->name << " [Number]: " << temp->number << std::endl;
		temp = temp->next;
	}
	std::cout << std::endl;

	return ;
}

LIST *LIST::AddRandom(void)
{
	//When the list is empty currently.
	if (this->size == 0){
		if (this->begin != NULL || this->end != NULL){
			//Exception Handling
			COUT_ERROR << "ERROR: Unexpected situation occured." << std::endl;
			return NULL;
		}
		this->begin = this->end = new NODE;
		(this->begin->Random)();
		this->size = 1;
		return this;
	}

	//When the list is not empty currently.
	if (this->end->next != NULL){
		//Exception Handling
		COUT_ERROR << "ERROR: Unexpected situation occured." << std::endl;
		return NULL;
	}
	this->end->next = new NODE;
	this->end->next->prev = this->end;
	(this->end->next->Random)();
	this->end = this->end->next;
	this->size += 1;

	return this;
}

LIST *LIST::AddRandom(int sizeArg)
{
	//Exception Handling
	if (sizeArg < 1){
		COUT_ERROR << "ERROR: sizeArg is smaller than 1." << std::endl;
		return NULL;
	}

	for (int i=0 ; i<sizeArg ; i++){
		(this->AddRandom)();
	}

	return NULL;
}

LIST *LIST::ChangeRandomElement(std::string &nameArg, int numArg)
{
	int index = rand() % (this->size);
	NODE &temp = (*this)[index];
	temp.name = nameArg;
	temp.number = numArg;
	return this;
}

class COMPARATOR {
public:
	bool operator()(NODE &, NODE &);
};
bool COMPARATOR::operator()(NODE &front, NODE &rear)
{
	const char *frontStr = front.name.c_str();
	const char *rearStr = rear.name.c_str();
	if (strcmp(frontStr, rearStr) < 0){
		return true;
	}
	return false;
}

LIST *LIST::Sort(void)
{
	std::vector<NODE> buffer;
	NODE *temp = NULL;

	//When the list is empty.
	if (this->size == 0){
		return NULL;
	}

	temp = this->begin;
	for (int i=0 ; i<this->size ; i++){
		buffer.push_back(*temp);
		temp = temp->next;
	}

	if (temp != NULL){
		COUT_ERROR << "ERROR: Unexpected sitaution occured." << std::endl;
	}

	std::sort(buffer.begin(), buffer.end(), COMPARATOR());

	temp = this->begin;
	for (int i=0 ; i<this->size ; i++){
		temp->name = buffer[i].name;
		temp->number = buffer[i].number;
		temp = temp->next;
	}

	if (temp != NULL){
		COUT_ERROR << "ERROR: Unexpected sitaution occured." << std::endl;
	}

	return this;
}

NODE &LIST::Search(std::string &nameArg)
{
	int beginIndex=0, endIndex=0, midIndex=0;
	int midIndex_next = 0;
	NODE *midNode = NULL;
	int cmpResult = 0;

	beginIndex = 0;
	endIndex = this->size - 1;
	midIndex = 0;
	midNode = this->begin;
	while(beginIndex <= endIndex){
		midIndex_next = (beginIndex + endIndex)/2;
		if (midIndex == midIndex_next){
			if (strcmp(midNode->name.c_str(), nameArg.c_str())){
				return *midNode;
			}
			else {
				break;
			}
		}
		else if (midIndex < midIndex_next){
			for (int i=0 ; i<midIndex_next-midIndex ; i++){
				midNode = midNode->next;
			}
		}
		else if (midIndex > midIndex_next){
			for (int i=0 ; i<midIndex-midIndex_next ; i++){
				midNode = midNode->prev;
			}
		}

		midIndex = midIndex_next;
		cmpResult = strcmp(midNode->name.c_str(), nameArg.c_str());
		if (cmpResult==0){
			return *midNode;
		}
		else if (cmpResult > 0){
			endIndex = midIndex-1;
			continue;
		}
		else if (cmpResult < 0){
			beginIndex = midIndex+1;
			continue;
		}
	}
	return gSearchFail;
}
