#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	if (l < r) {
		int s = l + (r - l) / 2;
		mergeSort(pData, l, s);
		mergeSort(pData, s + 1, r);

		int d1 = m - l + 1;
		int d2 = r - m;

		int* L = (int*)malloc(d1 * sizeof(int));
		int* R = (int*)malloc(d2 * sizeof(int));

		extraMemoryAllocated += d1 * sizeof(int) + d2 * sizeof(int);

		for (int i = 0; i < d1; i++) {
			L[i] = pData[l + i];
		}
		for (int j = 0; j < d2; j++) {
			R[j] = pData[m + 1 + j];
		}

		int i = 0, j = 0, k = l;
		while (i < d1 && j < d2) {
			if (L[i] <= R[j]) {
				pData[k] = L[i];
				i++;
			}
			else {
				pData[k] = R[j];
				j++;
			}
			k++;
		}

		while (i < d1) {
			pData[k] = L[i];
			i++;
			k++;
		}

		while (j < d2) {
			pData[k] = R[j];
			j++;
			k++;
		}

		free(L);
		free(R);
	}
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	for (int i = 1; i < n; i++)
	{
		int ist = pData[i];
		int m = i - 1;

		while (m >= 0 && pData[m] > ist)
		{
			pData[m + 1] = pData[m];
			m--;
		}

		pData[m + 1] = ist;
	}

}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	for (int i = 0; i < n - 1; i++) 
	{
		int swap = 0;
		for (int j = 0; j < n - i - 1; j++) 
		{
			if (pData[j] > pData[j + 1]) 
			{
				// Swap the elements
				int temp = pData[j];
				pData[j] = pData[j + 1];
				pData[j + 1] = temp;
				swap = 1;
			}
		}
		
		if (swap == 0)
			break;
	}

}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	for (int i = 0; i < n - 1; i++) 
	{
		int minInd = i;
		for (int j = i + 1; j < n; j++) 
		{
			if (pData[j] < pData[minInd])
			{
				minInd = j;
			}
		}
		
		int temp = pData[i];
		pData[i] = pData[minInd];
		pData[minInd] = temp;
	}

}

// parses input file to an integer array
int parseData(char* inputFileName, int** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (int*)malloc(sizeof(int) * dataSz);
		// Implement parse data block
	}

	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i = 0; i < 100; ++i)
	{
		printf("%d ", pData[i]);
	}
	printf("\n\t");

	for (i = sz; i < dataSz; ++i)
	{
		printf("%d ", pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
	double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt" };

	for (i = 0; i < 3; ++i)
	{
		int* pDataSrc, * pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);

		if (dataSz <= 0)
			continue;

		pDataCopy = (int*)malloc(sizeof(int) * dataSz);

		printf("---------------------------\n");
		printf("Dataset Size : %d\n", dataSz);
		printf("---------------------------\n");

		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
		printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
		printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
		printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
		printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		free(pDataCopy);
		free(pDataSrc);
	}

}