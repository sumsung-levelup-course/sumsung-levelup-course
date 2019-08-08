struct Node {
	Node* prev;
	int value;
	Node* next;

	Node* getNext();
	Node* getPrev();
};

class LinkedList
{
private:
	Node* head;
	Node* tail;
public:
	LinkedList()
	{
		head = new Node;
		tail = new Node;
		tail->value = 0;
		head->value = 0;
		tail->next = head;
		head->prev = tail;
	}

	LinkedList(int n, int* arr);//n크기의 arr배열을 입력받아 linkedList로 변환해주는 생성자
	Node* getTail() { return tail; }
	Node* getHead() { return head; }


	void addfront(Node* sNode, int val);//snode앞쪽에 원소를 추가함
	void delNode(Node* sNode);
};

LinkedList::LinkedList(int n, int* arr)
{

}
void LinkedList::delNode(Node* sNode)
{
	if (sNode == tail || sNode == head) return;
	Node* prevNode = sNode->prev;
	Node* nextNode = sNode->next;

	prevNode->next = nextNode;
	nextNode->prev = prevNode;
	delete(sNode);
}
Node* Node::getNext()
{
	return this->next;
}
Node* Node::getPrev()
{
	return this->prev;
}
void LinkedList::addfront(Node* sNode, int val)
{
	Node* frontNode = sNode->prev;
	Node* addNode = new Node;
	addNode->value = val;

	frontNode->next = addNode;
	addNode->prev = frontNode;

	sNode->prev = addNode;
	addNode->next = sNode;
}
LinkedList l;
Node* findidx(int num)
{//num보다 큰값을 링크드리스트에서 찾아 그 위치를 반환. 큰값이 없다면 head반환
	Node* nowNode = l.getTail();
	while (nowNode->getNext()->value != 0)
	{
		nowNode = nowNode->getNext();
		if (nowNode->value > num)
		{
			//printf("nowNode->val : %d \n", nowNode->value);
			return nowNode;
		}
	}
	return l.getHead();
}

void init()
{
	while (l.getTail()->next != l.getHead())
		l.delNode(l.getTail()->next);
}

void mergenums(int n, int * arr)
{
	//printf("arr[0]: %d\n", arr[0]);
	Node* idx = findidx(arr[0]);
	for (int i = 0; i < n; ++i)
	{

		l.addfront(idx, arr[i]);
	}
	Node* nowNode = l.getTail();
	while (nowNode->getNext()->value != 0)
	{
		nowNode = nowNode->getNext();
		//printf("%d ", nowNode->value);
	}
	//printf("\n");
}

int findkth(int kth)
{
	if (kth > 0)
	{
		Node* nowNode = l.getTail();
		for (int i = 0; i < kth; ++i)
		{
			nowNode = nowNode->getNext();
		}
		return nowNode->value;
	}
	else
	{
		Node* nowNode = l.getHead();
		for (int i = 0; i < -kth; ++i)
		{
			nowNode = nowNode->getPrev();
		}
		return nowNode->value;
	}
}
