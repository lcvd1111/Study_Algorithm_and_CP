#include "search.hh"
NODE gSearchFail; 

NODE::NODE(void)
{
	return ;
}

NODE::~NODE(void)
{
	return ;
}

NODE *NODE::Random(void)
{
	return this;
}

LIST::LIST(void)
{
	gSearchFail.name = "SEARCH_FAIL";
	gSearchFail.number = -1;
	return ;
}

LIST::~LIST(void)
{
	return ;
}

NODE &LIST::operator[](int indexArg)
{
	return gSearchFail;
}

void LIST::Print(void)
{
	return ;
}

LIST *LIST::AddRandom(void)
{
	return this;
}

LIST *LIST::ChangeRandomElement(std::string &, int)
{
	return this;
}

LIST *LIST::Sort(void)
{
	return this;
}

NODE &LIST::Search(std::string &)
{
	return gSearchFail;
}
