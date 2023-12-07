#include "search.hh"

std::string strOutIndex("OUT_OF_INDEX");
std::string strSearchFail("SEARCH_FAIL");
NODE gOutIndex(strOutIndex);
NODE gSearchFail(strSearchFail);
static const char letterCollection[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

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
	(*this).name.clear();
	(*this).number = 0;

	return ;
}

NODE *NODE::Random(void)
{
	int len = 0;

	len = rand()%8;
	while(len == 0){
		len = rand()%8;
	}

	(*this).name.clear();
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

	if (indexArg >= (*this).size){
		return gOutIndex;
	}

	temp = this->begin;
	for (int i=0 ; i<indexArg ; i++){
		temp = temp->next;
	}

	return *temp;
}

int LIST::Size(void)
{
	return (*this).size;
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
		COUT << "ERROR: sizeArg is smaller than 1." << std::endl;
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

	//When the list is empty
	if (this->size == 0){
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

void LIST::Print(void)
{
	NODE *temp = NULL;
	int index = 0;

	//WHen the list is empty currently.
	if (this->size == 0){
		std::cout << std::endl;
		return ;
	}

	index = 0;
	temp = this->begin;

	while(temp != NULL){
		std::cout << "[" << index << "]" << "Name: " << temp->name << " Number: " << temp->number << std::endl;
		temp = temp->next;
		index ++;
	}
	std::cout << std::endl;

	return ;
}

class Comparator {
public:
	bool operator()(NODE &front, NODE &rear)
	{
		if (strcmp(front.name.c_str(), rear.name.c_str()) < 0){
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
	for (int i=0 ; i<(this->size) ; i++){
		buffer.push_back(*temp);
		temp = temp->next;
	}

	std::sort(buffer.begin(), buffer.end(), Comparator());

	temp = this->begin;
	for (int i=0 ; i<(this->size) ; i++){
		temp->name = buffer[i].name;
		temp->number = buffer[i].number;
		temp = temp->next;
	}

	return this;
}

NODE &LIST::Search(std::string &nameArg)
{
	int index = 0;
	NODE *temp = NULL;
	int stepSize = 0;
	int cmpResult = 0;

	index = 0;
	temp = this->begin;
	stepSize = FindSqrt(this->size);

	while(1){
		cmpResult = strcmp(((temp->name).c_str)(), nameArg.c_str());
		if (cmpResult == 0){
			return *temp;
		}
		else if (cmpResult > 0){
			break;//Stop Jumping!
		}
		else if (cmpResult < 0){
			if (index + stepSize < this->size){
				//Jump!
				index = index + stepSize;
				for (int i=0 ; i<stepSize ; i++){
					temp = temp->next;
				}
				continue;
			}
			else {
				//When you can't jump anymore.
				for (int i=0 ; i<(this->size)-index-1 ; i++){
					temp = temp->next;
					cmpResult = strcmp(((temp->name).c_str)(), nameArg.c_str());
					if (cmpResult == 0){
						return *temp;
					}
					else if (cmpResult > 0){
						return gSearchFail;
					}
					else if (cmpResult < 0){
						temp = temp->next;
					}
				}
				return gSearchFail;
			}
		}
	}

	if (index == 0){
		//When even the first element is bigger than the value that you are searching for.
		return gSearchFail;
	}

	for (int i=0 ; i<stepSize-1 ; i++){
		temp = temp->prev;
		cmpResult = strcmp(((temp->name).c_str)(), nameArg.c_str());
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

int FindSqrt(int arg)
{
	unsigned long long int begin=0, end=0, mid=0;
	unsigned long long int longArg = (unsigned long long int)(arg);

	end = longArg/2;
	
	while(begin <= end){
		mid = (begin + end)/2;

		if (mid*mid == longArg){
			return mid;
		}
		else if (mid*mid < longArg){
			begin = mid + 1;
			continue;
		}
		else if (mid*mid > longArg){
			end = mid - 1;
			continue;
		}
	}

	if (mid*mid > longArg){
		mid --;
	}

	return mid;
}
