#include <stdio.h>
#include <stdlib.h>		//for exit
#include <ctype.h>		//for isspace
#include <time.h>		//for time

#define MAXLEN 1000000
#define INTCMP(x,y) (((x)>(y))?1:(((x)==(y))?0:-1))
#define INTSWAP(x,y) {int t; t = (x); (x) = (y); (y) = t;}

int no_list[MAXLEN + 1];
int list_len = 0;
int item;

void GenRandom();
void GetNoList();
void InsertSort();
void PrintList();
int BinSearchIter();
int BinSearchRecur(int low, int high);
int SeqSearch();

int main() {
	clock_t start, stop;

	//둘 중 하나를 취사선택
	GenRandom();
	//GetNoList();

	InsertSort();
	//PrintList();
	
	start = clock();
	printf("BinSearchIter: %d\n", BinSearchIter());
	stop = clock();
	printf("%e elapsed\n\n", (double)(stop-start)/CLOCKS_PER_SEC);

	start = clock();
	printf("BinSearchRecur: %d\n", BinSearchRecur(0, list_len - 1));
	stop = clock();
	printf("%e elapsed\n\n", (double)(stop - start) / CLOCKS_PER_SEC);

	start = clock();
	printf("SeqSearch: %d\n", SeqSearch());
	stop = clock();
	printf("%e elapsed\n\n", (double)(stop - start) / CLOCKS_PER_SEC);

	return 0;
}

void GenRandom() {
	int len;
	int i;

	srand(time(NULL));

	len = 50000;

	for (i = 0; i < len; i++)
		no_list[i] = rand() % (len*10);

	list_len = len;

	item = rand() % (len * 10);
}

void GetNoList() {
	FILE *fp = fopen("input.txt", "r");
	int ch;			//Input Character
	int no = 0;		//Input Number
	int i = 0;		//Number of Input Nunber

	//exit if file open error
	if (!fp) {
		fprintf(stderr, "file open error\n");
		exit(100);
	}

	//get numbers
	printf("Input list of numbers.\n");
	while ((ch = getc(fp)) != '\n') {
		//if space and no to push then push
		if (isspace(ch) && no > 0 && list_len < MAXLEN){
			no_list[list_len] = no;
			list_len++;	no = 0;
		}
		//if not space add up
		else
			no = no * 10 + (ch - '0');
	}
	//push last number
	if (no > 0 && list_len < MAXLEN) {
		no_list[list_len] = no;
		list_len++;	no = 0;
	}

	item = getc(fp) - '0';
	fclose(fp);
}

void InsertSort() {
	int i, j;

	for (i = 1; i < list_len; i++) {
		for (j = i; no_list[j - 1] > no_list[j] && j > 0; j--)
			INTSWAP(no_list[j - 1], no_list[j]);
	}
}

void PrintList() {
	int i;

	for (i = 0; i < list_len; i++)
		printf("%d ", no_list[i]);
	putchar('\n');
}

int BinSearchIter() {
	int low, mid, high;

	low = 0;
	high = list_len - 1;

	while (low <= high) {	//종료 시점 맞나?
		mid = (low + high) / 2;

		switch(INTCMP(item, no_list[mid])) {
		case 1:		//item > mid number
			low = mid + 1;
		case 0:		//item == mid number
			return mid;
		case -1:	//item < mid number
			high = mid - 1;
		}
	}
	return -1;
}
int BinSearchRecur(int low, int high) {
	int mid = (low + high) / 2;

	if (low > high)
		return -1;

	switch (INTCMP(item, no_list[mid])) {
	case 1:		//item > mid number
		return BinSearchRecur(mid + 1, high);
	case 0:		//item == mid number
		return mid;
	case -1:	//item < mid number
		return BinSearchRecur(low, mid - 1);
	}
}

int SeqSearch() {
	int i;

	for (i = 0; i < list_len; i++)
		if (no_list[i] == item)
			return i;

	return -1;
}