const int MAX = 1000100;
struct Node {
	int value;
	Node* next;
	Node* prev;
};
Node nodelist[MAX];
int node_idx = 0;
struct List {
	Node* head;
	Node* tail;
	int size;
	List()
	{
		head = new Node;
		tail = new Node;
		head->value = -1;
		tail->value = -1;
		head->prev = tail;
		head->next = 0;
		tail->next = head;
		tail->prev = 0;
		size = 0;
	}
	~List()
	{
		delete head;
		delete tail;
	}
	void add(int val, Node* list)
	{//list앞에 val을 가진 노드를 추가
		Node* first = list->prev;

		nodelist[node_idx].value = val;
		first->next = &nodelist[node_idx];
		nodelist[node_idx].next = list;
		list->prev = &nodelist[node_idx];
		nodelist[node_idx].prev = first;
		node_idx++;
		size++;
		return;
	}
	
};
List mainlist;
void init()
{
	mainlist.tail->next = mainlist.head;
	mainlist.head->prev = mainlist.tail;
	node_idx = 0;
}

struct Pt_set {
	Node* st;
	Node* end;
};
Pt_set makeList(int n, int* arr)
{//n 크기의 arr을 입력받아 list로 만든 후 head와 tail을 리턴.
	List fir;
	for (int i = 0; i < n; i++)
	{
		fir.add(arr[i], fir.head);
	}
	return { fir.tail->next, fir.head->prev };
}
Node* find_pos(int val, List* list)
{//list에서 val보다 커지는 위치의 노드를 리턴
	Node* itr = list->tail;
	while(itr->next!=list->head)
	{
		itr = itr->next;
		if (itr->value > val) return itr;
	}
	return list->head;
}
void insertList(Pt_set ptst, Node* pos)
{//ptst의 첫노드와 마지막노드,를 pos위치에 껴넣기
	Node* tmp = pos->prev;
	tmp->next = ptst.st;
	ptst.end->next = pos;
	pos->prev = ptst.end;
	ptst.st->prev = tmp;

}
void mergenums(int n, int * arr)
{
	Pt_set pt = makeList(n, arr); // n크기의 arr을 입력받아 head와 tail을 리턴.
	Node* pos = find_pos(pt.st->value, &mainlist); // list에서 value값보다 
	insertList(pt, pos);
	return;
}

int findkth(int kth)
{
	if (kth > 0)
	{
		Node* itr = mainlist.tail;
		for (int i = 0; i < kth; i++)
		{
			itr = itr->next;

		}
		return itr->value;
	}
	else
	{
		int n = -1 * kth;
		Node* itr = mainlist.head;
		for (int i = 0; i < n; i++)
		{
			itr = itr->prev;
		}
		return itr->value; 
	}

}
