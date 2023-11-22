// S. S. 138, Abb. 8.7.
// Distanzen:  3*h+1: …, 13, 4, 1
// Vergleich: Pos. 1 mit Pos. 14, Pos. 2 mit Pos. 15
// Vergleich: 1,5,9,13 und 2,6,10,14
// Letzter Durchlauf: normaler Insertion Sort, kein Element muss weit bewegt werden.

void shellsort_sort (int a[], int N) // a = {-13, 3, -12}, N = 3
{
	int i, j, h, v;

    /*
     * 1. (h = 0, wahr wegen 0 < 1, h = 1)
     * 2. (h = 1, falsch wegen 1 < 1, h = 4)
     */
	for (h = 0; h < N/3; h = 3*h + 1);

    /*
     * 1.1. (h = 4, wahr wegen 4 > 0, h = 1)
     * 2.1. (h = 1, wahr wegen 1 > 0, h = 0)
     */
	for ( ; h > 0; h /= 3)
    {
        /*
         * 1.1. (i = 5, 5 < 3, i = 3)
         * 2.1. (i = 2, 2 < 3, i = 3)
         */
        for (i = h + 1; i < N; i++)
        {
            /*
             * 2.1 (v = 3)
             */
            v = a[i]; // direkter Nachfolger von h.

            /*
             * 2.1 (j = 2)
             */
            j = i; // j zeigt anfangs noch auf den selben Wert wie v.

            /*
             * 2.1 (2 > 1 && a[1] > 3)
             */
            // h < j anfangs, also Vorgänger.
            // solange(j der Nachfolger von h && a[Nachfolger - Vorgänger] > direkter Nachfolger von h)
            while (j > h && a[j - h] > v)
            {
                printf("");

                // Nachfolger = Vorgänger
                a[j] = a[j - h];

                // Ziehe vom Nachfolger den Vorgänger ab.
                j -= h;
            }

            a[j] = v;
        }
    }
}