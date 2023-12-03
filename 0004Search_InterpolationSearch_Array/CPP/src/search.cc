#include "search.hh"

#define NAME_LEN 32;

//Creating File-Scope variables
static const char letterCollection[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
NODE gSearchFail(std::string("SEARCH_FAIL"));
NODE gOutIndex(std::string("OUT_OF_INDEX"));

//Function Definitions
//NODE class methods
NODE::NODE(void)
{
	(this->name).clear();
	this->number = 0;
	return ;
}

NODE::NODE(std::string nameArg)
{
	this->name = nameArg;
	this->number = 0;
	return ;
}

NODE::~NODE(void)
{
	return ;
}

NODE *NODE::Random(void)
{
	int len = rand()%8;
	len += 1;
	(this->name).clear();
	for (int i=0 ; i<len ; i++){
		(this->name) += letterCollection[rand()%62];
	}
	this->number = rand()%10000;
	if (this->number == 777){
		this->number += 1;
	}

	return this;
}

//ARRAY class methods
ARRAY::ARRAY(void)
{
	srand((unsigned int)time(NULL));
	(this->nodeVector).clear();

	return ;
}

ARRAY::~ARRAY(void)
{
	(this->nodeVector).clear();
	return ;
}

NODE &ARRAY::operator[](int indexArg)
{
	//Exception Handling
	if (indexArg >= (*this).Size()){
		return gOutIndex;
	}

	return (this->nodeVector)[indexArg];
}

int ARRAY::Size(void)
{
	return (this->nodeVector).size();
}

ARRAY *ARRAY::AddRandom(void)
{
	NODE temp;
	temp.Random();
	(this->nodeVector).push_back(temp);
	return this;
}

ARRAY *ARRAY::AddRandom(int sizeArg)
{
	//Exception Handling
	if (sizeArg < 1){
		COUT << "ERROR: sizeArg < 1." << std::endl;
	}

	for (int i=0 ; i<sizeArg ; i++){
		(*this).AddRandom();
	}

	return this;
}

ARRAY *ARRAY::ChangeRandomElement(std::string &nameArg, int numArg)
{
	int randomIndex = rand() % ((*this).Size());
	(this->nodeVector)[randomIndex].name = nameArg;
	(this->nodeVector)[randomIndex].number = numArg;

	return this;
}

class COMPARATOR {
public:
	bool operator()(NODE &front, NODE &rear){
		if (front.number < rear.number){
			return true;
		}
		return false;
	}
};

ARRAY *ARRAY::Sort(void)
{
	std::sort((this->nodeVector).begin()
				,(this->nodeVector).end()
				,COMPARATOR());

	return this;
}

void ARRAY::Print(void)
{
	for (std::vector<NODE>::iterator i=(this->nodeVector).begin()
			; i!=(this->nodeVector).end()
			; i++){
		std::cout << "[Name] " << i->name << " [Number]" << i->number << std::endl;
	}
	std::cout << std::endl;
	return ;
}

NODE &ARRAY::Search(int numArg)
{
	int beginIndex=0, endIndex=0, midIndex=0;
	
	endIndex = (*this).Size() - 1;
	if ((*this)[beginIndex].number > numArg
			|| (*this)[endIndex].number < numArg)
	{
		return gSearchFail;
	}

	while(beginIndex <= endIndex){
		midIndex = beginIndex + (endIndex-beginIndex)*(numArg-(*this)[beginIndex].number)/((*this)[endIndex].number-(*this)[beginIndex].number);

		if ((*this)[midIndex].number == numArg){
			return (*this)[midIndex];
		}
		else if ((*this)[midIndex].number > numArg){
			endIndex = midIndex - 1;
			continue;
		}
		else if ((*this)[midIndex].number < numArg){
			beginIndex = midIndex + 1;
			continue;
		}
	}

	return gSearchFail;
}
