#include <stdio.h>
#include <stdlib.h>

int* naive_mult(int *a, int *b, int n, int m)
{
	int i = 0, j = 0;
	int *res = (int*)calloc(n + m, sizeof(int));
	for (i = n - 1; i >= 0; --i)
	{
		for (j = m - 1; j >= 0; --j)
		{
			res[i + j] += a[i] * b[j];
		}
	}
	return res;
}

int* better_mult(int *a, int *b, int n)
{
	int k = 0;
	int *res = NULL;
	int *res1, *res2, *res3;

	int *mid = NULL;
	int *a1 = NULL;
	int *a2 = NULL;
	int *b1 = NULL;
	int *b2 = NULL;
	int *a1a2 = NULL;
	int *b1b2 = NULL;

	int i = 0;
	if (n <= 16)
	{
		res = naive_mult(a, b, n, n);
		return res;
	}
	k = n / 2;
	res = (int*)calloc(2 * n, sizeof(int));

	mid = (int*)calloc(n, sizeof(int));
	a1 = (int*)calloc(k, sizeof(int));
	a2 = (int*)calloc(k, sizeof(int));
	b1 = (int*)calloc(k, sizeof(int));
	b2 = (int*)calloc(k, sizeof(int));
	a1a2 = (int*)calloc(k, sizeof(int));
	b1b2 = (int*)calloc(k, sizeof(int));

	res1 = res2 = res3 = NULL;

	for (i = 0; i < k; ++i)
	{
		a1[i] = a[i];
		a2[i] = a[k + i];
		b1[i] = b[i];
		b2[i] = b[k + i];
		a1a2[i] = a1[i] + a2[i];
		b1b2[i] = b1[i] + b2[i];
	}

	res1 = better_mult(a1, b1, k);
	res2 = better_mult(a2, b2, k);
	res3 = better_mult(a1a2, b1b2, k);

	free(a1);
	free(a2);
	free(b1);
	free(b2);
	free(a1a2);
	free(b1b2);

	for (i = 0; i < n; ++i)
	{
		mid[i] = res3[i] - (res2[i] + res1[i]);
	}

	free(res3);

	for (i = 0; i < n; ++i)
	{
		res[i] += res1[i];
		res[i + k] += mid[i];
		res[i + n] += res2[i];
	}

	free(mid);
	free(res1);
	free(res2);

	return res;
}

int main()
{
	int n = 0, m = 0, len = 0, bred = 0;
	int *a = NULL, *b = NULL, *res = NULL;
	int i = 0;

	scanf("%d %d", &n, &m);
	a = (int*)calloc(n, sizeof(int));
	b = (int*)calloc(m, sizeof(int));
	
	len = n + m;

	for (i = 0; i < n; ++i)
	{
		scanf("%d", &a[i]);		
	}

	for (i = 0; i < m; ++i)
	{
		scanf("%d", &b[i]);
	}

	res = better_mult(a, b, n);

	for (i = len - 1; i >= 0; --i)
	{
		if (res[i] != 0)
		{
			len = i + 1;
			break;
		}
	}

	for (i = 0; i < len; ++i)
	{
		printf("%d ", res[i]);
	}
	printf("\n");

	free(a);
	free(b);
	free(res);
}