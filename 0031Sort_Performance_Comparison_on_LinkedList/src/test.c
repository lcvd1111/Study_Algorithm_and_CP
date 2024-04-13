#include "test.h"
#define TEST_SIZE 1000
#define TEST_SIZE2 5000

typedef struct _SORT_COMPARE_NODE SORT_COMPARE_NODE;
struct _SORT_COMPARE_NODE {
	char sortingName[32];
	double duration;
};

int SortDurationCompare(const void *prev, const void *rear)
{
	//Function for qsort()
	double compareResult = (((SORT_COMPARE_NODE *)prev)->duration) - (((SORT_COMPARE_NODE *)rear)->duration);

	if (compareResult > 0){
		return 1;
	}

	if (compareResult == 0){
		return 0;
	}

	return -1;
}

int UnitTest_List(void)
{
	LIST testList1;
	LIST testList2;
	LIST_METHOD_CONSTRUCTOR(&testList1);
	LIST_METHOD_CONSTRUCTOR(&testList2);

	((testList1.Method)->Add_Random)(&testList1, 100);
	((testList2.Method)->Add_Random)(&testList2, 50);

	//((testList1.Method)->Print)(&testList1);
	//((testList1.Method)->Print)(&testList2);

	((testList1.Method)->Copy_to_List)(&testList1, &testList2);
	//((testList2.Method)->Print)(&testList2);

	LIST_METHOD_DESTRUCTOR(&testList1);
	LIST_METHOD_DESTRUCTOR(&testList2);

	return 0;
}

int CompareFunc(const void *prev, const void *rear)
{
	return strcmp(((LIST_NODE *)prev)->name,((LIST_NODE *)rear)->name);
}

int UnitTest_BubbleSort(void)
{
	LIST testList;
	LIST_METHOD_CONSTRUCTOR(&testList);
	LIST_NODE testArray[TEST_SIZE];
	memset(testArray, 0, sizeof(LIST_NODE)*(TEST_SIZE));
	LIST_NODE *temp = NULL;

	(testList.Method->Add_Random)(&testList, TEST_SIZE);
	(testList.Method->Copy_to_Array)(&testList, testArray);

	(testList.Method->Sort->Bubble)(&testList);
	//(testList.Method->Print)(&testList);
	qsort(testArray, TEST_SIZE, sizeof(LIST_NODE), &CompareFunc);

	temp = testList.begin;
	for (int i=0 ; i<testList.size ; i++){
		if (strcmp(temp->name, testArray[i].name)){
			return (-1-i);
		}
		temp = temp->next;
	}

	LIST_METHOD_DESTRUCTOR(&testList);

	return 0;
}

int UnitTest_InsertionSort(void)
{
	LIST testList;
	LIST_METHOD_CONSTRUCTOR(&testList);
	LIST_NODE testArray[TEST_SIZE];
	memset(testArray, 0, sizeof(LIST_NODE)*(TEST_SIZE));
	LIST_NODE *temp = NULL;

	(testList.Method->Add_Random)(&testList, TEST_SIZE);
	(testList.Method->Copy_to_Array)(&testList, testArray);

	(testList.Method->Sort->Insertion)(&testList);
	//(testList.Method->Print)(&testList);
	qsort(testArray, TEST_SIZE, sizeof(LIST_NODE), &CompareFunc);

	temp = testList.begin;
	for (int i=0 ; i<testList.size ; i++){
		if (strcmp(temp->name, testArray[i].name)){
			return (-1-i);
		}
		temp = temp->next;
	}

	LIST_METHOD_DESTRUCTOR(&testList);

	return 0;
}

int UnitTest_SelectionSort(void)
{
	LIST testList;
	LIST_METHOD_CONSTRUCTOR(&testList);
	LIST_NODE testArray[TEST_SIZE];
	memset(testArray, 0, sizeof(LIST_NODE)*(TEST_SIZE));
	LIST_NODE *temp = NULL;

	(testList.Method->Add_Random)(&testList, TEST_SIZE);
	(testList.Method->Copy_to_Array)(&testList, testArray);

	(testList.Method->Sort->Selection)(&testList);
	//(testList.Method->Print)(&testList);
	qsort(testArray, TEST_SIZE, sizeof(LIST_NODE), &CompareFunc);

	temp = testList.begin;
	for (int i=0 ; i<testList.size ; i++){
		if (strcmp(temp->name, testArray[i].name)){
			return (-1-i);
		}
		temp = temp->next;
	}

	LIST_METHOD_DESTRUCTOR(&testList);

	return 0;
}

