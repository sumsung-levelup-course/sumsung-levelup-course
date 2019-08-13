#define MAX_TEXT_LENGTH 5000
#define MAX_ASCII 300
char inText[MAX_TEXT_LENGTH + 1];
int countof[MAX_ASCII];

char nowch[32];
char code_of[MAX_ASCII][32];
int code_table_size = 0;
struct NODE {
	char ch = 0;
	unsigned int count = 0;
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
	NODE()
	{
		left = 0;
		right = 0;
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
	for (int i = 0; i < MAX_ASCII + 1; i++)
		countof[i] = 0;
	ordersize = 0;
	nodelist.itr = nodelist.tail;
	while (nodelist.getNext())
	{
		nodelist.delFront();
		nodelist.itr = nodelist.tail;
	}
	code_table_size = 0;
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
	for (int i = 0; i < 50000; i++)
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
		my_strcpy(code_of[now->ch], nowch);
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

	//code_of �ϼ�
	return;
}

void getBits(char ch, char bits[32])
{
	my_strcpy(bits, code_of[ch]);
	return;
}

void appendstr(int* idx, char data[], char w[])
{//data�迭�� idx���� w[]+' '�� append 
	int len = my_strlen(w);
	for (int i = 0; i < len; i++)
	{
		data[(*idx)++] = w[i];
	}
}
void makeHeader(char data[256 * 10])
{
	int head_idx = 0;
	int s = ordersize;
	data[head_idx++] = (char)s;
	for (int i = 0; i < MAX_ASCII; i++)
	{
		if (countof[i] != 0)
		{
			data[head_idx++] = (char)i;
			data[head_idx++] = (char)my_strlen(code_of[i]);
		}
	}
	char tmp[256 * 10];
	int tmpidx = 0;
	for (int i = 0; i < MAX_ASCII; i++)
	{
		if (countof[i] != 0)
		{
			appendstr(&tmpidx, tmp, code_of[i]);
		}
	}

	tmp[tmpidx++] = 0;
	int c = 0;
	int tmpnum = 0;
	for (int i = 0; i < tmpidx; i++)
	{
		if (c == 8)
		{
			data[head_idx++] = (char)tmpnum;
			tmpnum = 0;
			c = 0;
		}
		if (i == tmpidx - 1)
		{
			while (c < 8)
			{
				tmpnum = tmpnum * 2;
				c++;
			}
			data[head_idx++] = (char)tmpnum;
		}
		tmpnum = tmpnum * 2 + tmp[i] - '0';
		c++;
	}
	data[head_idx++] = 0;
	return;
}

void encode(char data[MAX_TEXT_LENGTH + 1])
{
	char tmp[MAX_TEXT_LENGTH * 10];
	int tmp_idx = 0;
	int idx = 0;
	int bit_num = 0;
	int head_idx = 0;

	while (inText[idx])
	{
		//printf("codeof[%d]:%s  ", idx, code_of[inText[idx]]);
		appendstr(&tmp_idx, tmp, code_of[inText[idx]]);
		bit_num += my_strlen(code_of[inText[idx]]);
		idx++;
	}

	tmp[tmp_idx++] = 0;
	//printf("tmp:%s   bit_num: %d\n", tmp, bit_num);
	data[head_idx++] = bit_num / 256;
	data[head_idx++] = bit_num % 256;
	int c = 0;
	int tmpnum = 0;
	for (int i = 0; i < tmp_idx; i++)
	{
		if (c == 8)
		{
			data[head_idx++] = (char)tmpnum;
			//printf("tmpnum: %d ", tmpnum);
			tmpnum = 0;
			c = 0;
		}
		if (i == tmp_idx - 1)
		{
			while (c < 8)
			{
				tmpnum = tmpnum * 2;
				c++;
			}
			data[head_idx++] = (char)tmpnum;
		}
		tmpnum = tmpnum * 2 + tmp[i] - '0';
		c++;
	}
	data[head_idx++] = 0;

}

struct CodeNode {
	char ch;
	char code[20];
	int bit_num;
};
CodeNode code_table[MAX_ASCII];

void make_tree(int size)
{
	NODE* top = new NODE;
	nodelist.add_frontof(nodelist.head, top);
	for (int i = 0; i < size; i++)
	{
		int len = my_strlen(code_table[i].code);
		nodelist.itr = nodelist.tail;
		nodelist.getNext();
		for (int j = 0; j < len; j++)
		{
			if (code_table[i].code[j] == '0')
			{//0�̸�
				if (nodelist.itr->left == 0)
				{
					NODE* first = new NODE;
					nodelist.itr->left = first;
				}
				nodelist.itr = nodelist.itr->left;
			}
			else
			{
				if (nodelist.itr->right == 0)
				{
					NODE* second = new NODE;
					nodelist.itr->right = second;
				}
				nodelist.itr = nodelist.itr->right;
			}
		}
		nodelist.itr->ch = code_table[i].ch;
	}
}//tree�����
//void print_tree(NODE* ptr)
//{
//	if (ptr->ch != 0)
//	{
//		printf("char:%c  ", ptr->ch);
//		return;
//	}
//	if(ptr->left!=0) print_tree(ptr->left);
//	if(ptr->right!=0) print_tree(ptr->right);
//}
void readHeader(char data[256 * 10])
{
	code_table_size = data[0];
	int until = data[0] * 2;
	int code_idx = 0;
	int totalLen = 0;
	for (int i = 0; i < until; i++)
	{
		if (i % 2 == 0)
		{//�����ڵ��
			code_table[code_idx].ch = data[i + 1];
		}
		else
		{
			code_table[code_idx++].bit_num = data[i + 1];
			totalLen += data[i + 1];
		}
	}//�ڵ����̺��� ch,bitnum�÷� ä��

	char bit_part[30000];
	int bit_part_idx = 0;
	int data_idx = data[0] * 2;
	//printf("data_idx:%d  len: %d  ", data_idx, my_strlen(data));
	if (totalLen % 8 != 0)
	{
		totalLen /= 8;
		totalLen++;
	}
	else totalLen /= 8;
	for (int i = 0; i <= totalLen; i++)
	{
		int num = data[data_idx++];
		for (int j = 7; j >= 0; j--)
		{
			bit_part[bit_part_idx++] = (num & (1 << j)) != 0 ? '1' : '0';
		}
	}//bit��Ʈ �����Ϸ�
	bit_part[bit_part_idx++] = 0;
	bit_part_idx = 0;
	for (int i = 0; i < code_table_size; i++)
	{
		for (int j = 0; j < code_table[i].bit_num; j++)
		{
			code_table[i].code[j] = bit_part[bit_part_idx++];
		}
	}//code_table�ϼ�

	//for (int i = 0; i < code_table_size; i++)
	//{
	//	printf("code_table[%d] - ch:%c  code:%s  bitnum:%d\n", i, code_table[i].ch, code_table[i].code, code_table[i].bit_num);
	//}
	make_tree(code_table_size);//Ʈ�� ����

	nodelist.itr = nodelist.tail->next;
	//print_tree(nodelist.itr);

}

void decode(char data[MAX_TEXT_LENGTH + 1], char output[MAX_TEXT_LENGTH + 1])
{}