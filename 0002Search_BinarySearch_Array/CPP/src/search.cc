#include "search.hh"

static const char letterCollection[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
NODE g_SearchFail;

NODE::NODE(void)
{
	(this->name).clear();
	this->number = 0;
	return ;
}

NODE::~NODE(void)
{
	(this->name).clear();
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

	return this;
}

ARRAY::ARRAY(void)
{
	srand((unsigned int)time(NULL));

	(this->nodeArray).clear();

	return ;
}

ARRAY::~ARRAY(void)
{
	(this->nodeArray).clear();

	return ;
}

int ARRAY::Size(void)
{
	int ret = (this->nodeArray).size();

	return ret;
}

NODE &ARRAY::operator[](int indexArg)
{
	//Exception Handling
	if (indexArg >= (*this).Size()){
		COUT_ERROR << "ERROR: indexArg >= size" COLOR_BLACK << std::endl;
		throw std::out_of_range("");
	}

	NODE &ret = (this->nodeArray)[indexArg];

	return ret;
}

ARRAY *ARRAY::AddRandom(void)
{
	NODE newNode;
	newNode.Random();
	(this->nodeArray).push_back(newNode);

	return this;
}

ARRAY *ARRAY::AddRandom(int sizeArg)
{
	for (int i=0 ; i<sizeArg ; i++){
		(*this).AddRandom();
	}

	return this;
}

NODE &ARRAY::ChangeRandomElement(std::string &nameArg, int numArg)
{
	int currentSize = (*this).Size();
	int index = rand()%currentSize;
	NODE &ret = (*this)[index];

	ret.name = nameArg;
	ret.number = numArg;

	return ret;
}

ARRAY *ARRAY::Print(void)
{

	for (int i=0; i<(*this).Size() ; i++){
		std::cout << "[" << i << "] " << "Name: " << (*this)[i].name << ", Number: " << (*this)[i].number << std::endl;
	}

	return this;
}

class CUSTOM_COMPARE {
public:
	bool operator()(NODE &, NODE &);
};

bool CUSTOM_COMPARE::operator()(NODE &front, NODE &rear)
{
	const char *a = front.name.c_str();
	const char *b = rear.name.c_str();
	if (strcmp(a, b)<0){
		return true;
	}
	return false;
}

ARRAY *ARRAY::Sort(void)
{
	std::sort((this->nodeArray).begin(), (this->nodeArray).end(), CUSTOM_COMPARE());

	return this;
}

NODE &ARRAY::BinarySearch(std::string &nameArg)
{
	int begin=0, end=0, mid=0;
	const char *midStr=NULL, *tempStr=nameArg.c_str();

	end = (*this).Size()-1;

	while(begin<=end){
		mid = (begin+end)/2;
		if ((*this)[mid].name == nameArg){
			return (*this)[mid];
		}
		else {
			midStr = (*this)[mid].name.c_str();
			if (strcmp(midStr, tempStr)>0){
				end = mid - 1;
				continue;
			}
			else {
				begin = mid+1;
				continue;
			}
		}
	}

	g_SearchFail.name = "SEARCH_FAIL";
	g_SearchFail.number = -1;
	NODE &ret = g_SearchFail;
	return ret;
}