int UnitTest_HeapSort(void)
{
	LIST testList;
	LIST_METHOD_CONSTRUCTOR(&testList);
	LIST_NODE testArray[TEST_SIZE];
	memset(testArray, 0, sizeof(LIST_NODE)*(TEST_SIZE));
	LIST_NODE *temp = NULL;

	(testList.Method->Add_Random)(&testList, TEST_SIZE);
	(testList.Method->Copy_to_Array)(&testList, testArray);

	(testList.Method->Sort->Heap)(&testList);
	//(testList.Method->Print)(&testList);
	qsort(testArray, TEST_SIZE, sizeof(LIST_NODE), &CompareFunc);

	temp = testList.begin;
	for (int i=0 ; i<testList.size ; i++){
		if (strcmp(temp->name, testArray[i].name)){
			return (-1-i);
		}
		temp = temp->next;
	}

	LIST_METHOD_DESTRUCTOR(&testList);

	return 0;
}

int UnitTest_TreeSort(void)
{
	LIST testList;
	LIST_METHOD_CONSTRUCTOR(&testList);
	LIST_NODE testArray[TEST_SIZE];
	memset(testArray, 0, sizeof(LIST_NODE)*(TEST_SIZE));
	LIST_NODE *temp = NULL;

	(testList.Method->Add_Random)(&testList, TEST_SIZE);
	(testList.Method->Copy_to_Array)(&testList, testArray);

	(testList.Method->Sort->Tree)(&testList);
	//(testList.Method->Print)(&testList);
	qsort(testArray, TEST_SIZE, sizeof(LIST_NODE), &CompareFunc);

	temp = testList.begin;
	for (int i=0 ; i<testList.size ; i++){
		if (strcmp(temp->name, testArray[i].name)){
			return (-1-i);
		}
		temp = temp->next;
	}

	LIST_METHOD_DESTRUCTOR(&testList);

	return 0;
}

int UnitTest_QuickSort(void)
{
	LIST testList;
	LIST_METHOD_CONSTRUCTOR(&testList);
	LIST_NODE testArray[TEST_SIZE];
	memset(testArray, 0, sizeof(LIST_NODE)*(TEST_SIZE));
	LIST_NODE *temp = NULL;

	(testList.Method->Add_Random)(&testList, TEST_SIZE);
	(testList.Method->Copy_to_Array)(&testList, testArray);

	(testList.Method->Sort->Quick)(&testList);
	//(testList.Method->Print)(&testList);
	qsort(testArray, TEST_SIZE, sizeof(LIST_NODE), &CompareFunc);

	temp = testList.begin;
	for (int i=0 ; i<testList.size ; i++){
		if (strcmp(temp->name, testArray[i].name)){
			return (-1-i);
		}
		temp = temp->next;
	}

	LIST_METHOD_DESTRUCTOR(&testList);

	return 0;
}

int UnitTest_MergeSort(void)
{
	LIST testList;
	LIST_METHOD_CONSTRUCTOR(&testList);
	LIST_NODE testArray[TEST_SIZE];
	memset(testArray, 0, sizeof(LIST_NODE)*(TEST_SIZE));
	LIST_NODE *temp = NULL;

	(testList.Method->Add_Random)(&testList, TEST_SIZE);
	(testList.Method->Copy_to_Array)(&testList, testArray);

	(testList.Method->Sort->Merge)(&testList);
	//(testList.Method->Print)(&testList);
	qsort(testArray, TEST_SIZE, sizeof(LIST_NODE), &CompareFunc);

	temp = testList.begin;
	for (int i=0 ; i<testList.size ; i++){
		if (strcmp(temp->name, testArray[i].name)){
			return (-1-i);
		}
		temp = temp->next;
	}

	LIST_METHOD_DESTRUCTOR(&testList);

	return 0;
}

int UnitTest_ShellSort(void)
{
	LIST testList;
	LIST_METHOD_CONSTRUCTOR(&testList);
	LIST_NODE testArray[TEST_SIZE];
	memset(testArray, 0, sizeof(LIST_NODE)*(TEST_SIZE));
	LIST_NODE *temp = NULL;

	(testList.Method->Add_Random)(&testList, TEST_SIZE);
	(testList.Method->Copy_to_Array)(&testList, testArray);

	(testList.Method->Sort->Shell)(&testList);
	//(testList.Method->Print)(&testList);
	qsort(testArray, TEST_SIZE, sizeof(LIST_NODE), &CompareFunc);

	temp = testList.begin;
	for (int i=0 ; i<testList.size ; i++){
		if (strcmp(temp->name, testArray[i].name)){
			return (-1-i);
		}
		temp = temp->next;
	}

	LIST_METHOD_DESTRUCTOR(&testList);

	return 0;
}

