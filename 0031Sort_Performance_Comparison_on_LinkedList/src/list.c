#include "list.h"

static char letterCollection[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
static LIST_NODE_METHOD gListNodeMethod = {.Random = &LIST_NODE_METHOD_Random };
static LIST_METHOD_SORT gListMethodSort = { .Bubble = &LIST_METHOD_SORT_Bubble,
								.Insertion = &LIST_METHOD_SORT_Insertion,
								.Selection = &LIST_METHOD_SORT_Selection,
								.Tree = &LIST_METHOD_SORT_Tree,
								.Heap = &LIST_METHOD_SORT_Heap,
								.Merge = &LIST_METHOD_SORT_Merge,
								.Quick = &LIST_METHOD_SORT_Quick,
								.Shell = &LIST_METHOD_SORT_Shell,};
static LIST_METHOD gListMethod = {.Print = &LIST_METHOD_Print,
							.Size = &LIST_METHOD_Size,
							.Add_One_Random = &LIST_METHOD_Add_One_Random,
							.Add_Random = &LIST_METHOD_Add_Random,
							.Copy_to_Array = &LIST_METHOD_Copy_to_Array,
							.Copy_to_List = &LIST_METHOD_Copy_to_List,
							.Sort = &gListMethodSort};
static const int stepSizeList[] = {1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 
									4095, 8191, 16383, 32767, 65535, 131071, 262143,
									524287, 1048575, 2097151, 4194303, 8388607,
									16777215, 33554431, 67108863, 134217727, 268435455};



//Function Definitions
void LIST_NODE_METHOD_CONSTRUCTOR(LIST_NODE *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	memset(this->name, 0, NAME_LEN);
	this->number = 0;
	this->prev = NULL;
	this->next = NULL;

	//Binding the method Functions
	this->Method = &gListNodeMethod;

	return ;
}

void LIST_NODE_METHOD_DESTRUCTOR(LIST_NODE *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	return ;
}

void LIST_NODE_METHOD_Random(LIST_NODE *this)
{
	int len = 0;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	while(len == 0){
		len = rand()%8;
	}

	for (int i=0 ; i<len ; i++){
		(this->name)[i] = letterCollection[rand()%62];
	}
	(this->name)[len] = 0;

	this->number = rand()%10000;

	return ;
}

void LIST_METHOD_CONSTRUCTOR(LIST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	this->begin = this->end = NULL;
	this->size = 0;
	this->currentNode = NULL;

	//Binding the method functions
	this->Method = &gListMethod;

	srand((unsigned int)time(NULL));

	return ;
}

void LIST_METHOD_DESTRUCTOR(LIST *this)
{
	LIST_NODE *temp = NULL;
	LIST_NODE *temp_next = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//When the list is empty currently.
	if (this->size == 0){
		return ;
	}

	//When the list is not empty currently.
	temp = this->begin;

	while(temp != NULL){
		temp_next = temp->next;
		LIST_NODE_METHOD_DESTRUCTOR(temp);
		free(temp);
		this->size -= 1;
		temp = temp_next;
	}

	this->begin = this->end = NULL;

	return ;
}

LIST *LIST_METHOD_Print(LIST *this)
{
	LIST_NODE *temp = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	temp = this->begin;

	printf("\n");
	for (int i=0 ; i<this->size ; i++){
		printf("[%d] Name: %s Number: %d\n"
				, i, temp->name, temp->number);
		temp = temp->next;
	}
	printf("\n");

	return this;
}

int LIST_METHOD_Size(LIST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return -1;
	}

	return (this->size);
}

LIST *LIST_METHOD_Add_One_Random(LIST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the list is empty currently.
	if (this->size == 0){
		assert(this->begin == NULL && this->end == NULL);
		this->begin = (LIST_NODE *)malloc(sizeof(LIST_NODE));
		this->end = this->begin;
		this->size = 1;
		LIST_NODE_METHOD_CONSTRUCTOR(this->begin);
		((this->begin)->Method->Random)(this->begin);
		return this;
	}

	//When the list is not empty currently.
	assert(this->end->next == NULL);
	this->end->next = (LIST_NODE *)malloc(sizeof(LIST_NODE));
	this->size += 1;
	LIST_NODE_METHOD_CONSTRUCTOR(this->end->next);
	this->end->next->prev = this->end;
	this->end = this->end->next;
	(this->end->Method->Random)(this->end);

	return this;
}

