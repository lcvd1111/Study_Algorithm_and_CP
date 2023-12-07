#include "search.hh"

std::string strOutIndex("OUT_OF_INDEX");
std::string strSearchFail("SEARCH_FAIL");
NODE gOutIndex(strOutIndex);
NODE gSearchFail(strSearchFail);
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
	
	srand((unsigned int)time(NULL));

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

int FindSqrt(int arg)
{
	unsigned long long int begin=0, end=0, mid=0;
	unsigned long long int longArg = (unsigned long long int)arg;

	end = arg/2;
	while(begin <= end){
		mid = (begin+end)/2;
		if (mid*mid == arg){
			return mid;
		}
		else if (mid*mid > arg){
			end = mid - 1;
			continue;
		}
		else if (mid*mid < arg){
			begin = mid + 1;
			continue;
		}
	}
	if (mid*mid > arg){
		mid -- ;
	}

	return mid;
}

NODE &ARRAY::Search(std::string &nameArg)
{
	int index = 0;
	std::vector<NODE>::iterator temp;
	int stepSize = 0;
	int cmpResult = 0;

	//Exception Handling
	if ((*this).Size() == 0){
		return gSearchFail;
	}

	index = 0;
	temp = (*this).nodeVector.begin();
	stepSize = FindSqrt((*this).Size());

	//Jumping
	while(1){
		cmpResult = strcmp((temp->name).c_str(), nameArg.c_str());
		if (cmpResult == 0){
			return *temp;
		}
		else if (cmpResult > 0){
			if (index == 0){
				return gSearchFail;
			}
			break;//Jump Ends.
		}
		else if (cmpResult < 0){
			if (index+stepSize >= (*this).Size()){
				//When you can't do jump anymore.
				for (int i=0 ; i<(*this).Size()-index-1 ; i++){
					temp = temp + 1;
					cmpResult = strcmp((temp->name).c_str(), nameArg.c_str());
					if (cmpResult == 0){
						return *temp;
					}
					else if (cmpResult < 0){
						temp = temp+1;
						continue;
					}
					else if (cmpResult > 0){
						return gSearchFail;
					}
				}
				return gSearchFail;
			}
			else {
				index = index + stepSize;
				temp = temp + stepSize;
				continue;
			}
		}
	}

	//Linear Search toward reverse direction
	for (int i=0 ; i<stepSize-1 ; i++){
		temp = temp-1;
		cmpResult = strcmp((*temp).name.c_str(), nameArg.c_str());
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

void ARRAY::Print(void)
{
	for (std::vector<NODE>::iterator i=(*this).nodeVector.begin() ; i!=(*this).nodeVector.end() ; i++){
		std::cout << COLOR_BLACK << "[" << (int)(i-(*this).nodeVector.begin()) << "] <Name>: " << i->name << " <Number>: " << i->number << COLOR_BLACK << std::endl;
	}
	std::cout << std::endl;
}
