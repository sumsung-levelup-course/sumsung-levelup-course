#define MAX_TEXT_LENGTH 5000
#define MAX_ASCII 300
//#include <stdio.h>
int d[2];
int code_table_size = 0;

struct CodeNode {
	char ch;
	char code[20];
	int bit_num;
};
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

LinkedList nodelist;
CodeNode code_table[MAX_ASCII];
void del_tree(NODE* ptr)
{
	if (ptr->left != 0) del_tree(ptr->left);
	if (ptr->right != 0)del_tree(ptr->right);
	if (ptr->left == 0 && ptr->right == 0)
	{
		delete ptr;
		return;
	}
}
void Initialize()
{
	nodelist.itr = nodelist.tail;
	if (nodelist.itr->left != 0) del_tree(nodelist.itr->left);
	if (nodelist.itr->right != 0) del_tree(nodelist.itr->right);
	nodelist.itr = nodelist.tail;
	while (nodelist.getNext())
	{
		nodelist.delFront();
		nodelist.itr = nodelist.tail;
	}
	for (int i = 0; i < code_table_size; i++)
	{
		code_table[i].ch = 0;
		code_table[i].code[0] = 0;
		code_table[i].bit_num = 0;
	}
	code_table_size = 0;
	d[0] = d[1] = 0;

	return;
}

int my_strlen(char w[])
{
	int ret = 0;
	for (int i = 0; i < 5000; i++)
	{
		if (w[i] != 0) ret++;
		else break;
	}
	return ret;
}

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
			{//0이면
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
}//tree만들기

void readHeader(char data[256 * 10])
{
	code_table_size = 0;
	for (int i = 0; i <= 7; i++)
	{
		if ((data[0] & (1 << i)) != 0)
			code_table_size += (1 << i);
	}

	int until = code_table_size * 2;
	int code_idx = 0;
	int totalLen = 0;
	for (int i = 0; i < until; i++)
	{
		int tmp = 0;
		for (int j = 0; j <= 7; j++)
		{
			if ((data[i + 1] & (1 << j)) != 0)
				tmp += (1 << j);
		}
		if (i % 2 == 0)
		{//문자코드부
			code_table[code_idx].ch = tmp;
		}
		else
		{
			code_table[code_idx++].bit_num = tmp;
			totalLen += tmp;
		}
	}//코드테이블의 ch,bitnum컬럼 채움

	char bit_part[40000];
	int bit_part_idx = 0;
	int data_idx = code_table_size * 2 + 1;
	//printf("data_idx:%d  len: %d  ", data_idx, my_strlen(data));
	if (totalLen % 8 != 0)
	{
		totalLen /= 8;
		totalLen++;
	}
	else totalLen /= 8;
	for (int i = 0; i < totalLen; i++)
	{
		int num = data[data_idx++];
		for (int j = 7; j >= 0; j--)
		{
			bit_part[bit_part_idx++] = (num & (1 << j)) != 0 ? '1' : '0';
			//printf("bit_part: %d  ans:%d\n  ", bit_part[bit_part_idx], num);
		}
	}//bit파트 생성완료
	bit_part[bit_part_idx++] = 0;
	bit_part_idx = 0;
	for (int i = 0; i < code_table_size; i++)
	{
		int j = 0;
		for (; j < code_table[i].bit_num; j++)
		{
			code_table[i].code[j] = bit_part[bit_part_idx++];
		}
		code_table[i].code[j] = 0;
	}//code_table완성

	make_tree(code_table_size);//트리 만듦

	nodelist.itr = nodelist.tail->next;
	//print_tree(nodelist.itr);

}

void decode(char data[MAX_TEXT_LENGTH + 1], char output[MAX_TEXT_LENGTH + 1])
{//data[0]:length/256; data[1]:length%256, data[-]:8bit으로끊어진 원문데이터

//	printf("data[0]:%d  data[1]:%d\n", data[0],data[1]);
	for (int k = 0; k < 2; k++)
	{
		for (int i = 0; i <= 7; i++)
		{
			if ((data[k] & (1 << i)) != 0)
				d[k] += (1 << i);
		}
	}
	//printf("d[0]:%d, d[1]:%d\n", d[0], d[1]);
	int length = d[0] * 256 + d[1];
	//printf("length:%d  ", length);
	int save = length % 8;
	length = (length % 8 == 0) ? length / 8 : length / 8 + 1;
	//printf("length: %d \n", length);
	int data_idx = 2;
	int output_idx = 0;
	nodelist.itr = nodelist.tail->next; //itr초기화
	for (int i = 0; i < length; i++)
	{
		if (i == length - 1)
		{
			for (int j = 7; j > 7 - save; j--)
			{
				if ((data[data_idx] & (1 << j)) != 0)//1이면
				{
					nodelist.itr = nodelist.itr->right;
				}
				else
					nodelist.itr = nodelist.itr->left;

				if (nodelist.itr->ch != 0)//문자가 있으면
				{
					output[output_idx++] = nodelist.itr->ch;
					//("%c", nodelist.itr->ch);
					nodelist.itr = nodelist.tail->next; //itr초기화
				}
			}
			break;
		}
		//printf("data[%d]: %d  ", data_idx,data[data_idx]);
		for (int j = 7; j >= 0; j--)
		{
			if ((data[data_idx] & (1 << j)) != 0)//1이면
			{
				nodelist.itr = nodelist.itr->right;
			}
			else
				nodelist.itr = nodelist.itr->left;

			if (nodelist.itr->ch != 0)//문자가 있으면
			{
				output[output_idx++] = nodelist.itr->ch;
				//printf("%c", nodelist.itr->ch); 
				nodelist.itr = nodelist.tail->next; //itr초기화
			}
		}
		data_idx++;

	}
	output[output_idx++] = 0;
	//printf("output: %s\n", output);
}