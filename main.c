#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "sort/heapSort.h"
#include "sort/insertionSort.h"
#include "sort/mergeSort.h"
#include "sort/quickSort.h"
#include "sort/selectionSort.h"
#include "sort/shellSort.h"

#define VALUES 200000 // Größe des zu erstellenden Arrays.
#define MAX_RAND_VALUE 200000 // Maximal generierter Zufallswert.

#define DEBUG 1 // Unit-Tests ausführen und Debug-Infos ausgeben = 1, ansonsten = 0
#define BRIEF_DEBUG 1 // 1 => alle Einzelheiten ausgeben, falls DEBUG erlaubt ist. Bei 0 normal ausgeben.

#if DEBUG
        #undef VALUES
        #define VALUES 6 // Nur noch 6 Werte im Unit-Testmodus statt die Zahl für den Normalfall.

        #undef MAX_RAND_VALUE
        #define MAX_RAND_VALUE 3 // Zufallswerte im Unit-Testmodus liegen zwischen 1 und 3.
#endif

/// @brief Erstellt ein leeres, alloziiertes Array der Größe VALUES.
/// @return Array der Größe VALUES.
int* alloc()
{
    return calloc(VALUES, sizeof(int));
}

/// @brief Kopiert ein Array der Länge VALUES.
/// @param array Das Array, das kopiert werden soll.
/// @return Kopiertes Array vom Typ int.
int* copy(int *array)
{
    return memcpy(alloc(), array, VALUES);
}

/// @brief Befüllt ein Array mit aufsteigenden Werten ab 1.
/// @param array Array, das mit aufsteigenden Werten befüllt werden soll.
void fillAscending(int *array)
{
    for(int i = 1; i <= VALUES; i++)
    {
        array[i - 1] = i;
    }
}

/// @brief Befüllt ein Array mit Zufallswerten von 1 bis 200000.
/// @param array Array, das mit absteigenden Werten befüllt werden soll.
void fillDescending(int *array)
{
    for(int i = VALUES; i > 0; i--)
        array[(i - VALUES) * (-1)] = i;
        // z.B. bei VALUES = 3 gilt folgendes:
        // Für den Anfang ist i = 3 => array[(3 - 3) * (-1)] = 3;
        // Danach ist i = 2 => array[(2 - 3) * (-1)] = 2;
        // Und am Ende ist i = 1 => array[(1 - 3) * (-1)] = 1;
}

/// @brief Befüllt ein Array mit zufälligen Werten von 1 bis MAX_RAND_VALUE.
/// @param array Array, das befüllt werden soll.
void fillRandom(int *array)
{
    srand(time(NULL));

    for(int i = 0; i < VALUES; i++)
    {
        float randRatio = rand() / (float) RAND_MAX;

        int rand = randRatio * MAX_RAND_VALUE + 1;

        array[i] = rand;
    }
}

#if DEBUG
/// @brief Testet, ob ein gültiges leeres Array erzeugt wird der Größe VALUES.
void testAlloc()
{
    puts("testAlloc()");

    int *array = alloc(); // Array der Größe VALUES erstellt.

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

    int *array = alloc();

    fillAscending(array);

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

    int *array = alloc();

    fillDescending(array);

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

    int *array = alloc();

    fillRandom(array);

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

    int *array = alloc();

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

    heapsort_sort(array, VALUES - 1); // 1 abziehen, da Heap Sort ein Feld selber braucht zum Arbeiten.

    #if defined(DEBUG) && DEBUG
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

    int *array = alloc();

    array[0] = 0;
    array[1] = 13;
    array[2] = 12;
    array[3] = -78;
    array[4] = 32;
    array[5] = INT_MIN;

    selectionsort_sort(array, VALUES);

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

    int *array = alloc();

    array[0] = 0;
    array[1] = 13;
    array[2] = 12;
    array[3] = -78;
    array[4] = 32;
    array[5] = INT_MIN;

    insertionsort_sort(array, VALUES);

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

    int *array = alloc();

    array[0] = 0;
    array[1] = 13;
    array[2] = 12;
    array[3] = -78;
    array[4] = 32;
    array[5] = INT_MIN;

    mergesort_sort(array, 0, VALUES - 1);

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

    int *array = alloc();

    array[0] = 0;
    array[1] = 13;
    array[2] = 12;
    array[3] = -78;
    array[4] = 32;
    array[5] = INT_MIN;

    quicksort_sort(array, 0, VALUES - 1);

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

/// @brief Testet die Funktionalität von ShellSort.
void testShellSort()
{
    puts("testShellSort()");

    int *array = alloc();

    array[0] = 0;
    array[1] = 13;
    array[2] = 12;
    array[3] = -78;
    array[4] = 32;
    array[5] = INT_MIN;

    shellsort_sort(array, VALUES - 1);

    assert(array[0] == 0); // array[0] unverändert, da nicht verwendet.
    assert(array[1] == INT_MIN);
    assert(array[2] == -78);
    assert(array[3] == 12);
    assert(array[4] == 13);
    assert(array[5] == 32);

    puts("OK");

    free(array);

    puts("");
}

#endif

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
    // TODO testQuickSort();
    testSelectionSort();
    testShellSort();
    #endif

    return EXIT_SUCCESS;
}