#include "search.h"

//Filescope variable Defintions
static char charSet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

//Function Definitions
NODE *RandomFill(NODE *arrayArg, int sizeArg)
{
	int index = 0;
	char stringBuf[STRING_LEN] = {0,};
	int wordLength = 0;

	//Exceptoin Handling
	if (arrayArg == NULL){
		PRINTF_ERROR("ERROR: arrayArg is NULL.\n");
		return NULL;
	}

	//Exceptoin Handling
	if (sizeArg < 1){
		PRINTF_ERROR("ERROR: sizeArg < 1.\n");
		return NULL;
	}

	srand((unsigned int)(time(NULL)));

	for (int i=0 ; i<sizeArg ; i++){
		memset(stringBuf, 0, STRING_LEN);
		wordLength = rand()%(STRING_LEN-2);

		if (wordLength < 2){
			wordLength += 2;
		}

		for (int j=0 ; j<wordLength ; j++){
			stringBuf[j] = charSet[rand()%62];
		}
		stringBuf[wordLength] = '\0';

		strncpy(arrayArg[i].name, stringBuf, STRING_LEN);
		arrayArg[i].number = rand()%100000;
	}

	return NULL;
}

int LinearSearch(NODE *arrayArg, int sizeArg, char *nameArg)
{
	//Exception Handling
	if (arrayArg == NULL){
		PRINTF_ERROR("ERROR: arrayArg is NULL.\n");
		return -1;
	}
	
	//Exception Handling
	if (nameArg == NULL){
		PRINTF_ERROR("ERROR: nameArg is NULL.\n");
		return -2;
	}

	for (int i=0; i<sizeArg ; i++){
		if (strcmp((arrayArg+i)->name, nameArg)){
			continue;
		}
		return i;
	}

	return -1;
}
