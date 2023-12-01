#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "utils.h"
#include "test.h"
#include "sort/selectionSort.h"
#include "sort/insertionSort.h"
#include "sort/heapSort.h"
#include "sort/mergeSort.h"
#include "sort/quickSort.h"
#include "sort/shellSort.h"
#include "values.h"

#define BRIEF_DEBUG 0

#include "utils.h"
#include "test.h"

/// @brief Testet, ob ein gültiges leeres Array erzeugt wird der Größe VALUES.
void testAlloc()
{
    puts("testAlloc()");

    int *array = alloc(6); // Array der Größe VALUES erstellt.

    assert(array[0] == 0);
    assert(array[1] == 0);
    assert(array[2] == 0);
    assert(array[3] == 0);
    assert(array[4] == 0);
    assert(array[5] == 0);

    puts("OK");

    puts("");
}

/// @brief Testet, ob Werte korrekt aufsteigend gebildet werden in einem Array.
void testFillAscending()
{
    puts("testFillAscending()");

    int *array = alloc(6);

    fillAscending(array, 6);

    assert(array[0] == 1);
    assert(array[1] == 2);
    assert(array[2] == 3);
    assert(array[3] == 4);
    assert(array[4] == 5);
    assert(array[5] == 6);

    puts("OK");

    free(array);

    puts("");
}

/// @brief Testet die korrekte Zuweisung von absteigenden Werten für Arrays.
void testFillDescending()
{
    puts("testFillDescending()");

    int *array = alloc(6);

    fillDescending(array, 6);

    assert(array[0] == 6);
    assert(array[1] == 5);
    assert(array[2] == 4);
    assert(array[3] == 3);
    assert(array[4] == 2);
    assert(array[5] == 1);

    puts("OK");

    free(array);

    puts("");
}

/// @brief Testet, ob gültige Zufallswerte für ein Array generiert werden zwischen 1 und MAX_RAND_VALUE als Bedingung.
void testFillRandom()
{
    puts("testFillRandom()");

    int *array = alloc(6);

    fillRandom(array, 6);

    assert(array[0] > 0 && array[0] <= MAX_RAND_VALUE);
    assert(array[1] > 0 && array[1] <= MAX_RAND_VALUE);
    assert(array[2] > 0 && array[2] <= MAX_RAND_VALUE);
    assert(array[3] > 0 && array[3] <= MAX_RAND_VALUE);
    assert(array[4] > 0 && array[4] <= MAX_RAND_VALUE);
    assert(array[5] > 0 && array[4] <= MAX_RAND_VALUE);

    puts("OK");

    free(array);

    puts("");
}

/// @brief Testet den Heap-Sort auf Korrektheit.
void testHeapSort()
{
    puts("testHeapSort()");

    int *array = alloc(6);

    array[0] = 0; // Wird nicht benutzt werden von HeapSort, da HeapSort ab 1 indiziert.
    array[1] = 13;
    array[2] = 12;
    array[3] = -78;
    array[4] = 32;
    array[5] = INT_MIN;

    #if defined(BRIEF_DEBUG) && BRIEF_DEBUG
    for(int i = 0; i < VALUES; i++)
    {
        printf("%d ", array[i]);
    }
    #endif

    heapsort_sort(array, 6 - 1); // 1 abziehen, da Heap Sort ein Feld selber braucht zum Arbeiten.

    #if defined(BRIEF_DEBUG) && BRIEF_DEBUG
    puts("");

    for(int i = 0; i < VALUES; i++)
    {
        printf("%d ", array[i]);
    }

    puts("");
    #endif

    assert(array[0] == 0);
    assert(array[1] == INT_MIN);
    assert(array[2] == -78);
    assert(array[3] == 12);
    assert(array[4] == 13);
    assert(array[5] == 32);

    puts("OK");

    free(array);

    puts("");
}

/// @brief Test den Selection Sort auf die korrekte Funktionalität.
void testSelectionSort()
{
    puts("testSelectionSort()");

    int *array = alloc(6);

    array[0] = 0;
    array[1] = 13;
    array[2] = 12;
    array[3] = -78;
    array[4] = 32;
    array[5] = INT_MIN;

    selectionsort_sort(array, 6);

    assert(array[0] == INT_MIN);
    assert(array[1] == -78);
    assert(array[2] == 0);
    assert(array[3] == 12);
    assert(array[4] == 13);
    assert(array[5] == 32);

    puts("OK");

    free(array);

    puts("");
}

/// @brief Testet die Funktionalität von InsertionSort.
void testInsertionSort()
{
    puts("testInsertionSort()");

    int *array = alloc(6);

    array[0] = 0;
    array[1] = 13;
    array[2] = 12;
    array[3] = -78;
    array[4] = 32;
    array[5] = INT_MIN;

    insertionsort_sort(array, 6);

    assert(array[0] == INT_MIN);
    assert(array[1] == -78);
    assert(array[2] == 0);
    assert(array[3] == 12);
    assert(array[4] == 13);
    assert(array[5] == 32);

    puts("OK");

    free(array);

    puts("");
}

/// @brief Testet die Funktionalität von MergeSort.
void testMergeSort()
{
    puts("testMergeSort()");

    int *array = alloc(6);

    array[0] = 0;
    array[1] = 13;
    array[2] = 12;
    array[3] = -78;
    array[4] = 32;
    array[5] = INT_MIN;

    mergesort_sort(array, 6);

    assert(array[0] == INT_MIN);
    assert(array[1] == -78);
    assert(array[2] == 0);
    assert(array[3] == 12);
    assert(array[4] == 13);
    assert(array[5] == 32);

    puts("OK");

    free(array);

    puts("");
}

/// @brief Testet die Funktionalität von QuickSort.
void testQuickSort()
{
    puts("testQuickSort()");

    int *array = alloc(6);

    array[0] = 0;
    array[1] = 13;
    array[2] = 12;
    array[3] = -78;
    array[4] = 32;
    array[5] = INT_MIN;

    quicksort_sort(array, 6);

    assert(array[0] == INT_MIN);
    assert(array[1] == -78);
    assert(array[2] == 0);
    assert(array[3] == 12);
    assert(array[4] == 13);
    assert(array[5] == 32);

    puts("OK");

    free(array);

    puts("");
}

/// @brief Gibt ein Array aus der Länge N.
void printArray(int *array, int N)
{
    for(int i = 0; i < N; i++)
    {
        printf("%d ", array[i]);
    }

    puts("");
}

/// @brief Testet die Funktionalität von ShellSort.
/// @todo evtl. Shell Sort mit Null-indizieren.
void testShellSort()
{
    puts("testShellSort()");

    int *array = alloc(6);

    array[0] = 0;
    array[1] = 13;
    array[2] = 12;
    array[3] = -78;
    array[4] = 32;
    array[5] = INT_MIN;

    #if defined(BRIEF_DEBUG) && BRIEF_DEBUG
    printArray(array, VALUES);
    #endif

    shellsort_sort(array, 6 - 1);

    #if defined(BRIEF_DEBUG) && BRIEF_DEBUG
    printArray(array, VALUES);
    #endif

    assert(array[0] == 0);
    assert(array[1] == INT_MIN);
    assert(array[2] == -78);
    assert(array[3] == 12);
    assert(array[4] == 13);
    assert(array[5] == 32);

    puts("OK");

    free(array);

    puts("");
}