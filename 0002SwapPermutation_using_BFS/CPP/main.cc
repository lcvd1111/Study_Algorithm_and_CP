#include <iostream>
#include <queue>
#include <cstring>

#define STRING_LEN 64

typedef class _QUEUE_NODE QUEUE_NODE;
class _QUEUE_NODE {
public:
	char data[STRING_LEN];
	int level;
};

int SwapChar(char *outputStore, char *strArg, int indexA, int indexB)
{
	char buffer = 0;

	//Exception Handling
	if (outputStore == NULL){
		std::cout << "ERROR: outputStore is NULL." << std::endl;
		return -1;
	}

	strncpy(outputStore, strArg, STRING_LEN);

	buffer = outputStore[indexA];
	outputStore[indexA] = outputStore[indexB];
	outputStore[indexB] = buffer;

	return 0;
}

int Permutation_Using_LevelOrder_Traversal(char *strArg, unsigned int lenArg)
{
	char currentStr[STRING_LEN] = {0,};
	char childNodeStr[STRING_LEN] = {0,};
	int currentLevel = 0;
	QUEUE_NODE tempNode;
	memset(&tempNode, 0X00, sizeof(QUEUE_NODE));
	std::queue <QUEUE_NODE>bfsQueue;

	strncpy(currentStr, strArg, STRING_LEN);

	while(1){
		if (currentLevel == lenArg){
			std::cout << currentStr << std::endl;

			if (bfsQueue.empty())
				break;

			strncpy(currentStr, bfsQueue.front().data, STRING_LEN);
			currentLevel = bfsQueue.front().level;
			bfsQueue.pop();
			continue;
		}

		for (int j=currentLevel ; j<lenArg ; j++){
			SwapChar(tempNode.data, currentStr, currentLevel, j);
			tempNode.level = currentLevel + 1;
			bfsQueue.push(tempNode);
		}

		if (bfsQueue.empty())
			break;

		strncpy(currentStr, bfsQueue.front().data, STRING_LEN);
		currentLevel = bfsQueue.front().level;
		bfsQueue.pop();
		continue;
	}

	return 0;
}

int main(int argc, char **argv)
{
	char inputStr[STRING_LEN] = {0,};
	unsigned int inputStrLen = 0;

	if (argc < 2){
		std::cout << "Input a string as an option." << std::endl;
		return -1;
	}

	strncpy(inputStr, argv[1], STRING_LEN);
	inputStrLen = strlen(inputStr);

	if(Permutation_Using_LevelOrder_Traversal(inputStr, inputStrLen)){
		std::cout << "FAIL." << std::endl;
		return -1;
	}

	return 0;
}
