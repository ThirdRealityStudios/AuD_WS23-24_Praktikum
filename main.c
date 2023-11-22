#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "test.h"
#include "sort/heapSort.h"
#include "sort/insertionSort.h"
#include "sort/mergeSort.h"
#include "sort/quickSort.h"
#include "sort/selectionSort.h"
#include "sort/shellSort.h"

#define VALUES 200000 // Größe des zu erstellenden Arrays.

#define DEBUG 1 // Unit-Tests ausführen und Debug-Infos ausgeben = 1, ansonsten = 0

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

    return EXIT_SUCCESS;
}