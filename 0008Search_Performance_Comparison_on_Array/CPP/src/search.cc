#include "search.hh"

std::string gOutIndexStr("OUT_OF_INDEX");
std::string gSearchFailStr("SEARCH_FAIL");
NODE gOutIndex(gOutIndexStr);
NODE gSearchFail(gSearchFailStr);
static const char letterCollection[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

//Function Definitions
NODE::NODE(void)
{
	(this->name).clear();
	this->number = 0;

	return ;
}

NODE::NODE(std::string &nameArg)
{
	(this->name) = nameArg;
	this->number = 0;

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
	while(len == 0){
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
	(*this).nodeArray.clear();

	return ;
}

ARRAY::~ARRAY(void)
{
	srand((unsigned int)time(NULL));
	(this->nodeArray).clear();

	return ;
}

NODE &ARRAY::operator[](int indexArg)
{
	if (indexArg >= (*this).Size()){
		return gOutIndex;
	}

	return (*this).nodeArray[indexArg];
}

void ARRAY::Print(void)
{
	int index = 0;

	for (std::vector<NODE>::iterator i=(*this).nodeArray.begin() ; i!=(*this).nodeArray.end() ; i++){
		std::cout << "[" << index << "]" << "Name: " << i->name << " Number: " << i->number << std::endl;
		index++;
	}
	std::cout << std::endl;

	return ;
}

int ARRAY::Size(void)
{
	return (*this).nodeArray.size();
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
void ARRAY::Sort(void)
{
	std::sort((*this).nodeArray.begin(), (*this).nodeArray.end(), Comparator());

	return ;
}

ARRAY *ARRAY::AddRandom(void)
{
	NODE temp;
	temp.Random();
	(*this).nodeArray.push_back(temp);
	return NULL;
}

ARRAY *ARRAY::AddRandom(int sizeArg)
{
	if (sizeArg < 1){
		COUT_ERROR << "ERROR: sizeArg < 1." << std::endl;
		return NULL;
	}

	for (int i=0 ; i<sizeArg ; i++){
		(*this).AddRandom();
	}

	return NULL;
}

ARRAY *ARRAY::ChangeRandomElement(std::string &nameArg, int numArg)
{
	int index = 0;

	index = rand()%((*this).Size());
	(*this).nodeArray[index].name = nameArg;
	(*this).nodeArray[index].number = numArg;

	return this;
}

NODE &ARRAY::LinearSearch(std::string &nameArg)
{
	for (std::vector<NODE>::iterator i=(*this).nodeArray.begin() ; i!=(*this).nodeArray.end() ; i++){
		if (strcmp((i->name).c_str(), nameArg.c_str()) == 0){
			return *i;
		}
	}

	return gSearchFail;
}

NODE &ARRAY::JumpSearch(std::string &nameArg)
{
	int index = 0;
	int cmpResult = 0;
	int stepSize = 0;
	std::vector<NODE> &rArray = (*this).nodeArray; //reference to array.

	stepSize = FindSqrt((*this).Size());

	while(1){
		cmpResult = strcmp(rArray[index].name.c_str(), nameArg.c_str());
		if (cmpResult == 0){
			return rArray[index];
		}
		else if (cmpResult > 0){
			//Stop Jump
			break;
		}
		else if (cmpResult < 0){
			if (index + stepSize < (*this).Size()){
				//Jump
				index += stepSize;
				continue;
			}
			else {
				//When you cant' jump. -> Linear Traversal starts.
				for (int i=0 ; i<(*this).Size()-index-1 ; i++){
					index += 1;
					cmpResult = strcmp(rArray[index].name.c_str(), nameArg.c_str());
					if (cmpResult == 0){
						return rArray[index];
					}
					else if (cmpResult > 0){
						return gSearchFail;
					}
					else if (cmpResult < 0){
						continue;
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

	//Linear Traversal toward reverse direction starts.
	for (int i=0 ; i<(stepSize-1) ; i++){
		index -= 1;
		cmpResult = strcmp(rArray[index].name.c_str(), nameArg.c_str());
		if (cmpResult == 0){
			return rArray[index];
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

NODE &ARRAY::BinarySearch(std::string &nameArg)
{
	int beginIndex=0, endIndex=0, midIndex=0;
	int cmpResult = 0;
	std::vector<NODE> &rArray = this->nodeArray;

	endIndex = (*this).Size();

	while (beginIndex <= endIndex){
		midIndex = (beginIndex+endIndex)/2;
		cmpResult = strcmp(rArray[midIndex].name.c_str(), nameArg.c_str());
		if (cmpResult == 0){
			return rArray[midIndex];
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

int FindSqrt(int arg)
{
	unsigned long long int begin=0, end=0, mid=0;

	begin = 0;
	end = arg/2;

	while(begin <= end){
		mid = (begin+end)/2;
		if (mid*mid == arg){
			return mid;
		}
		if (mid*mid > arg){
			end = mid-1;
		}
		if (mid*mid < arg){
			begin = mid+1;
		}
	}

	if (mid*mid > arg){
		mid--;
	}

	return mid;
}
