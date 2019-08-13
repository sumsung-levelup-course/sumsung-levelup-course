#define MAX_TEXT_LENGTH 5000
#define MAX_ASCII 200
char inText[MAX_TEXT_LENGTH + 1];
int countof[MAX_ASCII];
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
		if (count == a.count) return ch >= a.count;
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
	//void addFront(char ch, int cnt)
	//{
	//	NODE* newone = new NODE;
	//	newone->ch = ch;
	//	newone->count = cnt;
	//	newone->next = tail->next;
	//	newone->next->prev = newone;
	//	newone->prev = tail;
	//	tail->next = newone;
	//	size++;
	//}
	void add_frontof(NODE* ptr, char ch, int cnt)
	{
		NODE* newone = new NODE;
		newone->ch = ch;
		newone->count = cnt;
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
	{//�������
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
	for (int i = 0; i < MAX_ASCII; i++)
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
	NODE* list = 0;
	for (int i = ordersize - 1; i >= 0; i--)
	{
		nodelist.itr = nodelist.tail;
		nodelist.add_frontof(nodelist.itr->next, order[i].ch, order[i].cnt);
	}
	nodelist.itr = nodelist.tail;
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
	nodelist.add_frontof(nodelist.itr, newNode->ch, newNode->count);
	return;
}

void makeBinaryTree()
{
	while (nodelist.size > 1)
	{
		NODE* first = getFirst();
		NODE* second = getFirst();
		NODE* parent = new NODE;
		parent->count = first->count + second->count;
		parent->left = first;
		parent->right = second;
		addNode(parent);
	}
	return;
}