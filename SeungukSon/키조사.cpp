#include <stdio.h>
typedef unsigned long long ulong;

struct Node {
	Node* prev;
	ulong value;
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


	void addfront(Node* sNode, ulong val);//snode앞쪽에 원소를 추가함
	void delNode(Node* sNode);
	void clear();
};
void LinkedList::clear()
{
	Node* nowNode = this->getTail();
	while (nowNode->getNext()->value != 0)
	{
		this->delNode(nowNode->getNext());
	}
}
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
void LinkedList::addfront(Node* sNode, ulong val)
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

struct HashNode {
	ulong key;
	LinkedList chain;
};
#define MAX_SIZE 2000000
struct Hashmap {
	HashNode hashmap[MAX_SIZE];
};
Hashmap init_hashmap;
Hashmap hashmap;

void init()
{
	for (int i = 0; i < MAX_SIZE; i++)
		hashmap.hashmap[i].chain.clear();
	hashmap = init_hashmap;
}

int hash(ulong a)
{
	return a % MAX_SIZE;
}
int checkKey(ulong key)
{
	int hashval = hash(key);
	if (hashmap.hashmap[hashval].key == 0) //충돌없다면
	{
		hashmap.hashmap[hashval].key = key;//값 넣어주기
		
		return 1;
	}
	else // 충돌시
	{
		if (hashmap.hashmap[hashval].key == key) return 0;
		else
		{//체인내 탐색
			Node* NowNode = hashmap.hashmap[hashval].chain.getTail();
			while (NowNode->getNext()->value != 0)
			{//체인 내에 없으면 0
				NowNode = NowNode->getNext();
				if (NowNode->value == key) return 0;
			}
			hashmap.hashmap[hashval].chain.addfront(NowNode->getNext(), key);
			return 1;
		}
	}
}