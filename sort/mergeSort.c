#define MAX 100

int b[MAX+1];

void mergesort_sort (int a[], int l, int r)
{
	int i, j, k, m;

	if (r > l)
	{
		m = (r + l)/2;
        mergesort_sort (a, l, m);
        mergesort_sort (a, m+1, r);
		for (i = m+1; i > l; i--) b[i-1] = a[i-1];
		for (j = m; j < r; j++) b[r+m-j] = a[j+1];
		for (k = l; k <= r; k++)
			a[k] = (b[i] < b[j])? b[i++] : b[j--];
	}
}