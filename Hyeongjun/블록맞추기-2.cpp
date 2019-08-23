const int MAX=30000;
const int MAX_HASH = 30000;
const int INF=987654321;

struct node{
  int block[4][4];
  int block_shape;
  int max_height;
  int min_height;
  int is_use;
  node* next;
};

struct list{
  node* head;
  void add(node* new_node){
    node* tmp = head;
    head = new_node;
    head->next = tmp;
  }
};

struct Idx{
  int idx;
  int block_shape;
};

Idx my_idx[MAX];
list my_hash[MAX_HASH];
node nodes[MAX];

int get_idx(int block_shape){
  int low=0;
  int high=MAX-1;
  int mid=0;

  while(low<high){
    mid = (low + high)/2;
    if(block_shape > my_idx[mid].block_shape){
      low = mid+1;
    }
    else{
      high = mid;
    }
  }

  if(my_idx[high].block_shape != block_shape){
    return -1;
  }

  return my_idx[high].idx;
}

void quick_sort(int first, int last){
  int pivot=0;
  int i=0;
  int j=0;
  node tmp;
  if(first < last){
    pivot = first;
    i = first;
    j = last;
    while(i<j){
      while(nodes[i].max_height <= nodes[pivot].max_height && i < last){
        i++;
      }
      while(nodes[j].max_height > nodes[pivot].max_height){
        j--;
      }
      if(i<j){
        node tmp = nodes[i];
        nodes[i] = nodes[j];
        nodes[j] = tmp;
      }
    }
    tmp = nodes[pivot];
    nodes[pivot] = nodes[j];
    nodes[j] = tmp;

    quick_sort(first, j-1);
    quick_sort(j+1, last);
  }
}
void quick_sort_idx(int first, int last){
  int pivot=0;
  int i=0;
  int j=0;
  Idx tmp;
  if(first < last){
    pivot = first;
    i = first;
    j = last;
    while(i<j){
      while(my_idx[i].block_shape <= my_idx[pivot].block_shape && i < last){
        i++;
      }
      while(my_idx[j].block_shape > my_idx[pivot].block_shape){
        j--;
      }
      if(i<j){
        tmp = my_idx[i];
        my_idx[i] = my_idx[j];
        my_idx[j] = tmp;
      }
    }
    tmp = my_idx[pivot];
    my_idx[pivot] = my_idx[j];
    my_idx[j] = tmp;

    quick_sort_idx(first, j-1);
    quick_sort_idx(j+1, last);
  }
}

void init(){
  for(int i=0;i<MAX_HASH;i++){
    my_hash[i].head=0;
  }
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

void update_hash(){
  int idx=0;
  for(int i=0;i<MAX;i++){
    my_hash[get_idx(nodes[i].block_shape)].add(&nodes[i]);
  }
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

void update_node(int module[][4][4]){
  int min_h = INF;
  int max_h = 0;
  int sum=0;
  for(int i=0;i<MAX;i++){
    min_h=INF;
    max_h=0;
    for(int y=0;y<4;y++){
      for(int x=0;x<4;x++){
        nodes[i].block[y][x] = module[i][y][x];
        if(module[i][y][x] > max_h){
          max_h = module[i][y][x];
        } 
        if(module[i][y][x] < min_h){
          min_h = module[i][y][x];
        }
      }
    }
    for(int y=0;y<4;y++){
      for(int x=0;x<4;x++){
        nodes[i].block[y][x] -= min_h;
      }
    }
    sum = hash_function(nodes[i].block);
    nodes[i].max_height = max_h;
    nodes[i].min_height = min_h;
    nodes[i].block_shape = sum;
    nodes[i].is_use = 0;
  }


  quick_sort(0, MAX-1);
  for(int i=0;i<MAX;i++){
    my_idx[i].idx = i;
    my_idx[i].block_shape = nodes[i].block_shape;
  }
  quick_sort_idx(0, MAX-1);
}

int match(){
  // for(int i=0;i<MAX_HASH;i++){
  //   if(my_hash[i].head && my_hash[i].head->next){
  //     int a = 1;
  //   }
  // }


  int ret =0;
  int target_block[4][4];
  int target_shape=0;
  int match_shape=0;
  // bool is_match=0;
  node* tmp=0;
  node* match_node=0;
  int flag=0;
  int check =0;
  for(int i=MAX-1; i>=0; i--){
    flag=0;
    check = nodes[i].block[0][0];
    if(nodes[i].is_use) continue;

    for(int y=0;y<4;y++){
      for(int x=0;x<4;x++){
        target_block[y][x] = 2 - nodes[i].block[y][x];
        if(check != nodes[i].block[y][x]) flag=1;
      }
    }

    if(flag==0){
      ret += nodes[i].max_height;
      nodes[i].is_use = 1;
      my_hash[get_idx(nodes[i].block_shape)].head = nodes[i].next;
      continue;
    }
    //flip
    for(int y=0;y<4;y++){
      int value = target_block[y][0];
      target_block[y][0] = target_block[y][3];
      target_block[y][3] = value;
      value = target_block[y][1];
      target_block[y][1] = target_block[y][2];
      target_block[y][2] = value;
    }

    match_node=0;

    for(int j=0;j<3;j++){
      int target_idx = get_idx(hash_function(target_block));
      if(target_idx == -1 || target_idx==i){
        rotate(target_block);
        continue;
      }
      tmp = my_hash[target_idx].head;
      if(tmp){
        if(tmp->is_use) {
          rotate(target_block);
          continue;
        }

        if(match_node == 0){
          match_node = tmp;
        }
        else if(match_node->max_height < tmp->max_height){
          match_node = tmp;
        }
      }
      rotate(target_block);  
    }

    if(match_node == 0) continue;
    
    nodes[i].is_use = 1;
    match_node->is_use = 1;
    ret += (nodes[i].max_height + match_node->min_height);
    my_hash[get_idx(nodes[i].block_shape)].head = nodes[i].next;
    my_hash[get_idx(match_node->block_shape)].head = match_node->next;
  }

  return ret;
}


int makeBlock(int module[][4][4]){
  int ret=0;
  init();
  
  update_node(module);
  update_hash();

  ret = match();

	return ret;
}
