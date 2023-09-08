#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRING_LEN 64

int SwapStr(char *inputStr, char *outputStr, unsigned int lenArg, unsigned int indexA, unsigned int indexB)
{
	char charBuf = 0;

    if (outputStr == NULL){
        printf("ERROR: output storage is NULL.\n");
        return -1;
    }

    strncpy(outputStr, inputStr, lenArg);

	charBuf = outputStr[indexA];
	outputStr[indexA] = outputStr[indexB];
	outputStr[indexB] = charBuf;

	//printf("After the swapping in the SwapStr func: %s\n", outputStr);

    return 0;
}

int Permutation(char *stringArg, unsigned int lenArg, unsigned int indexA)
{
	char stringBuffer[STRING_LEN] = {0,};

	if (indexA == lenArg){ //When the current node is a leaf node
		printf("%s\n", stringArg);
		return 0;
	}

	for (int i=indexA ; i<lenArg ; i++){
		SwapStr(stringArg, stringBuffer, lenArg, indexA, i);
		Permutation(stringBuffer, lenArg, indexA+1);
	}

}

int main(int argc, char **argv)
{
    char inputString[STRING_LEN] = {0,};
    int inputStringLen = 0;

    if (argc < 2) {
        printf("Please input an option\n");
        return -1;
    }

    strncpy(inputString, argv[1], STRING_LEN);
    inputStringLen = strlen(inputString);

	printf("[%s, %d]\n", inputString, inputStringLen);

    Permutation(inputString, inputStringLen, 0);

    return 0;
}
