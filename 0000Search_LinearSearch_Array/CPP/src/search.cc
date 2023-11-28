#include "search.hh"

#define NAME_LEN 16 

static const char *letterCollection = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

//Function Definitions.
NODE::NODE(void)
{
	(this->name).clear();
	(this->number) = 0;

	return ;
}

NODE::~NODE(void)
{
	(this->name).clear();
	(this->number) = 0;

	return ;
}

NODE *NODE::Random(void)
{
	int length = 0;

	(this->name).clear();

	length = rand()%(NAME_LEN);
	if (length <2 ){
		length += 2;
	}
	for (int i=0; i<length ; i++){
		(this->name).push_back(letterCollection[rand()%62]);
	}

	this->number = rand()%100000;

	return this;
}

VECTOR::VECTOR(void)
{
	(this->array).clear();
	srand((unsigned int)time(NULL));

	return ;
}

VECTOR::~VECTOR(void)
{
	(this->array).clear();

	return ;
}

int VECTOR::Add(void)//Add random element
{
	NODE temp;
	temp.Random();
	(*this).array.push_back(temp);

	return 0;
}

int VECTOR::Add(std::string &nameArg, int numArg)//Change one of element into inputted data.
{
	int currentSize = (this->array).size();
	int index = 0;

	if (currentSize == 0){
		return -1;
	}

	index = rand()%(currentSize);

	(*this)[index].name = nameArg;
	(*this)[index].number = numArg;

	return 0;
}

NODE &VECTOR::operator[](int indexArg)
{
	NODE &ret = (this->array)[indexArg];
	return ret;
}

NODE VECTOR::Search(std::string &nameArg)
{
	NODE err;

	for (std::vector<NODE>::iterator i=(this->array).begin() ; i!=(this->array).end() ; i++){
		if (i->name == nameArg){
			return *i;
		}
	}

	return err;
}


void VECTOR::Print(void)
{
	for (std::vector<NODE>::iterator i=(*this).array.begin() ; i!=(*this).array.end() ; i++){
		std::cout << "Name: " << i->name << " Number: " << i->number << std::endl;
	}

	return ;
}