LIST *LIST_METHOD_Add_Random(LIST *this, int sizeArg)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//Exception Handling
	if (sizeArg < 0){
		PRINTF_ERROR("ERROR: sizeArg < 0.\n");
		return NULL;
	}
	
	for (int i=0 ; i<sizeArg ; i++){
		((*this).Method->Add_One_Random)(this);
	}

	return this;
}

LIST *LIST_METHOD_Copy_to_Array(LIST *this, LIST_NODE *dest)
{
	LIST_NODE *temp = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the list is empty
	if (this->size == 0){
		return this;
	}

	temp = this->begin;

	for (int i=0 ; i<this->size ; i++){
		memcpy(dest+i, temp, sizeof(LIST_NODE));
		temp = temp->next;
	}

	return this;
}

LIST *LIST_METHOD_Copy_to_List(LIST *this, LIST *dest)
{
	LIST_NODE *temp = NULL;
	LIST_NODE *temp_dest = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	if (dest == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
	}

	//When the list is empty
	if (this->size == 0){
		return this;
	}

	LIST_METHOD_DESTRUCTOR(dest);
	assert(dest->begin == NULL);
	assert(dest->end == NULL);
	assert(dest->size == 0);

	temp = this->begin;
	dest->begin = (LIST_NODE *)malloc(sizeof(LIST_NODE));
	LIST_NODE_METHOD_CONSTRUCTOR(dest->begin);
	dest->size ++;
	temp_dest = dest->begin;
	for (int i=0 ; i<this->size ; i++){
		memcpy(temp_dest->name, temp->name, NAME_LEN);
		temp_dest->number = temp->number;
		temp = temp->next;
		temp_dest->next = (LIST_NODE *)malloc(sizeof(LIST_NODE));
		LIST_NODE_METHOD_CONSTRUCTOR(temp_dest->next);
		temp_dest->next->prev = temp_dest;
		dest->size ++;
		temp_dest = temp_dest->next;
	}

	assert(dest->size == this->size + 1);
	temp_dest = temp_dest->prev;
	LIST_NODE_METHOD_DESTRUCTOR(temp_dest->next);
	free(temp_dest->next);
	temp_dest->next = NULL;
	dest->size -= 1;

	return this;
}

LIST *LIST_METHOD_SORT_Bubble(LIST *this)
{
	LIST_NODE *left=NULL, *right=NULL;
	char buffer_name[NAME_LEN] = {0,};
	int buffer_number = 0;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the list size is smaller than 2.
	if (this->size < 2){
		return NULL;
	}

	for (int numberOfCompare = this->size-1
		; numberOfCompare>0 
		; numberOfCompare--)
	{
		left = this->begin;
		for (int i=0 ; i<numberOfCompare ; i++){
			right = left->next;
			if (strcmp(left->name, right->name) > 0){
				memcpy(buffer_name, left->name, NAME_LEN);
				buffer_number = left->number;

				memcpy(left->name, right->name, NAME_LEN);
				left->number = right->number;

				memcpy(right->name, buffer_name, NAME_LEN);
				right->number = buffer_number;
			}
			left = left->next;
		}
	}

	return this;
}

LIST *LIST_METHOD_SORT_Insertion(LIST *this)
{
	LIST_NODE *sorted_Last_Node = NULL,
		 *unsorted_First_Node = NULL,
		 *currentNode = NULL;
	LIST_NODE operand_For_Sorting;
	int cmpResult = 0;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the size is smaller than 2
	if (this->size < 2){
		return NULL;
	}

	sorted_Last_Node = this->begin;
	for (int i=0 ; i<(this->size - 1) ; i++){
		unsorted_First_Node = sorted_Last_Node->next;
		memcpy(operand_For_Sorting.name, unsorted_First_Node->name, NAME_LEN);
		operand_For_Sorting.number = unsorted_First_Node->number;

		currentNode = sorted_Last_Node;

		while(currentNode != NULL){
			cmpResult = strcmp(currentNode->name, operand_For_Sorting.name);
			if (cmpResult > 0){
				memcpy(currentNode->next->name, currentNode->name, NAME_LEN);
				currentNode->next->number = currentNode->number;
				currentNode = currentNode->prev;
				continue;
			}
			else {
				memcpy(currentNode->next->name, operand_For_Sorting.name, NAME_LEN);
				currentNode->next->number = operand_For_Sorting.number;
				break;
			}
		}

		if (currentNode == NULL){
			memcpy(this->begin->name, operand_For_Sorting.name, NAME_LEN);
			this->begin->number = operand_For_Sorting.number;
		}

		sorted_Last_Node = sorted_Last_Node->next;
	}

	return this;
}

