typedef unsigned long long ulong;
const int MAX_N = 1500000;
const int MAX_HASH  = 1500000;

struct node{
  ulong value;
  node* next;
};

struct list{
  node* head;

  void add(ulong value);
};

node nodes[MAX_N];
list hash[MAX_HASH];
int node_idx=0;

void list::add(ulong value){
  nodes[node_idx].value = value;
  nodes[node_idx].next = head;
  head = &nodes[node_idx];
  node_idx+=1;
}

int hash_function(ulong key){
  ulong ret = key % (ulong)MAX_HASH;
  return ret;
}

int find_key(ulong value){
  node* cur = hash[hash_function(value)].head;
  while(cur) {
    if(cur->value == value) return 1;
    cur = cur->next;
  }

  return 0;

}

void init()
{
  node_idx=0;
  for(int i=0;i<MAX_HASH;i++){
    hash[i].head = 0;
  }
}

int checkKey(ulong key)
{
  int ret=0;
  if(find_key(key)){
    ret = 0;
  }
  else {
    hash[hash_function(key)].add(key);
    ret = 1;
  }
	return ret;
}
