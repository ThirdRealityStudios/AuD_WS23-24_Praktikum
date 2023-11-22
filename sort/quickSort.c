void swap(int array[], int i, int j)
{
    int copy = array[j];

    array[j] = array[i];

    array[i] = copy;
}

int quicksort_partition (int array[], int l, int r)
{
    int i = l;

    // Starte mit j links vom Pivotelement
    int j = r - 1;
    int pivot = array[r];

    while(i < j) // solange i an j nicht vorbeigelaufen ist
    {
         // Suche von links ein Element, welches größer als das Pivotelement ist
         while(i < j && array[i] <= pivot)
             i++;

         // Suche von rechts ein Element, welches kleiner oder gleich dem Pivotelement ist
         while(j > i && array[j] > pivot)
             j--;

         if(array[i] > array[j])
         {
             swap(array, i, j);
         }
    }

    // Tausche Pivotelement (daten[rechts]) mit neuer endgültiger Position (daten[i])
    // und gib die neue Position des Pivotelements zurück, beende Durchlauf
    if(array[i] > pivot)
    {
        swap(array, i, r);
    }
    else
    {
        i = r;
    }

    return i;
}

void quicksort_sort (int a[], int l, int r)
{
	int i;

	if (r > l)
	{
		i = quicksort_partition (a, l, r); // TODO implementieren.
        quicksort_sort (a, l, i-1);
        quicksort_sort (a, i+1, r);
	}
}