LIST *LIST_METHOD_SORT_Selection(LIST *this)
{
	//Selection Sort
	LIST_NODE *dst_Node = NULL,
		 *current_Node = NULL,
		 *min_Node = NULL;
	int cmpResult = 0;
	
	char charBuf[NAME_LEN] = {0,};
	int intBuf = 0;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When size of the list is smaller than 2
	if (this->size < 2){
		return NULL;
	}

	dst_Node = this->begin;
	while(dst_Node != NULL){
		min_Node = dst_Node;
		current_Node = dst_Node->next;
		while(current_Node != NULL){
			//Finding the minimum node
			cmpResult = strcmp(min_Node->name, current_Node->name);
			if (cmpResult > 0){
				min_Node = current_Node;
			}
			current_Node = current_Node->next;
		}

		//Swapping the minimum node and destination node
		memcpy(charBuf, min_Node->name, NAME_LEN);
		intBuf = min_Node->number;
		memcpy(min_Node->name, dst_Node->name, NAME_LEN);
		min_Node->number = dst_Node->number;
		memcpy(dst_Node->name, charBuf, NAME_LEN);
		dst_Node->number = intBuf;

		dst_Node = dst_Node->next;
	}

	return this;
}

int Recursive_DFS_Inorder_Traversal
(LIST *this, BST *inputBST, BST_NODE *inputBSTnode)
{
	BST_NODE *current_Node = inputBSTnode;
	BST_NODE *tempNode = NULL;

	//Moving to left child node.
	if (current_Node->leftChild != NULL){
		Recursive_DFS_Inorder_Traversal(this, inputBST, current_Node->leftChild);
	}

	//Visit Checking.
	tempNode = current_Node;
	while(tempNode->nextFriend != NULL){
		memcpy(this->currentNode->name, tempNode->key, NAME_LEN);
		this->currentNode->number = tempNode->data;
		this->currentNode = this->currentNode->next;
		tempNode = tempNode->nextFriend;
	}
	memcpy(this->currentNode->name, tempNode->key, NAME_LEN);
	this->currentNode->number = tempNode->data;
	this->currentNode = this->currentNode->next;

	//Moving to right child node.
	if (current_Node->rightChild != NULL){
		Recursive_DFS_Inorder_Traversal(this, inputBST, current_Node->rightChild);
	}
	
	return 0;
}

LIST *LIST_METHOD_SORT_Tree(LIST *this)
{
	LIST_NODE *tempNode = NULL;
	BST sortBST;
	BST_METHOD_CONSTRUCTOR(&sortBST);

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	tempNode = this->begin;
	for (int i=0 ; i<this->size ; i++){
		sortBST.Insert(&sortBST, tempNode->name, tempNode->number);
		tempNode = tempNode->next;
	}

	assert(tempNode == NULL);

	this->currentNode = this->begin;
	Recursive_DFS_Inorder_Traversal(this, &sortBST, sortBST.root);
	this->currentNode = NULL;

	BST_METHOD_DESTRUCTOR(&sortBST);

	return this;
}

LIST *LIST_METHOD_SORT_Heap(LIST *this)
{
	PQ sortingPQ;
	int level = 0;
	int size = 0;
	LIST_NODE *temp = NULL;
	PQ_NODE temp_PQ;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	level = 0;
	size = 1;
	while (size < this->size){
		level++;
		size *= 2;
	}

	PQ_CONSTRUCTOR(&sortingPQ, level);

	temp = this->begin;
	for (int i=0 ; i<this->size ; i++){
		memcpy(temp_PQ.name, temp->name, NAME_LEN);
		temp_PQ.number = temp->number;
		sortingPQ.Enqueue(&sortingPQ, &temp_PQ);
		temp = temp->next;
	}

	temp = this->begin;
	for (int i=0 ; i<this->size ; i++){
		sortingPQ.Dequeue(&sortingPQ, &temp_PQ);
		memcpy(temp->name, temp_PQ.name, NAME_LEN);
		temp->number = temp_PQ.number;
		temp = temp->next;
	}

	assert(temp == NULL);

	PQ_DESTRUCTOR(&sortingPQ);

	return this;
}

