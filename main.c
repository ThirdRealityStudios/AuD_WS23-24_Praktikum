#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

struct Element
{
    int key;
    struct Element *next;
};

// Funktionsprototypen definieren,
// damit der Compiler nicht mehr meckert
// wegen der Aufrufreihenfolge der Funktionen.
int isempty(struct Element *first);
struct Element* linit();
void linsert(struct Element **first, int key);
int ldelete(struct Element **first, int key);
void printList(struct Element *first);

/**
  * Erzeugen einer leeren Liste.
  * Sie besteht nur aus dem Endelement.
  */
struct Element* linit()
{
    struct Element *emptyList = calloc(sizeof(struct Element), 1);
    // => key ist 0 und next ist NULL.

    return emptyList;
}

/**
  * Sortiertes Einfügen eines Elementes in die Liste.
  *
  * Hinweis:
  *
  * Der Doppelpointer bei linsert() und ldelete() wird benötigt,
  * wenn sich das erste Element ändern soll in der aufrufenden Funktion.
  * "**first" beschreibt also die lokale Variable der aufrufenden Funktion.
  */
void linsert(struct Element **first, int key)
{
    // Ich erhalte lediglich eine KOPIE der Adresse des ersten Elements.
    // Muss das erste Element getauscht werden,
    // dann ist diese Variable hier ZWECKLOS wegen Call-by-value!
    // Die Änderung dieser Referenz hier hat also keinen Einfluss auf die
    // main-Funktion!
    // Stattdessen muss dann der übergebene Doppelpointer dereferenziert werden!
    struct Element *firstStructPtr = *first;

    if(isempty(firstStructPtr))
    {
        firstStructPtr -> key = key;
        firstStructPtr -> next = firstStructPtr; // "first" zeigt bewusst auf sich selber (interpretiert dann als Listengröße = 1).

        return; // Beenden, da bereits fertig mit dem Einfügen.
    }

    // Andernfalls muss ein neuer Knoten erzeugt werden:
    struct Element *toInsert = calloc(1, sizeof(struct Element));
    toInsert -> key = key;

    int hasExactlyOneElement = firstStructPtr -> next == firstStructPtr;

    if(hasExactlyOneElement) // Genau 1 Element ist in der Liste und das ist "first" selber mit einem gesetzten Wert.
    {
        if(key > firstStructPtr -> key)
        {
            firstStructPtr -> next = toInsert;

            return;
        }

        // Ab hier ist key <= firstStructPtr -> key.

        firstStructPtr -> next = NULL; // Endlosreferenz "aufbrechen" => Liste hat nun mehr als 1 Element.
        toInsert -> next = firstStructPtr; // Schonmal das später (!) nach links eingeordnete Element auf den größeren Wert zeigen lassen.

        *first = toInsert; // Dies hier ist die eigentliche Tauschoperation,
                           // die dann aber auch Auswirkungen auf die
                           // "first"-Referenz bzw. -Variable in der
                           // main-Funktion hat (da ich hier den Doppelpointer verwende).

        return;
    }

    // Mindestens 2 Elemente existieren ab hier.
    struct Element *precedingElement = NULL;
    struct Element *currentElement = *first;

    while(currentElement != NULL)
    {
        if(key < currentElement -> key)
        {
            if(precedingElement == NULL)
            {
                toInsert -> next = currentElement;

                *first = toInsert;

                return; // Fertig. Vor dem ersten Element eingefügt.
            }

            // Der ab hier folgende Teil ist äquivalent zu: else if(key >= precedingElement -> key)

            precedingElement -> next = toInsert;
            toInsert -> next = currentElement;

            return;
        }

        precedingElement = currentElement;
        currentElement = currentElement -> next;
    }

    // Am Ende der Liste einfügen mit precedingElement, da man das Element ganz zu Anfang nicht als kleiner einordnen konnte..
    precedingElement -> next = toInsert;
}

/**
  * Entfernen des Elementes mit Schlüssel "key"
  * aus der Liste.
  * Ist ein Element mit "key" nicht enthalten,
  * wird -1 zurückgegeben,
  * ansonsten 1.
  * Aus dem Hauptprogramm soll natürlich eine
  * Meldung kommen.
  *
  *
  * Hinweis:
  *
  * Der Doppelpointer bei linsert() und ldelete() wird benötigt,
  * wenn sich das erste Element ändern soll in der aufrufenden Funktion.
  */
