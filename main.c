#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

const int size = 8;
int **spielfeld = NULL;

/*
 * Initialisiert das Spielfeld mit Nullen.
 */
void initSpielfeld()
{
    spielfeld = calloc(sizeof(int**), size);

    for(int i = 0; i < size; i++)
    {
        spielfeld[i] = calloc(sizeof(int*), size);
    }
}

/**
 * Druckt das Spielfeld auf der Konsole aus.
 */
void printSpielfeld()
{
    for(int y = 0; y < size; y++)
    {
        for(int x = 0; x < size; x++)
        {
            printf("%d  ", spielfeld[y][x]);
        }

        puts("");
    }
}

int main()
{
    initSpielfeld();
    printSpielfeld();

    puts("");

    puts("Programm beendet.");

    return EXIT_SUCCESS;
}