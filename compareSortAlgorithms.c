#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = (int*)malloc(n1 * sizeof(int)); // Allocate memory for left subarray
    int* R = (int*)malloc(n2 * sizeof(int)); // Allocate memory for right subarray

    extraMemoryAllocated += n1 * sizeof(int) + n2 * sizeof(int);

    // Copy data to temp arrays
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r]
    i = 0; // Initial index of left subarray
    j = 0; // Initial index of right subarray
    k = l; // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L); // Deallocate memory for left subarray
    free(R); // Deallocate memory for right subarray

    extraMemoryAllocated -= n1 * sizeof(int) + n2 * sizeof(int);
}

void mergeSortRecursive(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSortRecursive(arr, l, m);
        mergeSortRecursive(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void mergeSort(int pData[], int l, int r) {
    extraMemoryAllocated = 0;
    mergeSortRecursive(pData, l, r);
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n) {
    extraMemoryAllocated = 0;
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = pData[i];
        j = i - 1;

        /* Move elements of pData[0..i-1], that are greater than key, to one position ahead of their current position */
        while (j >= 0 && pData[j] > key) {
            pData[j + 1] = pData[j];
            j = j - 1;
        }
        pData[j + 1] = key;
    }
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n) {
    extraMemoryAllocated = 0;
    int i, j;
    for (i = 0; i < n - 1; i++) {
        // Last i elements are already in place, so we don't need to check them again
        for (j = 0; j < n - i - 1; j++) {
            if (pData[j] > pData[j + 1]) {
                // Swap pData[j] and pData[j+1]
                int temp = pData[j];
                pData[j] = pData[j + 1];
                pData[j + 1] = temp;
            }
        }
    }
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n) {
    extraMemoryAllocated = 0;
    int i, j, minIndex, temp;
    for (i = 0; i < n - 1; i++) {
        minIndex = i;
        for (j = i + 1; j < n; j++) {
            if (pData[j] < pData[minIndex]) {
                minIndex = j;
            }
        }

        // Swap pData[i] and pData[minIndex]
        temp = pData[i];
        pData[i] = pData[minIndex];
        pData[minIndex] = temp;
    }
}

// parses input file to an integer array
int parseData(char* inputFileName, int** ppData) {
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    *ppData = NULL;

    if (inFile) {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (int*)malloc(sizeof(int) * dataSz);
        extraMemoryAllocated += sizeof(int) * dataSz; // Track memory allocation
        for (int i = 0; i < dataSz; ++i) {
            fscanf(inFile, "%d", &((*ppData)[i])); // Read each data element from the file
        }
        fclose(inFile); // Close the file after reading
    }

    return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}