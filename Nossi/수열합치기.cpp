#include <iostream>
#include <stdio.h>
#define NULL 0
using namespace std;

void init();
void mergenums(int n, int * arr);
int findkth(int kth);

int main()
{
//	freopen("input.txt", "r", stdin);

	int totalscore = 0;
	int score = 100;
	int fail;
	int inputnums[1000];

	int TC;
	cin >> TC;
	for (int tc = 1; tc <= TC; tc++)
	{
		fail = 0;

		init();

		int tcnt;
		cin >> tcnt;
		for (int j = 0; j < tcnt; j++)
		{
			char op;
			cin >> op;
			switch (op)
			{
			case 'M':
				int numscnt;
				cin >> numscnt;
				for (int k = 0; k < numscnt; k++)
				{
					cin >> inputnums[k];
				}
				mergenums(numscnt, inputnums);
				break;

			case 'K':
				int kth, tans;
				cin >> kth >> tans;
				if (findkth(kth) != tans)
					fail = 1;
				break;
			}
		}
		if (fail) printf("#%d 0\n", tc);
		else
		{
			printf("#%d 100\n", tc);
			totalscore += score;
		}
	}
	printf("Total Score = %d\n", totalscore / TC);
	return 0;
}



typedef struct node{
	int num;
	struct node *prev;
	struct node *next;
}Node;

class linked_list
{
private:
	Node *head, *cur, *tail;
	bool existBiggerNum;
public:
	linked_list()
	{
		head = NULL;
		cur = NULL;
		tail = NULL;

	}

	void add(int n)
	{
		Node *tmp = new Node;		// 이것들 delete해줘야되나?? 
		Node *prevTmp;
		tmp->num = n;
		tmp->prev = NULL;
		tmp->next = NULL;

		if (head == NULL)
		{
			head = tmp;
			tail = tmp;
		}else if (existBiggerNum) {
			if (cur == head)
			{
				head = tmp;
				head->next = cur;
				cur->prev = head;
			}
			else {
				prevTmp = cur->prev;
				prevTmp->next = tmp;
				tmp->prev = prevTmp;
				tmp->next = cur;
				cur->prev = tmp;
			}
			
		}
		else
		{
			tail->next = tmp;
			tmp->prev = tail;
			tail = tail->next;
		}

	}
	void findBiggerNum(int n) {
		cur = head;
		while (cur != NULL) {
			if (cur->num > n) {
				existBiggerNum = true;
				return;
			}
			else {
				cur = cur->next;
			}
		}
		existBiggerNum = false;
		return;
	}
	int findkth(int k) {
		if (k > 0) {
			cur = head;
			for (int i = 1; i < k; i++) {
				cur = cur->next;
			}
		}
		else if (k < 0) {
			cur = tail;
			for (int i = -1; i > k; i--) {
				cur = cur->prev;
			}
		}
		else throw("err");
		return cur->num;
	}
	void clear() {
		Node *tmp;
		while (head != NULL) {
			tmp = head;
			head = head->next;
			delete tmp;
		}
		tail = NULL;
		cur = NULL;
	}
};

linked_list full_list;
void init() {
	full_list.clear();
}

void mergenums(int n, int * arr) {

	for (int i = 0; i < n; i++) {
		if (i == 0) full_list.findBiggerNum(arr[i]);
		full_list.add(arr[i]);
	}
	//더 큰 숫자가 있는지 서칭한다.

}
int findkth(int kth) {
	return full_list.findkth(kth);

}
