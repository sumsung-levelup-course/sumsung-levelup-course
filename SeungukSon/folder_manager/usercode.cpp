#define MAX_LEN 25
#define MAX_FILE 27010
#define OUT "}"
#define ROOT "/"
#define STAR "*"
struct Node {
	Node* prev;
	Node* next;
	int idx;
	char data[MAX_LEN];
};

int cur = 0;
int size = 0;
int findcnt = 0;
int delcnt = 0;
int strcmp(char w1[], char w2[]);
int strlen(char w1[]);
int strcmp(char w1[], char w2[]);
void strcpy(char* target, char* in);
int strcmp(char w1[], char w2[])
{
	int len1 = strlen(w1);
	int len2 = strlen(w2);
	int min_len = len1 < len2 ? len1 : len2;

	for (int i = 0; i < min_len; i++)
	{
		if (w1[i] != w2[i]) return w1[i] - w2[i];
	}
	if (len1 == len2) return 0;
	return len1 < len2 ? -1 : 1;
}
int strlen(char w1[])
{
	int ret = 0;
	for (int i = 0; i < MAX_LEN; i++)
	{
		if (w1[i] != 0)
		{
			ret++;
		}
		else break;
	}

	return ret;
}
void strcpy(char* target, char* in)
{
	int siz = strlen(in);
	int i = 0;
	for (; i < siz; i++)
	{
		target[i] = in[i];
	}

	target[i] = 0;
}
void delNode(Node* d);

class LinkedList {
private:
	int parent;
	char name[MAX_LEN];
	Node* tail;
	Node* head;
	Node* itr;

public:
	LinkedList()
	{
		tail = new Node;
		head = new Node;
		char outof_range[] = OUT;
		strcpy(tail->data, outof_range);
		strcpy(head->data, outof_range);

		tail->next = head;
		head->prev = tail;

		itr = tail;
	}
	void setItr() { itr = tail; }
	void setItr(Node* it) { itr = it; }
	void setName(char name[]) { strcpy(this->name, name); }
	void setParent(int parent) { this->parent = parent; }
	Node* getTail() { return tail; }
	Node* getHead() { return head; }
	Node* getItr() { return itr; }
	char* getName() { return name; }
	int getParent() { return parent; }
	int getNext()
	{
		char out[] = OUT;
		itr = itr->next;
		if (strcmp(itr->data, out) != 0) return 1;
		else return 0;
	}
	void add(char word[], int nownum);
	void clear()
	{
		itr = tail;
		while (this->getNext())
		{
			delNode(itr);
			itr = tail;
		}
	}
};
LinkedList file_list[MAX_FILE];
void delNode(Node* d)
{
	Node* first = d->prev;
	Node* last = d->next;
	first->next = last;
	last->prev = first;
	char outof_range[] = OUT;
	file_list[d->idx].setName(outof_range); //file_list의 이름을 '}'로 설정
	delcnt++;
	delete d;
}