int UnitTest(void)
{
	int errCode = 0;
	printf(COLOR_BLACK "Unit Test for List: " COLOR_BLACK);
	if (errCode = UnitTest_List()){
		printf(COLOR_RED "FAIL\n" COLOR_BLACK );
		printf(COLOR_RED "Error Code: %d\n" COLOR_BLACK, errCode);
		return -1;
	}

	printf(COLOR_BLACK "Unit Test for Bubble Sort on list: " COLOR_BLACK);
	if (errCode = UnitTest_BubbleSort()){
		printf(COLOR_RED "FAIL\n" COLOR_BLACK );
		printf(COLOR_RED "Error Code: %d\n" COLOR_BLACK, errCode);
		return -2;
	}
	printf(COLOR_GREEN "SUCCESS\n" COLOR_BLACK );

	printf(COLOR_BLACK "Unit Test for Insertion Sort on list: " COLOR_BLACK);
	if (errCode = UnitTest_InsertionSort()){
		printf(COLOR_RED "FAIL\n" COLOR_BLACK );
		printf(COLOR_RED "Error Code: %d\n" COLOR_BLACK, errCode);
		return -3;
	}
	printf(COLOR_GREEN "SUCCESS\n" COLOR_BLACK );

	printf(COLOR_BLACK "Unit Test for Selection Sort on list: " COLOR_BLACK);
	if (errCode = UnitTest_SelectionSort()){
		printf(COLOR_RED "FAIL\n" COLOR_BLACK );
		printf(COLOR_RED "Error Code: %d\n" COLOR_BLACK, errCode);
		return -4;
	}
	printf(COLOR_GREEN "SUCCESS\n" COLOR_BLACK );

	printf(COLOR_BLACK "Unit Test for Quick Sort on list: " COLOR_BLACK);
	if (errCode = UnitTest_QuickSort()){
		printf(COLOR_RED "FAIL\n" COLOR_BLACK );
		printf(COLOR_RED "Error Code: %d\n" COLOR_BLACK, errCode);
		return -7;
	}
	printf(COLOR_GREEN "SUCCESS\n" COLOR_BLACK );

	printf(COLOR_BLACK "Unit Test for Merge Sort on list: " COLOR_BLACK);
	if (errCode = UnitTest_MergeSort()){
		printf(COLOR_RED "FAIL\n" COLOR_BLACK );
		printf(COLOR_RED "Error Code: %d\n" COLOR_BLACK, errCode);
		return -8;
	}
	printf(COLOR_GREEN "SUCCESS\n" COLOR_BLACK );

	printf(COLOR_BLACK "Unit Test for Heap Sort on list: " COLOR_BLACK);
	if (errCode = UnitTest_HeapSort()){
		printf(COLOR_RED "FAIL\n" COLOR_BLACK );
		printf(COLOR_RED "Error Code: %d\n" COLOR_BLACK, errCode);
		return -5;
	}
	printf(COLOR_GREEN "SUCCESS\n" COLOR_BLACK );

	printf(COLOR_BLACK "Unit Test for Tree Sort on list: " COLOR_BLACK);
	if (errCode = UnitTest_TreeSort()){
		printf(COLOR_RED "FAIL\n" COLOR_BLACK );
		printf(COLOR_RED "Error Code: %d\n" COLOR_BLACK, errCode);
		return -6;
	}
	printf(COLOR_GREEN "SUCCESS\n" COLOR_BLACK );

	printf(COLOR_BLACK "Unit Test for Shell Sort on list: " COLOR_BLACK);
	if (errCode = UnitTest_ShellSort()){
		printf(COLOR_RED "FAIL\n" COLOR_BLACK );
		printf(COLOR_RED "Error Code: %d\n" COLOR_BLACK, errCode);
		return -9;
	}
	printf(COLOR_GREEN "SUCCESS\n" COLOR_BLACK );
	printf("\n");

	return 0;
}

