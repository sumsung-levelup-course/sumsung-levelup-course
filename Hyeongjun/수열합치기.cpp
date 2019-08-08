#include <malloc.h>
//#include <cstdio>

const int MAX_N=1010;
const int MAX_M=1010;
const int MAX_SEQ = MAX_M * MAX_M + 2;
const int HEAD = 0;
const int TAIL = MAX_SEQ - 1;
const int INF = 2000000001;
const int NOT = -1;

struct node {
	int value;
	int prev;
	int next;
};

node seq[MAX_SEQ];
int list_idx;

//void print_list() {
//	printf("===========Print List=======\n");
//	int idx = seq[HEAD].next;
//	while (idx != TAIL) {
//		printf("%d ", seq[idx].value);
//		idx = seq[idx].next;
//	}
//	printf("\n");
//}

int create_list(int n, int* arr) {
	int ret = list_idx;

	if (n == 1) {
		seq[list_idx].value = arr[0];
		seq[list_idx].prev = NOT;
		seq[list_idx].next = NOT;
		list_idx += 1;
		return ret;
	}

	seq[list_idx].value = arr[0];
	seq[list_idx].prev = NOT;
	seq[list_idx].next = list_idx + 1;
	list_idx += 1;
	for (int i = 1; i < n-1; i++) {
		seq[list_idx].value = arr[i];
		seq[list_idx].prev = list_idx - 1;
		seq[list_idx].next = list_idx + 1;
		list_idx += 1;
	}
	seq[list_idx].value = arr[n-1];
	seq[list_idx].prev = list_idx - 1;
	seq[list_idx].next = NOT;
	list_idx += 1;

	return ret;
}

void merge(int idx) {
	int cur = HEAD;
	int finish = TAIL;

	while (seq[cur].value <= seq[idx].value) {
		cur = seq[cur].next;
	}

	int prev = seq[cur].prev;

	seq[prev].next = idx;
	seq[idx].prev = prev;
	seq[cur].prev = list_idx - 1;
	seq[list_idx - 1].next = cur;
}

void init()
{
	seq[HEAD].value = 0;
	seq[HEAD].prev = NOT;
	seq[HEAD].next = TAIL;
	seq[TAIL].value = INF;
	seq[TAIL].prev = HEAD;
	seq[TAIL].next = NOT;
	list_idx = 1;
}

void mergenums(int n, int * arr)
{
	int first_idx = create_list(n, arr);

	merge(first_idx);

	//print_list();
}

int findkth(int kth)
{
	int ret = 0;


	if (kth > 0) {
		int idx = seq[HEAD].next;
		while (kth>1) {
			idx = seq[idx].next;
			kth -= 1;
		}
		ret = seq[idx].value;
	}
	else {
		int idx = seq[TAIL].prev;
		while (kth < -1) {
			idx = seq[idx].prev;
			kth += 1;
		}
		ret = seq[idx].value;
	}

	//printf("ret:%d\n", ret);

	return ret;
}