void delson(int idx)
{
	file_list[idx].setItr();
	while (file_list[idx].getNext())
	{
		delson(file_list[idx].getItr()->idx);
		delNode(file_list[idx].getItr());
		file_list[idx].setItr();
	}
}
void LinkedList::add(char word[], int nownum)
{//sNode앞자리에 word값을 가진 노드 추가, file_list에 추가까지 된다.
	Node* newone = new Node;
	strcpy(newone->data, word);

	itr = tail; //setitr;
	while (getNext())
	{
		int flag = strcmp(word, itr->data);
		if (!flag) return; //아예같으면 리턴
		if (strcmp(word, itr->data) < 0) break;
	}
	Node* first = itr->prev;
	newone->prev = first;
	first->next = newone;
	newone->next = itr;
	itr->prev = newone;

	newone->idx = size;

	file_list[size].setName(word);
	file_list[size].setParent(nownum);
	size++;
}
int startwith(char* str, char* w)
{
	int len1 = strlen(str);
	int len2 = strlen(w);
	if (len2 < len1) return 0;
	for (int i = 0; i < len1; ++i)
	{
		if (str[i] != w[i]) return 0;
	}
	return 1;
}
void init()
{
	char outof_range[] = OUT;
	for (int i = 0; i < size; ++i)
	{
		file_list[i].clear();
	}
	cur = 0;
	size = 0;
	char root[] = ROOT;
	file_list[size].setName(root);
	file_list[size].setParent(-1);
	size++;
}
void make(char keyword[])
{
	file_list[cur].add(keyword, cur);
}
void change(char keyword[])
{
	char root[] = ROOT;
	char parent[] = "..";
	char top[] = "-1";
	char star[] = STAR;
	if (strcmp(keyword, root) == 0) cur = 0; //루트로변경
	else if (strcmp(keyword, parent) == 0)
	{
		cur = file_list[cur].getParent();
		if (cur == -1) cur = 0; //루트의 부모는 루트
		return;
	}
	else if (strcmp(keyword, star) == 0)
	{
		file_list[cur].setItr();
		if (file_list[cur].getNext())
		{//첫 노드가 존재하면 cur변경
			cur = file_list[cur].getItr()->idx;
			return;
		}
	}
	else
	{//문자열 또는 문자열*
		char str[MAX_LEN];
		strcpy(str, keyword);
		int st_len = strlen(str);
		if (keyword[strlen(keyword) - 1] == '*')
		{//문자열*일 경우
			str[--st_len] = 0;
			file_list[cur].setItr();
			while (file_list[cur].getNext())
			{
				Node* now = file_list[cur].getItr();
				if (startwith(str, now->data))
				{
					cur = now->idx;
					return;
				}
			}
		}
		else
		{
			file_list[cur].setItr();
			while (file_list[cur].getNext())
			{
				Node* now = file_list[cur].getItr();
				if (strcmp(now->data, str) == 0)
				{
					cur = now->idx;
					return;
				}
			}
		}

	}

}
int remove(char keyword[])
{
	delcnt = 0;
	char star[] = STAR;
	if (strcmp(keyword, star) == 0)
	{
		delson(cur);
		return delcnt;
	}
	else
	{
		char str[MAX_LEN];
		strcpy(str, keyword);
		int st_len = strlen(str);
		if (keyword[strlen(keyword) - 1] == '*')
		{//문자열*일 경우
			str[--st_len] = 0;
			file_list[cur].setItr();
			while (file_list[cur].getNext())
			{
				Node* now = file_list[cur].getItr();
				if (startwith(str, now->data))
				{
					delson(now->idx);
					Node* tmp = now->prev;
					delNode(now);
					file_list[cur].setItr(tmp);
				}
			}
		}
		else
		{//문자열일경우
			file_list[cur].setItr();
			while (file_list[cur].getNext())
			{
				Node* now = file_list[cur].getItr();
				if (strcmp(now->data, str) == 0)
				{
					delson(now->idx);
					Node* tmp = now->prev;
					delNode(now);
					return delcnt;
				}
			}
		}
	}
	return delcnt;
}
void countson(int idx)
{
	file_list[idx].setItr();
	while (file_list[idx].getNext())
	{
		countson(file_list[idx].getItr()->idx);
		findcnt++;
	}
}
void count_startwith(int idx, char word[])
{
	file_list[idx].setItr();
	while (file_list[idx].getNext())
	{
		Node* now = file_list[idx].getItr();
		if (startwith(word, now->data))
			findcnt++;
		count_startwith(now->idx, word);
	}
}
void countstr(int idx, char word[])
{
	file_list[idx].setItr();
	while (file_list[idx].getNext())
	{
		Node* now = file_list[idx].getItr();
		if (strcmp(word, now->data) == 0)
			findcnt++;
		countstr(now->idx, word);
	}
}
int find(char keyword[])
{
	findcnt = 0;
	char star[] = STAR;
	if (strcmp(keyword, star) == 0)
	{
		countson(cur);
	}
	else
	{
		char str[MAX_LEN];
		strcpy(str, keyword);
		int st_len = strlen(str);
		if (keyword[strlen(keyword) - 1] == '*')
		{//문자열*일 경우
			str[--st_len] = 0;
			count_startwith(cur, str);
		}
		else
		{//문자열일경우
			countstr(cur, str);
		}
	}
	return findcnt;

}