#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int *b = NULL, N = 0;

void heapsort_upheap (int k)
{
    int v;

    v = b[k];
    b[0] = INT_MAX;

    while (b[k/2] <= v)
    {
        b[k] = b[k/2];
        k = k/2;
    }

    b[k] = v;
}

void heapsort_insert (int v)
{
    b[++N] = v;
    heapsort_upheap (N);
}

void heapsort_downheap (int k)
{
    int j, v;

    v = b[k];

    while (k <= N/2)
    {
        j = k+k;

        if (j < N && b[j] < b[j+1])
            j++;

        if (v >= b[j])
            break;

        b[k] = b[j];
        k = j;
    }

    b[k] = v;
}

int heapsort_remove()
{
    int v = b[1];

    b[1] = b[N--];
    heapsort_downheap (1);

    return v;
}

void heapsort_sort (int a[], int laenge)
{
    b = calloc(laenge + 1, sizeof(int));

    int k;

    for (k = 1; k <= laenge; k++)
        heapsort_insert (a[k]);

    for (k = laenge; k >= 1; k--)
        a[k] = heapsort_remove();

    free(b);
}