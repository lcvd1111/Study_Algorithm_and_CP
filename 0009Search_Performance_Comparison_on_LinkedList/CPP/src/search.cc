#include "search.hh"

static const char letterCollection[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
std::string gStrOutIndex("OUT_OF_INDEX");
std::string gStrSearchFail("SEARCH_FAIL");
NODE gOutIndex(gStrOutIndex);
NODE gSearchFail(gStrSearchFail);

NODE::NODE(void)
{
	(*this).name.clear();
	(*this).number = 0;
	(*this).prev = (*this).next = NULL;

	return ;
}

NODE::NODE(std::string &nameArg)
{
	(*this).name = nameArg;
	(*this).number = 0;
	(*this).prev = (*this).next = NULL;

	return ;
}

NODE::~NODE(void)
{
	return ;
}

NODE *NODE::Random(void)
{
	int len = 0;
	
	len = rand() % 8;
	while(len == 0){
		len = rand() % 8;
	}

	for (int i=0 ; i<len ; i++){
		(*this).name += letterCollection[rand()%62];
	}
	(*this).number = rand()%10000;

	return this;
}

LIST::LIST(void)
{
	srand((unsigned int)time(NULL));
	(*this).begin = (*this).end = NULL;
	(*this).size = 0;

	return;
}

LIST::~LIST(void)
{
	NODE *temp=NULL, *temp_next=NULL;

	//When the list is empty currently.
	if (this->size == 0){
		return ;
	}

	//When the list is not empty currently.
	temp = this->begin;
	while(temp != NULL){
		temp_next = temp->next;
		delete temp;
		temp = temp_next;
	}

	return ;
}

NODE &LIST::operator[](int indexArg)
{
	NODE *temp = NULL;

	//Exception Handling
	if (indexArg >= (*this).size){
		COUT_ERROR << "ERROR: indexArg >= size" << std::endl;
		return gOutIndex;
	}

	temp = this->begin;

	for (int i=0 ; i<indexArg ; i++){
		temp = temp->next;
	}
	
	return *temp;
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
		(*((*this).begin)).Random();
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
	(*(this->end->next)).Random();
	this->end->next->prev = this->end;
	this->end = this->end->next;
	this->size += 1;

	return this;
}

LIST *LIST::AddRandom(int sizeArg)
{
	//Exception Handling
	if (sizeArg < 1){
		COUT_ERROR << "ERROR: sizeArg < 1" << std::endl;
		return NULL;
	}

	for (int i=0 ; i<sizeArg ; i++){
		(*this).AddRandom();
	}

	return this;
}

LIST *LIST::ChangeRandomElement(std::string &nameArg, int numArg)
{
	int index = 0;
	NODE *temp = NULL;

	//When the list is empty currently.
	if (this->size == 0){
		if (this->begin != NULL || this->end != NULL){
			//Exception Handling
			COUT_ERROR << "ERROR: Unexpected situation occured." << std::endl;
			return NULL;
		}
		return NULL;
	}

	index = rand()%(this->size);
	temp = this->begin;

	for (int i=0 ; i<index ; i++){
		temp = temp->next;
	}

	temp->name = nameArg;
	temp->number = numArg;

	return this;
}

class Comparator {
public:
	bool operator()(NODE &front, NODE &rear)
	{
		int cmpResult = 0;
		cmpResult = strcmp(front.name.c_str(), rear.name.c_str());
		if (cmpResult > 0){
			return false;
		}
		else if (cmpResult < 0){
			return true;
		}
		return false;
	}
};

LIST *LIST::Sort(void)
{
	std::vector<NODE> buffer;
	NODE *temp = NULL;

	//When the list is empty currently.
	if (this->size == 0){
		return NULL;
	}

	temp = this->begin;
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

LIST *LIST::Print(void)
{
	NODE *temp = NULL;
	int i = 0;

	//When the list is empty currently.
	if (this->size == 0){
		std::cout << std::endl;
		return NULL;
	}

	temp = this->begin;

	while(temp != NULL){
		std::cout << "[" << i << "]" << "Name: " << temp->name << " Number: " << temp->number << std::endl;
		temp = temp->next;
	}
	std::cout << std::endl;

	return this;
}

NODE &LIST::LinearSearch(std::string &nameArg)
{
	NODE *temp = NULL;

	//When the list is empty currently.
	if (this->size == 0){
		if (this->begin != NULL || this->end != NULL){
			//Exception Handling
			COUT_ERROR << "ERROR: Unexpected situation occured." << std::endl;
			return gSearchFail;
		}
		return gSearchFail;
	}

	temp = this->begin;

	while(temp != NULL){
		if (strcmp((*temp).name.c_str(), nameArg.c_str()) == 0){
			return *temp;
		}
		temp = temp->next;
	}

	return gSearchFail;
}

int FindSqrt(int arg)
{
	unsigned long long int begin=0, end=0, mid=0;
	unsigned long long int longArg = (unsigned long long int)arg;

	end = longArg/2;

	while(begin <= end){
		mid = (begin+end)/2;
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
		mid--;
	}

	return (int)mid;
}

NODE &LIST::JumpSearch(std::string &nameArg)
{
	int index = 0;
	NODE *temp = NULL;
	int cmpResult = 0;
	int stepSize = 0;

	//When the list is empty currently.
	if (this->size == 0){
		return gSearchFail;
	}

	temp = this->begin;
	index = 0;
	stepSize = FindSqrt(this->size);

	while(1){
		cmpResult = strcmp((temp->name).c_str(), nameArg.c_str());
		if (cmpResult == 0){
			return *temp;
		}
		else if (cmpResult > 0){
			//Stop Jump.
			break;
		}
		else if (cmpResult < 0){
			if (index + stepSize < (this->size)){
				//Jump.
				index = index + stepSize;
				for (int i=0 ; i<stepSize ; i++){
					temp = temp->next;
				}
				continue;
			}
			else {
				//When you can't jump anymore.
				for (int i=0 ; i<(*this).size-index-1 ; i++){
					temp = temp->next;
					cmpResult = strcmp((temp->name).c_str(), nameArg.c_str());
					if (cmpResult == 0){
						return *temp;
					}
					else if (cmpResult > 0){
						return gSearchFail;
					}
					else if (cmpResult < 0){
						continue;
					}
				}
			}
		}
	}

	//When the first element is bigger than the value that you are searching for.
	if (index == 0){
		return gSearchFail;
	}

	//Backwarding the block.
	for (int i=0 ; i<stepSize-1 ; i++){
		temp = temp->prev;
		cmpResult = strcmp((temp->name).c_str(), nameArg.c_str());
		if (cmpResult == 0){
			return *temp;
		}
		else if (cmpResult > 0){
			continue;
		}
		else if (cmpResult < 0){
			return gSearchFail;
		}
	}

	return gSearchFail;
}

NODE &LIST::BinarySearch(std::string &nameArg)
{
	int beginIndex=0, endIndex=0, midIndex=0;
	int midIndex_next = 0;
	int cmpResult = 0;
	NODE *temp = NULL;

	//When the list is empty currently.
	if (this->size == 0){
		return gSearchFail;
	}

	beginIndex = 0;
	endIndex = (*this).size-1;
	midIndex = 0;
	temp = this->begin;

	while(beginIndex <= endIndex){
		midIndex_next = (beginIndex + endIndex)/2;
		if (midIndex_next == midIndex){
			COUT_ERROR << "ERROR: Unexpected situation occured." << std::endl;
		}
		else if (midIndex_next > midIndex){
			for (int i=0 ; i<midIndex_next-midIndex ; i++){
				temp = temp->next;
			}
		}
		else if (midIndex_next < midIndex){
			for (int i=0 ; i<midIndex-midIndex_next ; i++){
				temp = temp->prev;
			}
		}
		midIndex = midIndex_next;

		cmpResult = strcmp((temp->name).c_str(), nameArg.c_str());
		if (cmpResult == 0){
			return *temp;
		}
		else if (cmpResult > 0){
			endIndex = midIndex - 1;
			continue;
		}
		else if (cmpResult < 0){
			beginIndex = midIndex + 1;
			continue;
		}
	}

	return gSearchFail;
}