int MergeFunc(LIST *this, LIST_NODE *beginNode, int elementNum)
{
	LIST_NODE *leftCurrentNode = beginNode;
	int leftElementNum = (elementNum+1)/2;
	int leftCurrentIndex = 0;

	LIST_NODE *rightCurrentNode = beginNode; for (int i=0 ; i<leftElementNum ; i++){rightCurrentNode = rightCurrentNode->next;}
	int rightElementNum = elementNum - leftElementNum;
	int rightCurrentIndex = 0;

	int cmpResult = 0;
	LIST_NODE *temp = NULL;

	LIST_NODE *resultArray = (LIST_NODE *)malloc(sizeof(LIST_NODE) * elementNum);
	for (int i=0 ; i<elementNum ; i++){
		LIST_NODE_METHOD_CONSTRUCTOR(resultArray + i);
	}
	int resultCurrentIndex = 0;

	while(1){
		cmpResult = strcmp(leftCurrentNode->name, rightCurrentNode->name);
		if (cmpResult < 0){
			memcpy((resultArray[resultCurrentIndex]).name, leftCurrentNode->name, NAME_LEN);
			(resultArray[resultCurrentIndex]).number = leftCurrentNode->number;
			leftCurrentIndex ++;
			leftCurrentNode = leftCurrentNode->next;

			if (leftCurrentIndex == leftElementNum){
				for (int i=0 ; i<rightElementNum-rightCurrentIndex ; i++){
					resultCurrentIndex++;
					memcpy(resultArray[resultCurrentIndex].name, rightCurrentNode->name, NAME_LEN);
					resultArray[resultCurrentIndex].number = rightCurrentNode->number;
					rightCurrentNode = rightCurrentNode->next;
				}
				break;
			}
		}
		else {
			memcpy(resultArray[resultCurrentIndex].name, rightCurrentNode->name, NAME_LEN);
			(resultArray[resultCurrentIndex]).number = rightCurrentNode->number;
			rightCurrentIndex ++;
			rightCurrentNode = rightCurrentNode->next;
			
			if (rightCurrentIndex == rightElementNum){
				for (int i=0 ; i<leftElementNum-leftCurrentIndex ; i++){
					resultCurrentIndex++;
					memcpy(resultArray[resultCurrentIndex].name, leftCurrentNode->name, NAME_LEN);
					resultArray[resultCurrentIndex].number = leftCurrentNode->number;
					leftCurrentNode = leftCurrentNode->next;
				}
				break;
			}

		}
		resultCurrentIndex++;
	}

	assert (resultCurrentIndex == elementNum-1);

	temp = beginNode;
	for (int i=0 ; i<elementNum ; i++){
		memcpy(temp->name, resultArray[i].name, NAME_LEN);
		temp->number = resultArray[i].number;
		temp = temp->next;
	}

	return 0;
}

int DFS_Recursive_Merge(LIST *this, LIST_NODE *beginNode, int elementNum)
{
	int leftChildElementNum = 0;
	int rightChildElementNum = 0;
	LIST_NODE *rightChildBeginNode = NULL;

	//Exception Handling
	if (beginNode == NULL){
		PRINTF_ERROR("ERROR: beginNode is NULL.\n");
		return -1;
	}

	//Base Case
	if (elementNum == 1){
		return 0;
	}

	leftChildElementNum = (elementNum+1)/2;

	DFS_Recursive_Merge(this, beginNode, leftChildElementNum);//Going to left child Node.

	//Backtracking to parent node is done.

	rightChildBeginNode = beginNode;
	for (int i=0 ; i<leftChildElementNum ; i++){
		rightChildBeginNode = rightChildBeginNode->next;
	}
	rightChildElementNum = elementNum - leftChildElementNum;

	DFS_Recursive_Merge(this, rightChildBeginNode, rightChildElementNum);//Going to right child Node.

	//Backtracking to parent node is done.

	MergeFunc(this, beginNode, elementNum);
	return 0;
}

LIST *LIST_METHOD_SORT_Merge(LIST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	DFS_Recursive_Merge(this, this->begin, this->size);
	return this;
}

