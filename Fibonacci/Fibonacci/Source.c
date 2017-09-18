#include <stdio.h>

#define N 10

void FibSeqIter();
long double FibSeqRecur(int i);
void PrintSeq();

long double seq[N + 1];

int main() {
	FibSeqIter();
	PrintSeq();
	printf("%dth element is %.0lf\n", N, FibSeqRecur(N));
}

void FibSeqIter() {
	int i;

	seq[0] = 0;
	if (N > 0) {
		seq[1] = 1;
		for (i = 2; i <= N; i++)
			seq[i] = seq[i - 1] + seq[i - 2];
	}
}

long double FibSeqRecur(int i) {
	if (i == 0) return 0;
	if (i == 1)	return 1;
	return FibSeqRecur(i - 1) + FibSeqRecur(i - 2);
}

void PrintSeq() {
	int i;

	for (i = 0; i <= N; i++)
		printf("%.0lf ", seq[i]);
	putchar('\n');
}