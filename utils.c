/// @brief Die Funktionen der Praktikumsaufgabe.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "values.h"

/// @brief Erstellt ein leeres, alloziiertes Array der Größe VALUES.
/// @param length Anzahl der int-Werte.
/// @return Array der Größe VALUES.
int* alloc(int length)
{
    return calloc(length, sizeof(int));
}

/// @brief Kopiert ein Array der Länge VALUES.
/// @param array Das Array, das kopiert werden soll.
/// @param length Die Länge des Arrays.
/// @return Kopiertes Array vom Typ int.
int* copy(int *array, int length)
{
    return memcpy(alloc(length), array, length);
}

/// @brief Befüllt ein Array mit aufsteigenden Werten ab 1.
/// @param array Array, das mit aufsteigenden Werten befüllt werden soll.
/// @param length Länge des Arrays, das übergeben wird.
void fillAscending(int *array, int length)
{
    for(int i = 1; i <= length; i++)
    {
        array[i - 1] = i;
    }
}

/// @brief Befüllt ein Array mit Zufallswerten von 1 bis 200000.
/// @param array Array, das mit absteigenden Werten befüllt werden soll.
/// @param length Länge des Arrays, das übergeben wird.
void fillDescending(int *array, int length)
{
    for(int i = length; i > 0; i--)
        array[(i - length) * (-1)] = i;
    // z.B. bei VALUES = 3 gilt folgendes:
    // Für den Anfang ist i = 3 => array[(3 - 3) * (-1)] = 3;
    // Danach ist i = 2 => array[(2 - 3) * (-1)] = 2;
    // Und am Ende ist i = 1 => array[(1 - 3) * (-1)] = 1;
}

/// @brief Befüllt ein Array mit zufälligen Werten von 1 bis MAX_RAND_VALUE.
/// @param array Array, das befüllt werden soll.
/// @param length Länge des Arrays, das übergeben wird.
void fillRandom(int *array, int length)
{
    srand(time(NULL));

    for(int i = 0; i < length; i++)
    {
        float randRatio = rand() / (float) RAND_MAX;

        int rand = randRatio * MAX_RAND_VALUE + 1;

        array[i] = rand;
    }
}