int Sort_Comparison(void)
{
	struct timeval time_begin, time_end, time_duration;
	SORT_COMPARE_NODE sortingDurationArray[8] = {{.sortingName="Bubble Sort", .duration=0},
												{.sortingName="Insertion Sort", .duration=0},
												{.sortingName="Selection Sort", .duration=0},
												{.sortingName="Heap Sort", .duration=0},
												{.sortingName="Tree Sort", .duration=0},
												{.sortingName="Quick Sort", .duration=0},
												{.sortingName="Merge Sort", .duration=0},
												{.sortingName="Shell Sort", .duration=0}};

	LIST testLists[8];
	for (int i=0 ; i<8 ; i++){
		LIST_METHOD_CONSTRUCTOR(testLists+i);
	}

	((testLists[0].Method)->Add_Random)(testLists + 0, TEST_SIZE2);
	for (int i=1; i<8 ; i++){
		((testLists[0].Method)->Copy_to_List)(testLists+0, testLists+i);
	}

	printf("<List Size>: %d\n", TEST_SIZE2);

	gettimeofday(&time_begin, NULL);
	(((testLists[0].Method)->Sort)->Bubble)(&testLists[0]);
	gettimeofday(&time_end, NULL);
	timersub(&time_end, &time_begin, &time_duration);
	sortingDurationArray[0].duration = (double)(time_duration.tv_sec) + ((double)(time_duration.tv_usec)/((double)(1000000)));

	gettimeofday(&time_begin, NULL);
	(((testLists[1].Method)->Sort)->Insertion)(&testLists[1]);
	gettimeofday(&time_end, NULL);
	timersub(&time_end, &time_begin, &time_duration);
	sortingDurationArray[1].duration = (double)(time_duration.tv_sec) + ((double)(time_duration.tv_usec)/((double)(1000000)));

	gettimeofday(&time_begin, NULL);
	(((testLists[2].Method)->Sort)->Selection)(&testLists[2]);
	gettimeofday(&time_end, NULL);
	timersub(&time_end, &time_begin, &time_duration);
	sortingDurationArray[2].duration = (double)(time_duration.tv_sec) + ((double)(time_duration.tv_usec)/((double)(1000000)));

	gettimeofday(&time_begin, NULL);
	(((testLists[3].Method)->Sort)->Heap)(&testLists[3]);
	gettimeofday(&time_end, NULL);
	timersub(&time_end, &time_begin, &time_duration);
	sortingDurationArray[3].duration = (double)(time_duration.tv_sec) + ((double)(time_duration.tv_usec)/((double)(1000000)));

	gettimeofday(&time_begin, NULL);
	(((testLists[4].Method)->Sort)->Tree)(&testLists[4]);
	gettimeofday(&time_end, NULL);
	timersub(&time_end, &time_begin, &time_duration);
	sortingDurationArray[4].duration = (double)(time_duration.tv_sec) + ((double)(time_duration.tv_usec)/((double)(1000000)));

	gettimeofday(&time_begin, NULL);
	(((testLists[5].Method)->Sort)->Quick)(&testLists[5]);
	gettimeofday(&time_end, NULL);
	timersub(&time_end, &time_begin, &time_duration);
	sortingDurationArray[5].duration = (double)(time_duration.tv_sec) + ((double)(time_duration.tv_usec)/((double)(1000000)));

	gettimeofday(&time_begin, NULL);
	(((testLists[6].Method)->Sort)->Merge)(&testLists[6]);
	gettimeofday(&time_end, NULL);
	timersub(&time_end, &time_begin, &time_duration);
	sortingDurationArray[6].duration = (double)(time_duration.tv_sec) + ((double)(time_duration.tv_usec)/((double)(1000000)));

	gettimeofday(&time_begin, NULL);
	(((testLists[7].Method)->Sort)->Shell)(&testLists[7]);
	gettimeofday(&time_end, NULL);
	timersub(&time_end, &time_begin, &time_duration);
	sortingDurationArray[7].duration = (double)(time_duration.tv_sec) + ((double)(time_duration.tv_usec)/((double)(1000000)));

	qsort(sortingDurationArray, 8, sizeof(SORT_COMPARE_NODE), &SortDurationCompare);

	for (int i=0 ; i<8 ; i++){
		printf("[%d] %s, Duration=%lf\n", i+1, sortingDurationArray[i].sortingName, sortingDurationArray[i].duration);
	}

	for (int i=0 ; i<8 ; i++){
		LIST_METHOD_DESTRUCTOR(testLists+i);
	}

	printf("\n");


	return 0;
}
