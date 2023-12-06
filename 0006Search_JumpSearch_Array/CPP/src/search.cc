#include "search.hh"

std::string strOutIndex("OUT_OF_INDEX");
std::string strSearchFail("SEARCH_FAIL");
NODE gOutIndex;
NODE gSearchFail;
static const char letterCollection[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890";

NODE::NODE(void)
{
	(*this).name.clear();
	(*this).number = 0;

	return ;
}

NODE::NODE(std::string &nameArg)
{
	(*this).name = nameArg;
	(*this).number = 0;
	return ;
}

NODE::~NODE(void)
{
	return ;
}

NODE *NODE::Random(void)
{
	int len = 0;
	len = rand()%8;
	if (len == 0){
		len = rand()%8;
	}

	for (int i=0 ; i<len ; i++){
		(*this).name += letterCollection[rand()%62];
	}

	this->number = rand()%10000;

	return this;
}

ARRAY::ARRAY(void)
{
	srand((unsigned int)time(NULL));
	(*this).nodeVector.clear();

	return ;
}

ARRAY::~ARRAY(void)
{
	(*this).nodeVector.clear();

	return ;
}

NODE &ARRAY::operator[](int indexArg)
{
	int size = (*this).Size();

	//Exception Handling
	if (indexArg >= size){
		COUT_ERROR << "ERROR: index is over the range." << std::endl;
		return gOutIndex;
	}

	return (*this).nodeVector[indexArg];
}

int ARRAY::Size(void)
{
	return ((*this).nodeVector.size());
}

ARRAY *ARRAY::AddRandom(void)
{
	NODE newNode;
	newNode.Random();
	(*this).nodeVector.push_back(newNode);

	return NULL;
}

ARRAY *ARRAY::AddRandom(int sizeArg)
{
	//Exception Handling
	if (sizeArg < 1){
		COUT_ERROR << "ERROR: sizeArg < 1" << std::endl;
		return NULL;
	}

	for (int i=0 ; i<sizeArg ; i++){
		(*this).AddRandom();
	}

	return NULL;
}

ARRAY *ARRAY::ChangeRandomElement(std::string &nameArg, int numArg)
{
	int randomIndex = 0;
	randomIndex = rand()%((*this).Size());

	(*this).nodeVector[randomIndex].name = nameArg;
	(*this).nodeVector[randomIndex].number = numArg;

	return NULL;
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

ARRAY *ARRAY::Sort(void)
{
	//When the array is empty currently.
	if ((*this).Size() == 0){
		return NULL;
	}

	std::sort((*this).nodeVector.begin(), (*this).nodeVector.end(), Comparator());

	return this;
}

NODE &ARRAY::Search(std::string &nameArg)
{

	return gSearchFail;
}

void ARRAY::Print(void)
{
	for (std::vector<NODE>::iterator i=(*this).nodeVector.begin() ; i!=(*this).nodeVector.end() ; i++){
		std::cout << COLOR_BLACK << "[" << (int)(i-(*this).nodeVector.begin()) << "] <Name>: " << i->name << " <Number>: " << i->number << COLOR_BLACK << std::endl;
	}
	std::cout << std::endl;
}
