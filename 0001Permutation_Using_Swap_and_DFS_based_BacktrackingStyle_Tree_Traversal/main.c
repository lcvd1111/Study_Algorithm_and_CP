#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int SwapChar(char *strArg, unsigned int lenArg, unsigned int indexA, unsigned int indexB)
{
    char buf = 0;

    //Exception Handling1
    if (indexA >= lenArg){
        return -1;
    }

    //Exception Handling2
    if (indexB >= lenArg){
        return -2;
    }

    buf = strArg[indexA];
    strArg[indexA] = strArg[indexB];
    strArg[indexB] = buf;

    return 0;
}

int SwapPermutation_DFS_BacktrackStyle(char *strArg, unsigned int lenArg, unsigned int startIndex)
{
    //startIndex can be regarded as a current node's depth value(=level-1 value).
    if (startIndex == lenArg-1){//When the current node is a leaf node.
        printf("%s\n", strArg);
        return 0;
    }
    for (int i=startIndex ; i<lenArg ; i++){
        SwapChar(strArg, lenArg, startIndex, i);
        SwapPermutation_DFS_BacktrackStyle(strArg, lenArg, startIndex+1);
        SwapChar(strArg, lenArg, startIndex, i);
    }

    return 0;
}

int main(int argc, char **argv)
{
    char inputStr[64] = {0,};
    unsigned int inputStrLen = 0;

    if (argc < 2){
        printf("Plz input a word as an option.\n");
        return -1;
    }

    strncpy(inputStr, argv[1], 64);
    inputStrLen = strlen(argv[1]);

    SwapPermutation_DFS_BacktrackStyle(argv[1], inputStrLen, 0);

    return 0;
}
