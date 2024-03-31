#include "test.h"

int UnitTest_Array(void)
{
	ARRAY testArray;
	ARRAY_METHOD_CONSTRUCTOR(&testArray, 100);

	testArray.Fill_Random(&testArray);
	//testArray.Print(&testArray);

	ARRAY_METHOD_DESTRUCTOR(&testArray);
	return 0;
}

void test_DFS_Print(BST *inputBST, BST_NODE *inputNode)
{
	BST_NODE *currentNode = inputNode;
	BST_NODE *friend_Of_CurrentNode = NULL;
	BST_NODE *tempNode = NULL;

	if (currentNode->leftChild != NULL){
		test_DFS_Print(inputBST, currentNode->leftChild);
	}

	printf("Key:%s, Data:%d\n", currentNode->key, currentNode->data);
	if (currentNode->nextFriend != NULL){
		friend_Of_CurrentNode = currentNode->nextFriend;
		while(friend_Of_CurrentNode->nextFriend != NULL){
			printf("Key:%s, Data:%d\n", friend_Of_CurrentNode->key, friend_Of_CurrentNode->data);
			friend_Of_CurrentNode = friend_Of_CurrentNode->nextFriend;
		}
		printf("Key:%s, Data:%d\n", friend_Of_CurrentNode->key, friend_Of_CurrentNode->data);
	}

	if (currentNode->rightChild != NULL){
		test_DFS_Print(inputBST, currentNode->rightChild);
	}

	return ;
}

int UnitTest_BST(void)
{
	BST testBST;
	BST_METHOD_CONSTRUCTOR(&testBST);

	if (testBST.size != 0){
		UNIT_TEST_FAIL;
		return -1;
	}
	testBST.Insert(&testBST, "d", 1);

	if (testBST.size != 1){
		UNIT_TEST_FAIL;
		return -2;
	}

	testBST.Insert(&testBST, "a", 2);

	if (testBST.size != 2){
		UNIT_TEST_FAIL;
		return -3;
	}

	testBST.Insert(&testBST, "c", 3);

	if (testBST.size != 3){
		UNIT_TEST_FAIL;
		return -4;
	}

	testBST.Insert(&testBST, "d", 3);
	
	if (testBST.size != 4){
		UNIT_TEST_FAIL;
		return -5;
	}
	
	testBST.Insert(&testBST, "b", 13);

	//printf("\n");
	//test_DFS_Print(&testBST, testBST.root);

	BST_METHOD_DESTRUCTOR(&testBST);
	return 0;
}

int CompareFunc(const void *prev, const void *rear)
{
	return (strcmp(((ARRAY_NODE *)prev)->name,
				((ARRAY_NODE *)rear)->name));
}

int UnitTest_Sort(void)
{
	ARRAY testArray;
	ARRAY_METHOD_CONSTRUCTOR(&testArray, 400);
	ARRAY_NODE rawArray[400];

	testArray.Fill_Random(&testArray);
	testArray.Copy_to_Raw_Array(&testArray, rawArray);
	//testArray.Print(&testArray);
	testArray.Sort(&testArray);
	qsort(rawArray, 400, sizeof(ARRAY_NODE), &CompareFunc);
	//testArray.Print(&testArray);

	for (int i=0 ; i<400 ; i++){
		if (strcmp((testArray.nodeArray)[i].name, rawArray[i].name)){
			return -1-i;
		}
	}

	ARRAY_METHOD_DESTRUCTOR(&testArray);
	return 0;
}

int UnitTest(void)
{
	int errCode = 0;
	printf(COLOR_BLACK "Unit Test for Array: ");
	if (errCode = UnitTest_Array()){
		printf(COLOR_RED "FAIL\n");
		printf(COLOR_RED "Error Code: %d\n" COLOR_BLACK, errCode);
		return -1;
	}
	printf(COLOR_GREEN "SUCCESS\n");

	printf(COLOR_BLACK "Unit Test for BST: ");
	if (errCode = UnitTest_BST()){
		printf(COLOR_RED "FAIL\n");
		printf(COLOR_RED "Error Code: %d\n" COLOR_BLACK, errCode);
		return -2;
	}
	printf(COLOR_GREEN "SUCCESS\n");

	printf(COLOR_BLACK "Unit Test for Tree Sorting to array: ");
	if (errCode = UnitTest_Sort()){
		printf(COLOR_RED "FAIL\n");
		printf(COLOR_RED "Error Code: %d\n" COLOR_BLACK, errCode);
		return -3;
	}
	printf(COLOR_GREEN "SUCCESS\n");

	return 0;
}