int Partition(LIST *this, LIST_NODE *beginNode, int elementSize, int *pivotIndex_return, LIST_NODE **pivotNode_return)
{
	int leftIndex=0, rightIndex=elementSize-1;
	LIST_NODE *leftNode=beginNode, *rightNode=beginNode;
	for (int i=0 ; i<rightIndex ; i++){
		rightNode = rightNode->next;
	}
	LIST_NODE *pivotNode = rightNode;

	//Variables for beins used as buffer for swapping
	LIST_NODE bufferNode;

	while(1){
		while (strcmp(leftNode->name, pivotNode->name)<0){
			leftNode = leftNode->next;
			leftIndex++;
		}

		while (strcmp(rightNode->name, pivotNode->name)>=0){
			rightNode = rightNode->prev;
			rightIndex--;

			if (rightIndex < 0){
				break;
			}
		}

		assert(leftIndex != rightIndex);

		if (leftIndex < rightIndex){
			memcpy(bufferNode.name, leftNode->name, NAME_LEN);
			bufferNode.number = leftNode->number;

			memcpy(leftNode->name, rightNode->name, NAME_LEN);
			leftNode->number = rightNode->number;

			memcpy(rightNode->name, bufferNode.name, NAME_LEN);
			rightNode->number = bufferNode.number;
			continue;
		}
		else if (leftIndex > rightIndex){
			memcpy(bufferNode.name, leftNode->name, NAME_LEN);
			bufferNode.number = leftNode->number;

			memcpy(leftNode->name, pivotNode->name, NAME_LEN);
			leftNode->number = pivotNode->number;

			memcpy(pivotNode->name, bufferNode.name, NAME_LEN);
			pivotNode->number = bufferNode.number;
			break;
		}
	}

	*pivotIndex_return = leftIndex;
	*pivotNode_return = leftNode;

	return 0;
}

int DFS_Recursive_Quick(LIST *this, LIST_NODE *beginNode, int elementSize)
{
	int pivotIndex = 0;
	LIST_NODE *pivotNode = NULL;

	int leftChild_elementSize=0, rightChild_elementSize=0;
	LIST_NODE *leftChild_beginNode=NULL, *rightChild_beginNode=NULL;

	//Base Case
	if ((elementSize <= 1) || (beginNode == NULL)){
		return 0;
	}

	if (Partition(this, beginNode, elementSize, &pivotIndex, &pivotNode)){
		PRINTF_ERROR("ERROR: 'Partition( )' function failed.\n");
		return -1;
	}

	leftChild_elementSize = pivotIndex;
	leftChild_beginNode = beginNode;
	DFS_Recursive_Quick(this, leftChild_beginNode, leftChild_elementSize);

	rightChild_elementSize = elementSize - pivotIndex - 1;
	rightChild_beginNode = pivotNode->next;
	DFS_Recursive_Quick(this, rightChild_beginNode, rightChild_elementSize);

	return 0;
}


LIST *LIST_METHOD_SORT_Quick(LIST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	DFS_Recursive_Quick(this, this->begin, this->size);

	return this;
}

LIST *LIST_METHOD_SORT_Shell(LIST *this)
{
	LIST_NODE *beginNode = NULL,
			  *sortedLastNode = NULL,
			  *unsortedFirstNode = NULL,
			  *currentNode = NULL,
			  *currentNextNode = NULL;
	LIST_NODE buffer;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	int stepSizeIndex = 0, stepSize = 0;

	for ( ; stepSizeList[stepSizeIndex]*2 < this->size ; stepSizeIndex++){
		;
	}
	stepSizeIndex--;

	for ( ; stepSizeIndex >=0 ; stepSizeIndex--){
		stepSize = stepSizeList[stepSizeIndex];
		beginNode = this->begin;
		for (int i=0 ; i<stepSize ; i++){
			sortedLastNode = beginNode;
			while(1){
				unsortedFirstNode = sortedLastNode;
				for (int j=0 ; j<stepSize ; j++){
					if (unsortedFirstNode->next != NULL){
						unsortedFirstNode = unsortedFirstNode->next;
					}
					else if (unsortedFirstNode->next == NULL){
						goto NEW_BEGIN_NODE;
					}
				}
				currentNode = sortedLastNode;
				currentNextNode = unsortedFirstNode;
				memcpy(&buffer, unsortedFirstNode, sizeof(LIST_NODE));
				while(1){
					if (strcmp(currentNode->name, buffer.name) > 0){
						memcpy(currentNextNode->name, currentNode->name, NAME_LEN);
						currentNextNode->number = currentNode->number;
						if (currentNode == beginNode){
							memcpy(currentNode->name, buffer.name, NAME_LEN);
							currentNode->number = buffer.number;
							goto ADDING_SORTED_NODE_DONE;
						}
						else if (currentNode != beginNode){
							currentNextNode = currentNode;
							for (int k=0 ; k<stepSize ; k++){
								currentNode = currentNode->prev;
							}
							continue;
						}
					}
					else {
						memcpy(currentNextNode->name, buffer.name, NAME_LEN);
						currentNextNode->number = buffer.number;
						goto ADDING_SORTED_NODE_DONE;
					}
				}
ADDING_SORTED_NODE_DONE: sortedLastNode = unsortedFirstNode;
			}
NEW_BEGIN_NODE: beginNode = beginNode->next;
		}
	}

	return this;
}

