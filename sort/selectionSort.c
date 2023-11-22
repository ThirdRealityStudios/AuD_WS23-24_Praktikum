void selectionsort_sort (int a[], int N)
{
	int i, j, min, t;

    /*
     * Bugfix für die äußere Schleifenbedingung:
     *
     * es gilt "i < (N - 1)" statt "i < N",
     * da ich Arrays ab 0 indizieren möchte.
     */
	for (i = 0; i < (N - 1); i++)
	{
		min = i;

        /*
         * Bugfix für die innere Schleifenbedingung:
         *
         * es gilt "j < N" statt "j <= N",
         * da bei mir die Arrays ab 0 verwendet werden und nicht ab 1.
         */
		for (j = i + 1; j < N; j++)
			if (a[j] < a[min]) min = j;
		t = a[min]; a[min] = a[i]; a[i] = t;
	}
}