#include "pch.h"
typedef unsigned long long ulong;

const int NODE_SIZE = 1500010;
const int MAX_HASH_SIZE = 500000;
struct Node{
	ulong val;
	Node* next;
};
struct List {
	Node* head;
	void add(ulong val);
	int size;
};
int node_idx = 0;
Node node[NODE_SIZE];
struct LList{
	List hashTable[MAX_HASH_SIZE];
};
LList hashT;
LList initT;
void List::add(ulong val)
{
	Node* tmp = head;
	head = &node[node_idx++];
	head->next = tmp;
	head->val = val;
	size++;
}

int hash(ulong num)
{
	return num % MAX_HASH_SIZE;
}

void init()
{
	node_idx = 0;
	hashT = initT;
}

bool notIn(ulong key)
{

	int idx = hash(key);
	int lim = hashT.hashTable[idx].size;
	if (lim == 0) return true;
	Node* itr = hashT.hashTable[idx].head;
	if (itr->val == key) return false;
	for (int i = 1; i < lim; i++)
	{
		itr = itr->next;
		if (itr->val == key) return false;
	}
	return true;
}
int checkKey(ulong key)
{
	if (notIn(key))
	{
		hashT.hashTable[hash(key)].add(key);
		return 1;
	}
	else
	{
		return 0;
	}
}