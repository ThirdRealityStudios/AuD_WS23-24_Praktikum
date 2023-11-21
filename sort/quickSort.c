void quicksort (int a[], int l, int r)
{
	int i;

	if (r > l)
	{
		i = partition (l, r); // TODO implementieren.
		quicksort (a, l, i-1);
		quicksort (a, i+1, r);
	}
}

int partition (int l, int r)
{
    // TODO implementieren

    /* Pseudocode für partition() aus Wikipedia:

 funktion teile(links, rechts)
     i:= links
     // Starte mit j links vom Pivotelement
     j:= rechts - 1
     pivot:= daten[rechts]

     wiederhole solange i < j // solange i an j nicht vorbeigelaufen ist
         // Suche von links ein Element, welches größer als das Pivotelement ist
         wiederhole solange i < j und daten[i] <= pivot
             i:= i + 1
         ende

         // Suche von rechts ein Element, welches kleiner oder gleich dem Pivotelement ist
         wiederhole solange j > i und daten[j] > pivot
             j:= j - 1
         ende

         falls daten[i] > daten[j] dann
             tausche daten[i] mit daten[j]
         ende
     ende

        // Tausche Pivotelement (daten[rechts]) mit neuer endgültiger Position (daten[i])
        // und gib die neue Position des Pivotelements zurück, beende Durchlauf
        falls daten[i] > pivot dann
            tausche daten[i] mit daten[rechts]
        sonst
            i:= rechts
        ende
        antworte i
    ende

    */

   return 0;
}