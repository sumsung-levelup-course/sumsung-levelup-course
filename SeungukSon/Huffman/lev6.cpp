#define MAX_TEXT_LENGTH 5000
#define MAX_ASCII 200
char inText[MAX_TEXT_LENGTH + 1];
int countof[MAX_ASCII];

char nowch[32];
char encode[MAX_ASCII][32];

struct NODE {
	char ch;
	unsigned int count;
	NODE* next;
	NODE* prev;
	NODE* left;
	NODE* right;
	bool operator <(NODE a)
	{
		if (count == a.count) return ch < a.ch;
		else return count < a.count;
	}
	bool operator>=(NODE a)
	{
		if (count == a.count) return ch >= a.ch;
		else return count >= a.count;
	}

};
struct LinkedList
{
	NODE* tail;
	NODE* head;
	NODE* itr;
	int size;
	LinkedList()
	{
		tail = new NODE;
		head = new NODE;
		size = 0;
		tail->next = head;
		head->prev = tail;
	}
	int getNext()
	{
		itr = itr->next;
		if (itr != head) return 1;
		else return 0;
	}

	void add_frontof(NODE* ptr, NODE* newone)
	{
		NODE* tmp = ptr->prev;
		tmp->next = newone;
		newone->prev = tmp;
		newone->next = ptr;
		ptr->prev = newone;
		size++;
	}
	void delFront()
	{
		if (tail->next != head)
		{
			NODE* target = tail->next;
			NODE* tmp = target->next;
			tail->next = tmp;
			tmp->prev = tail;
			delete target;
		}
		size--;
	}
};

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
LinkedList nodelist;
void makeBinaryTree();
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
}

void Initialize()
{
	for (int i = 0; i < MAX_ASCII + 1; i++)
		countof[i] = 0;
	ordersize = 0;
	nodelist.itr = nodelist.tail;
	while (nodelist.getNext())
	{
		nodelist.delFront();
		nodelist.itr = nodelist.tail;
	}

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
	for (int i = ordersize - 1; i >= 0; i--)
	{
		nodelist.itr = nodelist.tail;
		NODE* newone = new NODE;
		newone->ch = order[i].ch;
		newone->count = order[i].cnt;
		nodelist.add_frontof(nodelist.itr->next, newone);
	}
	nodelist.itr = nodelist.tail;

	makeBinaryTree();
	return;
}

unsigned int getTopNodeCount()
{
	return nodelist.size;
}
void getRankInfo(unsigned int index, NODE* node)
{
	nodelist.itr = nodelist.tail;
	for (int i = 0; i < index; i++)
	{
		nodelist.itr = nodelist.itr->next;
	}
	node->count = nodelist.itr->count;
	node->ch = nodelist.itr->ch;

	return;
}

NODE* getFirst()
{
	NODE* target = nodelist.tail->next;
	NODE* second = target->next;
	nodelist.tail->next = second;
	second->prev = nodelist.tail;
	nodelist.size--;
	return target;
}

void addNode(NODE* newNode)
{
	nodelist.itr = nodelist.tail;
	while (nodelist.getNext())
	{
		if (*nodelist.itr >= *newNode) break;
	}
	nodelist.add_frontof(nodelist.itr, newNode);
	return;
}


int my_strlen(char w[])
{
	int ret = 0;
	for (int i = 0; i < 32; i++)
	{
		if (w[i] != 0)ret++;
		else break;
	}
	return ret;
}
void my_strcpy(char target[], char in[])
{
	int len = my_strlen(in);
	int idx = 0;
	for (; idx < len; idx++)
	{
		target[idx] = in[idx];
	}
	target[idx] = 0;
}

void saveEncode(int lev, NODE* now, char num)
{
	nowch[lev] = num;
	if (now->ch != 0)
	{
		nowch[lev + 1] = 0;
		my_strcpy(encode[now->ch], nowch);
		return;
	}
	saveEncode(lev + 1, now->left, '0');
	saveEncode(lev + 1, now->right, '1');
}


void makeBinaryTree()
{
	while (nodelist.size > 1)
	{
		NODE* first = getFirst();
		NODE* second = getFirst();
		NODE* parent = new NODE;
		parent->ch = 0;
		parent->count = first->count + second->count;
		parent->left = first;
		parent->right = second;
		addNode(parent);
	}
	saveEncode(0, nodelist.tail->next->left, '0');
	saveEncode(0, nodelist.tail->next->right, '1');
	//for (int i = 0; i < MAX_ASCII; i++)
	//{
	//	printf("encode[%c]:%s\n", i, encode[i]);
	//}
	return;
}

void getBits(char ch, char bits[32])
{
	my_strcpy(bits, encode[ch]);
	return;
}