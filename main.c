#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>

// #define DEBUG

const int size = 8;
int **spielfeld = NULL;

int xAnfang = 0, yAnfang = 7;

int springer(int zeile, int spalte, int num);

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

// Pausiert die Programmausführung um x Sekunden.
void pause(double seconds)
{
    double start = clock() / CLOCKS_PER_SEC;
    double end = start + seconds;

    while((clock() / CLOCKS_PER_SEC) <= end);
}

/*
 * Freet alle Instanzen vom Spielfeld.
 */
void freeSpielfeld()
{
    for(int i = 0; i < size; i++)
    {
        free(&spielfeld[i]);
    }

    free(spielfeld);
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
            printf("%c  ", spielfeld[y][x] == 1 ? '1' : ' ');
        }

        puts("");
    }
}

// Kann ich dahin springen? Oder ist das außerhalb des Spielfeldes?
// Wenn innerhalb, dann return 1, ansonsten 0 für außerhalb.
int isValidLocation(int zeile, int spalte)
{
    return zeile >= 0 && zeile < size && spalte >= 0 && spalte < size;
}

// Versucht, an die angegebene Stelle hinzuspringen, kann aber auch versagen,
// falls die Position bereits besucht wurde, diese außerhalb des Spielfeldes ist
// oder es keine Möglichkeit gab,
// alle Felder einmal zu besuchen.
// Bei Versagen wird 0 zurückgegeben,
// ansonsten 1.
int tryJump(int targetZeile, int targetSpalte, int num)
{
    int sprungErfolgreich = 0;

    // Kann ich zur Location springen UND bin ich da noch nicht gewesen?
    if(isValidLocation(targetZeile, targetSpalte) && spielfeld[targetZeile][targetSpalte] == 0)
    {
        spielfeld[targetZeile][targetSpalte] = 1; // Jetzt reserviere ich mir die Stelle..

        #ifdef DEBUG
        printSpielfeld();
        puts("---");
        pause(3);
        #endif

        sprungErfolgreich = springer(targetZeile, targetSpalte, num + 1); // Jetzt springe ich dort hin..

        if(!sprungErfolgreich)
        {
            spielfeld[targetZeile][targetSpalte] = 0; // Backtracking, Änderungen rückgängig machen.

            #ifdef DEBUG
            printSpielfeld();
            puts("---");
            pause(3);
            #endif
        }

        return sprungErfolgreich;
    }

    return 0;
}

int springer(int zeile, int spalte, int num)
{
    // Alle möglichen Springerbewegungen hier:
    int rightUpZeile = zeile - 1,
        rightUpSpalte = spalte + 2;

    int rightDownZeile = zeile + 1,
        rightDownSpalte = spalte + 2;

    int leftUpZeile = zeile - 1,
        leftUpSpalte = spalte - 2;

    int leftDownZeile = zeile + 1,
        leftDownSpalte = spalte - 2;

    int topLeftZeile = zeile - 2,
        topLeftSpalte = spalte - 1;

    int topRightZeile = zeile - 2,
        topRightSpalte = spalte + 1;

    int bottomLeftZeile = zeile + 2,
        bottomLeftSpalte = spalte - 1;

    int bottomRightZeile = zeile + 2,
        bottomRightSpalte = spalte + 1;

    int sprungErfolgreich = 0;

    // Ich befinde mich noch in der Anfangsposition.
    if(num == 1)
    {
        // Die Anfangsposition soll standardmäßig immer schon besucht worden sein.
        spielfeld[zeile][spalte] = 1;
    }

    // Bin ich schon alle Felder durchlaufen?
    if(num == size*size)
    {
        return 1; // Alle Felder erfolgreich probiert => finale Lösung gefunden.
    }

    sprungErfolgreich = tryJump(topLeftZeile, topLeftSpalte, num);

    if(!sprungErfolgreich)
        sprungErfolgreich = tryJump(topRightZeile, topRightSpalte, num);

    if(!sprungErfolgreich)
        sprungErfolgreich = tryJump(rightUpZeile, rightUpSpalte, num);

    if(!sprungErfolgreich)
        sprungErfolgreich = tryJump(rightDownZeile, rightDownSpalte, num);

    if(!sprungErfolgreich)
        sprungErfolgreich = tryJump(leftUpZeile, leftUpSpalte, num);

    if(!sprungErfolgreich)
        sprungErfolgreich = tryJump(leftDownZeile, leftDownSpalte, num);

    if(!sprungErfolgreich)
        sprungErfolgreich = tryJump(bottomLeftZeile, bottomLeftSpalte, num);

    if(!sprungErfolgreich)
        sprungErfolgreich = tryJump(bottomRightZeile, bottomRightSpalte, num);

    return sprungErfolgreich;
}

int main()
{
    int loesungGefunden = 0;

    initSpielfeld();

    puts("Anfangsbelegung:");
    puts("");

    printSpielfeld();

    loesungGefunden = springer(yAnfang, xAnfang, 1);

    puts("");

    if(loesungGefunden)
        puts("Lösung gefunden!");
    else
        puts("Keine Lösung gefunden.");

    puts("");

    printSpielfeld();

    puts("");

    freeSpielfeld(); // Speicher wieder freigeben.

    puts("Programm beendet.");

    return EXIT_SUCCESS;
}