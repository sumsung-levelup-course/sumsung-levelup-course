#include <stdio.h>
using namespace std;

#define MAX_N 1010

struct mystruc {
	char ch;
	int index;
};
int top;
mystruc stack[MAX_N];

void stackInit(void)
{
	top = 0;
}

mystruc getTop()
{
	return stack[top - 1];
}

int stackIsEmpty(void)
{
	return (top == 0);
}

int stackIsFull(void)
{
	return (top == MAX_N);
}

int stackPush(mystruc value)
{
	if (stackIsFull())
	{
		return 0;
	}
	stack[top] = value;
	top++;

	return 1;
}

int stackPop(mystruc *value)
{
	if (top == 0)
	{
		return 0;
	}
	top--;
	*value = stack[top];

	return 1;
}
bool isall()
{
	char c = stack[0].ch;
	for (int i = 0; i < top; i++)
	{
		if (stack[i].ch != c) return false;
	}
	return true;
}
void init()
{
	top = 0;
}
void swap(int* a, int* b)
{
	int tmp = *a;
	*a =*b;
	*b = tmp;
}
int findDelim()
{
	int ch = stack[0].ch;
	for (int i = 0; i < top; i++)
	{
		if (stack[i].ch != ch)
		{
			int ret = stack[i - 1].index;
			for (int j = 0; j <= (i - 1)/2; j++)
			{	
				int tmp = stack[j].index;
				stack[j].index = ret - stack[i-1-j].index;
				stack[i - 1 - j].index = ret - tmp;
				//swap(&stack[j].index, &stack[i - 1-j].index);
			}
			return ret;
		}
	}
	return 0;
}
int main()
{
	int tc;
	scanf("%d", &tc);
	for (int t = 1; t <= tc; t++)
	{
		init();
		int ans = 0;
		int L;
		scanf("%d", &L);
		char ch;
		for (int i = 0; i < L; i++)
		{
			scanf(" %c", &ch);
			if (stackIsEmpty()) stackPush({ ch,i });
			else if (ch == ')')
			{
				mystruc pp;
				if (getTop().ch == '(') stackPop(&pp);
				else
					stackPush({ ch,i });
			}
			else
			{
				stackPush({ ch,i });
			}
		}
		if (top % 2 == 1) ans = -1;
		else if (top == 0) ans = 0;
		else if (isall()) ans = 1;
		else ans = 2;
		printf("#%d %d\n", t, ans);
		if (ans == 1)
		{
			int delim = stack[top / 2 - 1].index;
			if (stack[0].ch == ')')
			{
				printf("%d %d\n", 0, delim);
			}
			else
				printf("%d %d\n", delim+1, L - 1);

		}
		else if (ans == 2)
		{
			int delim = findDelim();
			printf("%d %d\n", 0, delim);
			int end = stack[top / 2].index;
			printf("%d %d\n", end, L - 1);
		}
	}
	return 0;
}
