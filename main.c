#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "test.h"
#include "utils.h"
#include "sort/heapSort.h"
#include "sort/insertionSort.h"
#include "sort/mergeSort.h"
#include "sort/quickSort.h"
#include "sort/selectionSort.h"
#include "sort/shellSort.h"

#define VALUES 200000 // Größe des zu erstellenden Arrays.

#define DEBUG 1 // Unit-Tests ausführen und Debug-Infos ausgeben = 1, ansonsten = 0

void (*sortFunc)(int[], int N);

clock_t sort(void (*algorithm)(int[], int N), int array[], int N)
{
    clock_t begin = clock();

    (*algorithm)(array, N);

    clock_t end = clock();

    return end - begin;
}

void sortMeasurePrint(void (*algorithm)(int array[], int N), void (*fillFunc)(int array[], int N),char *orderOfArrayValuesInfo)
{
    int *array = alloc(VALUES);
    fillFunc(array, VALUES);

    printf("-> %s: ", orderOfArrayValuesInfo);
    printf("%lu ms\n", sort(algorithm, array, VALUES));
    free(array);

    return;
}

void aufgabe(void (*algorithm)(int array[], int N), char *sortingAlgorithmName)
{
    printf("%s:\n", sortingAlgorithmName);
    sortMeasurePrint(algorithm, fillRandom, "random");
    sortMeasurePrint(algorithm, fillAscending, "ascending");
    sortMeasurePrint(algorithm, fillDescending, "descending");
    puts("");
}

int main()
{
    #if DEBUG // Alle wichtigen Units hier testen:
    testAlloc();
    testFillAscending();
    testFillDescending();
    testFillRandom();

    testHeapSort();
    testInsertionSort();
    testMergeSort();
    testQuickSort();
    testSelectionSort();
    testShellSort();
    #endif

    aufgabe(heapsort_sort, "Heap Sort");
    aufgabe(selectionsort_sort, "Selection Sort"); // OK
    aufgabe(mergesort_sort, "Merge Sort");
    aufgabe(insertionsort_sort, "Insertion Sort"); // OK
    aufgabe(shellsort_sort, "Shell Sort"); // OK
    // aufgabe(quicksort_sort, "Quick Sort");



    return EXIT_SUCCESS;
}