typedef unsigned long long ulong;

const int MAX_NODE = 1500000;
const int MAX_HASH_SIZE = 987654;
const int MOD = MAX_HASH_SIZE;

struct node {
	ulong value;
	node* next;
};

struct list {
	node* head;
	void add(ulong value);
};

int node_idx;
node nodes[MAX_NODE];
list hash[MAX_HASH_SIZE];

void list::add(ulong value) {
	node* tmp = head;
	head = &nodes[node_idx++];
	head->value = value;
	head->next = tmp;
}

int hash_function(ulong value) {
	ulong ret = value % (ulong)MOD;

	return (int)ret;
}

int find(ulong value) {
	int ret = 0;
	int key = hash_function(value);

	node* cur = hash[key].head;

	while (cur != 0 && cur->next != 0) {
		if (cur->value == value) return 1;
		cur = cur->next;
	}

	if (cur != 0) {
		if (cur->value == value) return 1;
	}

	return ret;
}

void push(ulong value) {
	hash[hash_function(value)].add(value);
}

void init()
{
	node_idx = 0;
	for (int i = 0; i < MAX_HASH_SIZE; i++) {
		hash[i].head = 0;
	}
}

int checkKey(ulong key)
{
	int ret = 0;
	if (!find(key)) {
		ret = 1;
		push(key);
	}

	return ret;
}
