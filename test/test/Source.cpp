#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void afis(int k, int *sol, char nume[][50], FILE *f)
{
	int i;
	for (i = 1; i <= k; i++)
	{
		fprintf(f, "%s ", nume[sol[i]]);
	}
	fprintf(f, "\n");
}

int valid(int k, int *sol, float inaltime[])
{
	int ok = 1, i;
	if (k == 1) return 1;
	for (i = 1; i<k; i++) if (sol[k] == sol[i]) { ok = 0; break; }
	if (ok == 1 && inaltime[sol[k]] < inaltime[sol[k - 1]]) ok = 0;
	return ok;
}

void BT(int n, int k, int *sol, char nume[][50], float* inaltime, FILE *f)
{
	int i;
	for (i = 1; i <= n; i++)
	{
		sol[k] = i;
		if (valid(k, sol, inaltime))
		{
			if (k == n) afis(k, sol, nume, f);
			else BT(n, k + 1, sol, nume, inaltime, f);
		}
	}
}

int main()
{
	int n, i, sol[50];
	char nume[50][50];
	float inaltime[50];
	FILE *f;
	f = fopen("sport.out", "w");
	printf("Numarul de elevi:");
	scanf("%d", &n);
	while (n > 10)
	{
		printf("Introdu o valoare mai mica decat 11:");
		scanf("%d", &n);
	}
	for (i = 1; i <= n; i++)
	{
		printf("Nume:");
		scanf("%s", nume[i]);
		printf("Inaltime:");
		scanf("%f", &inaltime[i]);
	}
	BT(n, 1, sol, nume, inaltime, f);
	fclose(f);
}