#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#define VALUES 3 // Größe des zu erstellenden Arrays.
#define MAX_RAND_VALUE 200000 // Maximal generierter Zufallswert.

#define DEBUG 1 // Unit-Tests ausführen und Debug-Infos ausgeben = 1, ansonsten = 0

#if DEBUG
        #undef VALUES
        #define VALUES 5 // Nur noch 5 Werte im Testmodus.

        #undef MAX_RAND_VALUE
        #define MAX_RAND_VALUE 3 // wird zwischen 1 und 3 liegen.
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

    assert(array[0] == 5);
    assert(array[1] == 4);
    assert(array[2] == 3);
    assert(array[3] == 2);
    assert(array[4] == 1);

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

    puts("OK");

    free(array);

    puts("");
}
#endif

int main()
{
    #if DEBUG
    testAlloc();
    testFillAscending();
    testFillDescending();
    testFillRandom();
    #endif

    return EXIT_SUCCESS;
}