int ldelete(struct Element **first, int key)
{
    if(isempty(*first))
    {
        return -1;
    }

    // Hier prüfen, ob die Liste exakt und wirklich nur 1 Element besitzt.

    int hasExactlyOneElement = (*first) -> next == *first;

    if(hasExactlyOneElement)
    {
        if((*first) -> key == key)
        {
            (*first) -> next = NULL; // Die Liste ist jetzt leer (da kein Endloszeiger auf sich selber mehr).

            return 1; // Das Entfernen war erfolgreich.
        }

        return -1; // Der "key" war nicht identisch. Fehlerzustand.
    }

    // Ab hier wird folglich Code ausgeführt für eine Listengröße > 1 (!).

    struct Element *precedingElement = *first;
    struct Element *currentElement = precedingElement -> next;

    // Falls das erste Element von der Löschung betroffen ist, dann..
    if(precedingElement -> key == key)
    {
        puts("Nice");

        *first = precedingElement -> next;

        // Bugfix dafür, falls das neue nächste Element selber keine Referenz mehr
        // besitzt auf ein Folgeelement.
        // Dies wird dann nämlich irrtümlich als "Liste ist leer" verstanden,
        // wenn "first" dies tut.
        // Daher ist dieser Bugfix notwendig,
        // damit eben diese Interpretation nicht mehr eintrifft.
        // Stattdessen zeigt in so einem Fall "first" auf sich selber (wie gewohnt)
        // Folglich hat die Liste nur noch 1 Element, falls das if-Statement wahr ist.
        if((*first) -> next == NULL)
        {
            (*first) -> next = *first; // Endloszeiger in diesem Fall..
        }

        free(precedingElement);

        return 1;
    }

    // Ab hier sind alle Elemente nach dem ersten (!) vom möglichen Löschvorgang betroffen.
    while(currentElement != NULL)
    {
        if(currentElement -> key == key)
        {
            precedingElement -> next = currentElement -> next; // Hier könnte first auf NULL zeigen => "Liste ist leer" => Bugfix angewendet hiernach.

            if(precedingElement -> next == NULL && precedingElement == *first) // Bugfix
            {
                precedingElement -> next = precedingElement; // Jetzt richtiger Zustand "Liste hat genau 1 Element".
            }

            free(currentElement);

            return 1;
        }

        precedingElement = currentElement;
        currentElement = currentElement -> next;
    }

    return -1; // Fehlerzustand.
}

/**
  * Rückgabe von 1,
  * falls die Liste leer ist,
  * ansonsten 0.
  *
  * Genauer gesagt ist die Liste leer,
  * wenn das erste Element nicht auf sich selber zeigt (interpretiert hier als Listengröße = 1)
  * und wenn es nicht auf ein anderes Element zeigt (interpretiert als Listengröße mind. 2).
  */
int isempty(struct Element *first)
{
    return first -> next == NULL;
}

/**
  * Ausgabe der in der Liste gespeicherten Elemente.
  */
void printList(struct Element *first)
{
    if(isempty(first))
    {
        puts("Die Liste ist leer.");

        return;
    }

    while(1)
    {
        printf("%d", first -> key); // Element ausgeben.

        int hasNext = first -> next != NULL; // selbsterklärend.

        // Beschreibt den Zustand,
        // wenn die Liste genau 1 Element enthält und
        // der "first"-Zeiger deswegen auf sich selber zeigt.
        int hasInfiniteElements = first -> next == first;

        if(hasNext && !hasInfiniteElements) // Falls noch weitere (echte) Elemente, dann..
        {
            printf(" -> ");
        }
        else // Ansonsten wurde die Liste durchlaufen (beenden).
        {
            break;
        }

        first = first -> next; // Nächstes Element laden.
    }

    puts("");
}

/**
  * Hilfsmethode,
  * um den Menükontext ausgeben zu lassen (formatiert).
  */
void printMenue()
{
    puts("");
    puts("Menue zur Warteschlangenverwaltung:");
    puts("1. Sortiertes Einfuegen eines Elementes");
    puts("2. Loeschen und Ausgeben des Elementes mit Schluessel key");
    puts("3. Ausgeben der Liste");
    puts("4. Beenden des Programms");
    puts("");
    printf("Bitte geben Sie die Ziffer der gewünschten Funktion ein: ");
    // Eingabe-Möglichkeit hiernach durch Programmierer erwartet.
}

int main()
{
    int choice = -1;

    // Den Listenanfang definieren mit linit().
    struct Element *first = linit();

    do
    {
        printMenue();

        scanf("%d", &choice);

        puts("");

        switch(choice)
        {
            case 1:
            {
                // Sortiertes Einfuegen eines Elemenetes

                int value = 0;

                printf("Ihr Wert zum Einfügen: ");

                scanf("%d", &value);

                linsert(&first, value);
            }
            break;

            case 2:
            {
                // 2. Loeschen und Ausgeben des Elementes mit Schluessel key

                int value = 0;

                printf("Ihr Wert zum LÖschen: ");

                scanf("%d", &value);

                int success = ldelete(&first, value) == 1;

                puts(success ? "Wert gelöscht." : "Der existiert nicht!");
            }
            break;

            case 3:
            {
                // Ausgeben der Liste

                printList(first);
            }
            break;
        }
    }
    while(choice != 4);

    puts("Programm beendet.");

    return EXIT_SUCCESS;
}