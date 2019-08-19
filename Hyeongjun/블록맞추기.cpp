#include <algorithm>
using namespace std;

const int MAX=30000;
const int MAX_HASH = 43046721;
const int INF=987654321;

struct node{
  int max_height;
  int min_height;
  node* next;
  node* prev;
};

struct BLOCK{
  int block[4][4];
  int min_height;
  int max_height;
};

struct list{
  node* head;
  void add(int max_height,int min_height);
  void del(node* target);
};

list my_hash[MAX_HASH];
node nodes[MAX];
int node_idx=0;
BLOCK blocks[MAX];

bool cmp(BLOCK b1, BLOCK b2){
  return b1.max_height < b2.max_height;
}

void list::add(int max_height,int min_height){
  if(head==0){
    head = &nodes[node_idx++];
    head->max_height=max_height;
    head->min_height=min_height;
    head->next=0;
    head->prev=0;
  }
  else{
    node* tmp = head;
    head = &nodes[node_idx++];
    head->max_height=max_height;
    head->min_height=min_height;
    head->next = tmp;
    head->prev=0;
    tmp->prev=head;
  }
}

void list::del(node* target){
  node* prev = target->prev;
  target->next->prev = prev;
  prev->next = target->next;
  target->max_height=-1;
  target->min_height=-1;
  target->next=0;
  target->prev=0;
}

void init(){
  node_idx=0;
}

int square_3(int number){
  if(number==0){
    return 1;
  }
  return 3 * square_3(number-1);
}

void copy(int dst[4][4], int src[4][4],int base){
  for(int y=0;y<4;y++){
    for(int x=0;x<4;x++){
      dst[y][x] = src[y][x] - base;
    }
  }
}

int hash_function(int block[4][4]){
  int ret=0;
  for(int y=0;y<4;y++){
    for(int x=0;x<4;x++){
      ret += (block[y][x] * square_3(4*y+x));
    }
  }
  return ret;
}

int get_height(int block[4][4]){
  int max_height=0;
  for(int y=0;y<4;y++){
    for(int x=0;x<4;x++){
      if(block[y][x] > max_height){
        max_height = block[y][x];
      }
    }
  }
  return max_height;
}

void update_hash(int module[][4][4]){
  int min_height=INF;
  int max_height=0;
  int block[4][4];
  for(int i=0;i<MAX;i++){
    min_height=INF;
    max_height=0;
    for(int y=0;y<4;y++){
      for(int x=0;x<4;x++){
        if(module[i][y][x] > max_height){
          max_height= module[i][y][x];
        }
        if(module[i][y][x] < min_height){
          min_height = module[i][y][x];
        }
      }
    }
    copy(blocks[i].block,module[i],0);
    blocks[i].min_height = min_height;
    blocks[i].max_height = max_height;

    copy(block,module[i],min_height);
    my_hash[hash_function(block)].add(max_height,min_height);
  }
}

node* find_block(BLOCK block){
  node* cur = my_hash[hash_function(block.block)].head;
  while(cur){
    if(cur->max_height == block.max_height) break;
    cur = cur->next;
  }
  return cur;
}

node* find_block_shape(int block[4][4]){
  node* cur = my_hash[hash_function(block)].head;
  node* ret = cur;
  int height = 0;
  while(cur){
    if(cur->max_height > height){
      ret = cur;
      height = cur->max_height;
    }
    cur = cur->next;
  }
  return ret;
}

void rotate(int block[4][4]){
  int ret[4][4];
  for(int y=0;y<4;y++){
    for(int x=0;x<4;x++){
      ret[x][3-y] = block[y][x];
    }
  }

  for(int y=0;y<4;y++){
    for(int x=0;x<4;x++){
      block[y][x] = ret[y][x];
    }
  }
}

node* get_target_block(BLOCK block){
  int target_shape[4][4];
  for(int y=0;y<4;y++){
    for(int x=0;x<4;x++){
      target_shape[y][x] = 2 - block.block[y][x];
    }
  }

  node* tmp;
  node* target_block;
  int height=0;
  for(int i=0;i<3;i++){
    tmp = find_block_shape(target_shape);
    if(tmp->max_height > height){
      height = tmp->max_height;
      target_block = tmp;
    }
    rotate(target_shape);
  }

  return target_block;
}

int update_ret(node* block_1,node* block_2){

}

int makeBlock(int module[][4][4]){
  int ret=0;
  init();
  update_hash(module);


  //sorting blocks
  sort(blocks,blocks+MAX);
  node* block_1=0;
  node* block_2=0;
  for(int i=0;i<MAX;i++){
    block_1 = find_block(blocks[i]);
    if(block_1==0) continue;

    block_2 = get_target_block(blocks[i]);

    if(block_2==0) continue;

    ret += update_ret(block_1, block_2);
  }

	return ret;
}
