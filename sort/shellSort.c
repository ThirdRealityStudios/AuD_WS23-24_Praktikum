// S. S. 138, Abb. 8.7.
// Distanzen:  3*h+1: …, 13, 4, 1
// Vergleich: Pos. 1 mit Pos. 14, Pos. 2 mit Pos. 15
// Vergleich: 1,5,9,13 und 2,6,10,14
// Letzter Durchlauf: normaler Insertion Sort, kein Element muss weit bewegt werden.

// 6.7: Shellsort

// S. S. 138, Abb. 8.7.
// Distanzen:  3*h+1: …, 13, 4, 1
// Vergleich: Pos. 1 mit Pos. 14, Pos. 2 mit Pos. 15
// Vergleich: 1,5,9,13 und 2,6,10,14
// Letzter Durchlauf: normaler Insertion Sort, kein Element muss weit bewegt werden.

void shellsort_sort (int a[], int N)
{
    int i, j, h, v;

    for (h = 1; h <= N/3; h = 3*h + 1) ;
    for ( ; h > 0; h /= 3)
        for (i = h + 1; i <= N; i++)
        {
            v = a[i]; j = i;
            while (j > h && a[j-h] > v)
            { a[j] = a[j-h]; j -= h;}
            a[j] = v;
        }
}
