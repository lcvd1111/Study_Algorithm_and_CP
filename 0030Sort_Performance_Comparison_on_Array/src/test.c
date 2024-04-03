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
	double compareResult = (((SORT_COMPARE_NODE *)prev)->duration) - (((SORT_COMPARE_NODE *)rear)->duration);

	if (compareResult > 0){
		return 1;
	}

	if (compareResult == 0){
		return 0;
	}

	return -1;
}

int UnitTest_Array(void)
{
	ARRAY testArray1;
	ARRAY testArray2;
	ARRAY_METHOD_CONSTRUCTOR(&testArray1, 100);
	ARRAY_METHOD_CONSTRUCTOR(&testArray2, 50);

	((testArray1.Method)->Fill_Random)(&testArray1);
	((testArray2.Method)->Fill_Random)(&testArray2);

	//((testArray1.Method)->Print)(&testArray1);
	//((testArray1.Method)->Print)(&testArray2);

	((testArray1.Method)->Copy_to_Array)(&testArray1, &testArray2);
	//((testArray2.Method)->Print)(&testArray2);

	ARRAY_METHOD_DESTRUCTOR(&testArray1);
	ARRAY_METHOD_DESTRUCTOR(&testArray2);

	return 0;
}

int CustomCompare(const void *prev, const void *rear)
{
	return (strcmp(((NODE *)prev)->name, ((NODE *)rear)->name));
}

int UnitTest_BubbleSort(void)
{
	ARRAY testArray;
	ARRAY_METHOD_CONSTRUCTOR(&testArray, TEST_SIZE);
	NODE testRawArray[TEST_SIZE];

	((testArray.Method)->Fill_Random)(&testArray);
	//((testArray.Method)->Print)(&testArray);
	((testArray.Method)->Copy_to_Raw_Array)(&testArray, testRawArray);

	(((testArray.Method)->Sort)->Bubble_Sort)(&testArray);
	//((testArray.Method)->Print)(&testArray);

	qsort(testRawArray, TEST_SIZE, sizeof(NODE), &CustomCompare);

	for (int i=0 ; i<TEST_SIZE ;i++){
		if (strcmp(testArray.nodeArray[i].name, testRawArray[i].name)){
			return -1-i;
		}
	}
	
	ARRAY_METHOD_DESTRUCTOR(&testArray);

	return 0;
}

int UnitTest_InsertionSort(void)
{
	ARRAY testArray;
	ARRAY_METHOD_CONSTRUCTOR(&testArray, TEST_SIZE);
	NODE testRawArray[TEST_SIZE];

	((testArray.Method)->Fill_Random)(&testArray);
	//((testArray.Method)->Print)(&testArray);
	((testArray.Method)->Copy_to_Raw_Array)(&testArray, testRawArray);

	(((testArray.Method)->Sort)->Insertion_Sort)(&testArray);
	//((testArray.Method)->Print)(&testArray);

	qsort(testRawArray, TEST_SIZE, sizeof(NODE), &CustomCompare);

	for (int i=0 ; i<TEST_SIZE ;i++){
		if (strcmp(testArray.nodeArray[i].name, testRawArray[i].name)){
			return -1-i;
		}
	}
	
	ARRAY_METHOD_DESTRUCTOR(&testArray);

	return 0;
}

int UnitTest_SelectionSort(void)
{
	ARRAY testArray;
	ARRAY_METHOD_CONSTRUCTOR(&testArray, TEST_SIZE);
	NODE testRawArray[TEST_SIZE];

	((testArray.Method)->Fill_Random)(&testArray);
	//((testArray.Method)->Print)(&testArray);
	((testArray.Method)->Copy_to_Raw_Array)(&testArray, testRawArray);

	(((testArray.Method)->Sort)->Selection_Sort)(&testArray);
	//((testArray.Method)->Print)(&testArray);

	qsort(testRawArray, TEST_SIZE, sizeof(NODE), &CustomCompare);

	for (int i=0 ; i<TEST_SIZE ;i++){
		if (strcmp(testArray.nodeArray[i].name, testRawArray[i].name)){
			return -1-i;
		}
	}
	
	ARRAY_METHOD_DESTRUCTOR(&testArray);

	return 0;
}

