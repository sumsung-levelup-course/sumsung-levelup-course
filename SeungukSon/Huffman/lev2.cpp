#define MAX_TEXT_LENGTH 5000
#define MAX_ASCII 200
char inText[MAX_TEXT_LENGTH + 1];
int countof[MAX_ASCII];
struct mystruct {
	char ch;
	int cnt = 0;
	bool operator < (mystruct a)
	{
		if (cnt == a.cnt) return ch < a.ch;
		else return cnt < a.cnt;
	}
	bool operator <=(mystruct a)
	{
		if (cnt == a.cnt)
			return ch <= a.ch;
		else
			return cnt <= a.cnt;
	}
	void operator =(mystruct a)
	{
		cnt = a.cnt;
		ch = a.ch;
	}
	bool operator >(mystruct a)
	{
		if (cnt == a.cnt) return ch > a.ch;
		else return cnt > a.cnt;
	}
};
mystruct order[MAX_ASCII];
int ordersize = 0;

int num;

void quickSort(int first, int last)
{
	int pivot;
	int i;
	int j;
	mystruct temp;
	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;

		while (i < j)
		{
			while (order[i] <= order[pivot] && i < last) i++;
			while (order[j] > order[pivot])	j--;
			if (i < j)
			{
				temp = order[i];
				order[i] = order[j];
				order[j] = temp;
			}
		}
		temp = order[pivot];
		order[pivot] = order[j];
		order[j] = temp;

		quickSort(first, j - 1);
		quickSort(j + 1, last);
	}
}

void make_dict()
{
	for (int i = 0; i < MAX_TEXT_LENGTH + 1; i++)
	{
		if (!inText[i]) break;
		countof[inText[i]]++;
	}
	for (int i = 0; i < MAX_ASCII; i++)
	{//차원축소
		if (countof[i] != 0)
		{
			mystruct tmp;
			tmp.ch = (char)i;
			tmp.cnt = countof[i];
			order[ordersize++] = tmp;
		}
	}

	quickSort(0, ordersize - 1);
	//for (int i = 0; i < ordersize; i++)
	//{
	//	printf("order[%d]: %c  %d\n", i, order[i].ch, order[i].cnt);
	//}
}

void Initialize()
{
	for (int i = 0; i < MAX_ASCII; i++)
		countof[i] = 0;
	ordersize = 0;
	return;
}

void setText(const char text[MAX_TEXT_LENGTH + 1])
{
	int i = 0;
	for (; i < MAX_TEXT_LENGTH + 1; i++)
	{
		if (text[i] != 0) inText[i] = text[i];
		else break;
	}
	inText[i] = 0;
	make_dict();
	return;
}

unsigned int getCount(char ch)
{
	unsigned int ret = 0;
	int i = 0;
	while (inText[i])
	{
		if (inText[i] == ch) ret++;
		i++;
	}

	return ret;
}

unsigned int getRank(char ch)
{
	unsigned int ret = 0;
	for (int i = 0; i < ordersize; i++)
	{
		if (order[i].ch == ch) return i + 1;
	}

	return ret;
}