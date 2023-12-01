#include <stdio.h>
#include <stdlib.h>

int *b = NULL;

void mergesort_innerSort(int a[], int l, int r)
{
    int i, j, k, m;

    if (r > l)
    {
        m = (r + l)/2;

        mergesort_innerSort(a, l, m);
        mergesort_innerSort(a, m+1, r);

        // Elemente in das temporäre Array b kopieren
        for (i = m; i >= l; i--)
        {
            b[i] = a[i];
        }

        for (j = m+1; j <= r; j++)
        {
            b[r+m+1-j] = a[j];
        }

        // Die beiden Hälften zusammenführen
        i = l;
        j = r;

        for (k = l; k <= r; k++)
        {
            a[k] = (b[i] < b[j]) ? b[i++] : b[j--];
        }
    }
}

void mergesort_sort(int a[], int N)
{
    b = calloc(sizeof(int), N);

    mergesort_innerSort(a, 0, N-1);

    free(b);
}