int UnitTest_HeapSort(void)
{
	ARRAY testArray;
	ARRAY_METHOD_CONSTRUCTOR(&testArray, TEST_SIZE);
	NODE testRawArray[TEST_SIZE];

	((testArray.Method)->Fill_Random)(&testArray);
	//((testArray.Method)->Print)(&testArray);
	((testArray.Method)->Copy_to_Raw_Array)(&testArray, testRawArray);

	(((testArray.Method)->Sort)->Heap_Sort)(&testArray);
	//((testArray.Method)->Print)(&testArray);

	qsort(testRawArray, TEST_SIZE, sizeof(NODE), &CustomCompare);

	for (int i=0 ; i<TEST_SIZE ;i++){
		if (strcmp(testArray.nodeArray[i].name, testRawArray[i].name)){
			return -1-i;
		}
	}
	
	ARRAY_METHOD_DESTRUCTOR(&testArray);

	return 0;
}

int UnitTest_TreeSort(void)
{
	ARRAY testArray;
	ARRAY_METHOD_CONSTRUCTOR(&testArray, TEST_SIZE);
	NODE testRawArray[TEST_SIZE];

	((testArray.Method)->Fill_Random)(&testArray);
	//((testArray.Method)->Print)(&testArray);
	((testArray.Method)->Copy_to_Raw_Array)(&testArray, testRawArray);

	(((testArray.Method)->Sort)->Tree_Sort)(&testArray);
	//((testArray.Method)->Print)(&testArray);

	qsort(testRawArray, TEST_SIZE, sizeof(NODE), &CustomCompare);

	for (int i=0 ; i<TEST_SIZE ;i++){
		if (strcmp(testArray.nodeArray[i].name, testRawArray[i].name)){
			return -1-i;
		}
	}
	
	ARRAY_METHOD_DESTRUCTOR(&testArray);

	return 0;
}

int UnitTest_QuickSort(void)
{
	ARRAY testArray;
	ARRAY_METHOD_CONSTRUCTOR(&testArray, TEST_SIZE);
	NODE testRawArray[TEST_SIZE];

	((testArray.Method)->Fill_Random)(&testArray);
	//((testArray.Method)->Print)(&testArray);
	((testArray.Method)->Copy_to_Raw_Array)(&testArray, testRawArray);

	(((testArray.Method)->Sort)->Quick_Sort)(&testArray);
	//((testArray.Method)->Print)(&testArray);

	qsort(testRawArray, TEST_SIZE, sizeof(NODE), &CustomCompare);

	for (int i=0 ; i<TEST_SIZE ;i++){
		if (strcmp(testArray.nodeArray[i].name, testRawArray[i].name)){
			return -1-i;
		}
	}
	
	ARRAY_METHOD_DESTRUCTOR(&testArray);

	return 0;
}

int UnitTest_MergeSort(void)
{
	ARRAY testArray;
	ARRAY_METHOD_CONSTRUCTOR(&testArray, TEST_SIZE);
	NODE testRawArray[TEST_SIZE];

	((testArray.Method)->Fill_Random)(&testArray);
	//((testArray.Method)->Print)(&testArray);
	((testArray.Method)->Copy_to_Raw_Array)(&testArray, testRawArray);

	(((testArray.Method)->Sort)->Merge_Sort)(&testArray);
	//((testArray.Method)->Print)(&testArray);

	qsort(testRawArray, TEST_SIZE, sizeof(NODE), &CustomCompare);

	for (int i=0 ; i<TEST_SIZE ;i++){
		if (strcmp(testArray.nodeArray[i].name, testRawArray[i].name)){
			return -1-i;
		}
	}
	
	ARRAY_METHOD_DESTRUCTOR(&testArray);

	return 0;
}

