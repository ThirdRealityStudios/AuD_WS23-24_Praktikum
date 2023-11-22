#include <stdio.h>
#include <limits.h>

#define MAXN	100

static int a[MAXN+1], N;

void heapsort_upheap (int k)
{
	int v;

	v = a[k]; a[0] = INT_MAX;
	while (a[k/2] <= v)
	{ a[k] = a[k/2]; k = k/2; }
	a[k] = v;
}

void heapsort_insert (int v)
{ 
	a[++N] = v;
	heapsort_upheap (N);
}

void heapsort_downheap (int k)
{
	int j, v;

	v = a[k];
    while (k <= N/2)
	{ 
		j = k+k;
		if (j < N && a[j] < a[j+1]) j++;
		if (v >= a[j]) break;
		a[k] = a[j]; k = j; 
	}
	a[k] = v;
}

int heapsort_remove ()
{
	int v = a[1];

	a[1] = a[N--];
	heapsort_downheap (1);
	return v;
}

void heapsort_sort (int a[], int laenge)
{
	int k;

	for (k = 1; k <= laenge; k++) heapsort_insert (a[k]);
	for (k = laenge; k >= 1; k--) a[k] = heapsort_remove();
}