void insertionsort_sort(int a[], int N)
{
	int i, j, v;

	for(i = 1; i < N; i++)
    {
		v = a[i];
        j = i;

		while (a[j-1] > v && j > 0) // Bugfix für ungültigen Speicherzugriff von j (Fix durch && j > 0).
        {
            a[j] = a[j-1];
            j--;
        }

		a[j] = v;
	}
}