int UnitTest_ShellSort(void)
{
	ARRAY testArray;
	ARRAY_METHOD_CONSTRUCTOR(&testArray, TEST_SIZE);
	NODE testRawArray[TEST_SIZE];

	((testArray.Method)->Fill_Random)(&testArray);
	//((testArray.Method)->Print)(&testArray);
	((testArray.Method)->Copy_to_Raw_Array)(&testArray, testRawArray);

	(((testArray.Method)->Sort)->Shell_Sort)(&testArray);
	//((testArray.Method)->Print)(&testArray);

	qsort(testRawArray, TEST_SIZE, sizeof(NODE), &CustomCompare);

	for (int i=0 ; i<TEST_SIZE ;i++){
		if (strcmp(testArray.nodeArray[i].name, testRawArray[i].name)){
			return -1-i;
		}
	}
	
	ARRAY_METHOD_DESTRUCTOR(&testArray);

	return 0;
}

int UnitTest(void)
{
	int errCode = 0;
	printf(COLOR_BLACK "Unit Test for Array: " COLOR_BLACK);
	if (errCode = UnitTest_Array()){
		printf(COLOR_RED "FAIL\n" COLOR_BLACK );
		printf(COLOR_RED "Error Code: %d\n" COLOR_BLACK, errCode);
		return -1;
	}

	printf(COLOR_BLACK "Unit Test for Bubble Sort on array: " COLOR_BLACK);
	if (errCode = UnitTest_BubbleSort()){
		printf(COLOR_RED "FAIL\n" COLOR_BLACK );
		printf(COLOR_RED "Error Code: %d\n" COLOR_BLACK, errCode);
		return -2;
	}
	printf(COLOR_GREEN "SUCCESS\n" COLOR_BLACK );

	printf(COLOR_BLACK "Unit Test for Insertion Sort on array: " COLOR_BLACK);
	if (errCode = UnitTest_InsertionSort()){
		printf(COLOR_RED "FAIL\n" COLOR_BLACK );
		printf(COLOR_RED "Error Code: %d\n" COLOR_BLACK, errCode);
		return -3;
	}
	printf(COLOR_GREEN "SUCCESS\n" COLOR_BLACK );

	printf(COLOR_BLACK "Unit Test for Selection Sort on array: " COLOR_BLACK);
	if (errCode = UnitTest_SelectionSort()){
		printf(COLOR_RED "FAIL\n" COLOR_BLACK );
		printf(COLOR_RED "Error Code: %d\n" COLOR_BLACK, errCode);
		return -4;
	}
	printf(COLOR_GREEN "SUCCESS\n" COLOR_BLACK );

	printf(COLOR_BLACK "Unit Test for Quick Sort on array: " COLOR_BLACK);
	if (errCode = UnitTest_QuickSort()){
		printf(COLOR_RED "FAIL\n" COLOR_BLACK );
		printf(COLOR_RED "Error Code: %d\n" COLOR_BLACK, errCode);
		return -7;
	}
	printf(COLOR_GREEN "SUCCESS\n" COLOR_BLACK );

	printf(COLOR_BLACK "Unit Test for Merge Sort on array: " COLOR_BLACK);
	if (errCode = UnitTest_MergeSort()){
		printf(COLOR_RED "FAIL\n" COLOR_BLACK );
		printf(COLOR_RED "Error Code: %d\n" COLOR_BLACK, errCode);
		return -8;
	}
	printf(COLOR_GREEN "SUCCESS\n" COLOR_BLACK );

	printf(COLOR_BLACK "Unit Test for Heap Sort on array: " COLOR_BLACK);
	if (errCode = UnitTest_HeapSort()){
		printf(COLOR_RED "FAIL\n" COLOR_BLACK );
		printf(COLOR_RED "Error Code: %d\n" COLOR_BLACK, errCode);
		return -5;
	}
	printf(COLOR_GREEN "SUCCESS\n" COLOR_BLACK );

	printf(COLOR_BLACK "Unit Test for Tree Sort on array: " COLOR_BLACK);
	if (errCode = UnitTest_TreeSort()){
		printf(COLOR_RED "FAIL\n" COLOR_BLACK );
		printf(COLOR_RED "Error Code: %d\n" COLOR_BLACK, errCode);
		return -6;
	}
	printf(COLOR_GREEN "SUCCESS\n" COLOR_BLACK );

	printf(COLOR_BLACK "Unit Test for Shell Sort on array: " COLOR_BLACK);
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

	ARRAY testArrays[8];
	for (int i=0 ; i<8 ; i++){
		ARRAY_METHOD_CONSTRUCTOR(testArrays+i, TEST_SIZE2);
	}

	((testArrays[0].Method)->Fill_Random)(testArrays + 0);
	for (int i=1; i<8 ; i++){
		((testArrays[0].Method)->Copy_to_Array)(testArrays+0, testArrays+i);
	}

	printf("<Array Size>: %d\n", TEST_SIZE2);

	gettimeofday(&time_begin, NULL);
	(((testArrays[0].Method)->Sort)->Bubble_Sort)(&testArrays[0]);
	gettimeofday(&time_end, NULL);
	timersub(&time_end, &time_begin, &time_duration);
	sortingDurationArray[0].duration = (double)(time_duration.tv_sec) + ((double)(time_duration.tv_usec)/((double)(1000000)));

	gettimeofday(&time_begin, NULL);
	(((testArrays[1].Method)->Sort)->Insertion_Sort)(&testArrays[1]);
	gettimeofday(&time_end, NULL);
	timersub(&time_end, &time_begin, &time_duration);
	sortingDurationArray[1].duration = (double)(time_duration.tv_sec) + ((double)(time_duration.tv_usec)/((double)(1000000)));

	gettimeofday(&time_begin, NULL);
	(((testArrays[2].Method)->Sort)->Selection_Sort)(&testArrays[2]);
	gettimeofday(&time_end, NULL);
	timersub(&time_end, &time_begin, &time_duration);
	sortingDurationArray[2].duration = (double)(time_duration.tv_sec) + ((double)(time_duration.tv_usec)/((double)(1000000)));

	gettimeofday(&time_begin, NULL);
	(((testArrays[3].Method)->Sort)->Heap_Sort)(&testArrays[3]);
	gettimeofday(&time_end, NULL);
	timersub(&time_end, &time_begin, &time_duration);
	sortingDurationArray[3].duration = (double)(time_duration.tv_sec) + ((double)(time_duration.tv_usec)/((double)(1000000)));

	gettimeofday(&time_begin, NULL);
	(((testArrays[4].Method)->Sort)->Tree_Sort)(&testArrays[4]);
	gettimeofday(&time_end, NULL);
	timersub(&time_end, &time_begin, &time_duration);
	sortingDurationArray[4].duration = (double)(time_duration.tv_sec) + ((double)(time_duration.tv_usec)/((double)(1000000)));

	gettimeofday(&time_begin, NULL);
	(((testArrays[5].Method)->Sort)->Quick_Sort)(&testArrays[5]);
	gettimeofday(&time_end, NULL);
	timersub(&time_end, &time_begin, &time_duration);
	sortingDurationArray[5].duration = (double)(time_duration.tv_sec) + ((double)(time_duration.tv_usec)/((double)(1000000)));

	gettimeofday(&time_begin, NULL);
	(((testArrays[6].Method)->Sort)->Merge_Sort)(&testArrays[6]);
	gettimeofday(&time_end, NULL);
	timersub(&time_end, &time_begin, &time_duration);
	sortingDurationArray[6].duration = (double)(time_duration.tv_sec) + ((double)(time_duration.tv_usec)/((double)(1000000)));

	gettimeofday(&time_begin, NULL);
	(((testArrays[7].Method)->Sort)->Shell_Sort)(&testArrays[7]);
	gettimeofday(&time_end, NULL);
	timersub(&time_end, &time_begin, &time_duration);
	sortingDurationArray[7].duration = (double)(time_duration.tv_sec) + ((double)(time_duration.tv_usec)/((double)(1000000)));

	qsort(sortingDurationArray, 8, sizeof(SORT_COMPARE_NODE), &SortDurationCompare);

	for (int i=0 ; i<8 ; i++){
		printf("[%d] %s, Duration=%lf\n", i+1, sortingDurationArray[i].sortingName, sortingDurationArray[i].duration);
	}

	for (int i=0 ; i<8 ; i++){
		ARRAY_METHOD_DESTRUCTOR(testArrays+i);
	}

	printf("\n");

	return 0;
}
