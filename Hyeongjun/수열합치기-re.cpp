// #include <cstdio>
const int MAX_N = 1000;
const int MAX_M = 1000;
const int MAX_NODE = MAX_N * MAX_M * 2;

struct node{
  int value;
  node* prev;
  node* next;
};

struct list{
  node* head;
  node* tail;

  list():head(0), tail(0) {};
  void add(int value);
  void merge(list l);
};

node nodes[MAX_NODE];
list main_list;
int node_idx=0;

void list::add(int value){
  if(head==0){
    nodes[node_idx].value=value;
    nodes[node_idx].prev=0;
    nodes[node_idx].next=0;
    head = &nodes[node_idx];
    tail = &nodes[node_idx];
    node_idx+=1; 
  }
  else{
    nodes[node_idx].value=value;
    nodes[node_idx].prev=tail;
    nodes[node_idx].next=0;
    tail->next = &nodes[node_idx];
    tail = &nodes[node_idx];
    node_idx+=1;
  }
}

void list::merge(list new_list){
  node* find = head;
  while(find && find->value <= new_list.head->value){
    find = find -> next;
  }
  if(head == 0 ){
    head = new_list.head;
    tail = new_list.tail;
  }
  else if(find == 0){
    new_list.head->prev = tail;
    tail->next = new_list.head;
    tail = new_list.tail;
  }
  else if(find->prev==0){
    head->prev = new_list.tail;
    new_list.tail ->next = head;
    head = new_list.head;
  }
  else{
    new_list.head->prev = find->prev;
    find->prev->next = new_list.head;
    new_list.tail->next = find;
    find->prev = new_list.tail;
  }
}

// void print_main(){
//   printf("Merge\n");
//   node* tmp = main_list.head;
//   while(tmp){
//     printf("%d ",tmp->value);
//     tmp = tmp-> next;
//   }
//   printf ("\n");
// }

void init( )
{
  node_idx=0;
  main_list.head=0;
  main_list.tail=0;
}

void mergenums(int n, int * arr)
{   
  list new_list;
  for(int i=0;i<n;i++){
    new_list.add(arr[i]);
  }

  main_list.merge(new_list);
  // print_main();
}

int findkth( int kth)
{
  int ret=0;
  if(kth>0){
    node* head = main_list.head;
    kth -=1;
    while(kth--){
      head = head ->next;
    }
    ret = head->value;
  }
  else{
    node* tail = main_list.tail;
    kth = ~kth + 1;
    kth -=1;
    while(kth--){
      tail = tail->prev;
    }
    ret = tail->value;
  }

  return ret;
} 
