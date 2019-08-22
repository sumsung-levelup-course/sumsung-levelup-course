// #include <cstdio>
const int MAX_CHAR=21;
const int MAX_NODE=27001;
const int ROOT=0;
struct node{
  char name[MAX_CHAR];
  int child_num;
  node* next;
  node* prev;
  node* parent;
  node* child;
};

int node_idx;
node* cur_state;
node nodes[MAX_NODE];

// void print_node(){
//   printf("CurFolderName:%s\n",cur_state->name);
//   for(int i=0;i<MAX_NODE;i++){
//     if(nodes[i].parent!=0){
//       printf("Name: %s\tChildNum: %d\t ParentName:%s\t",nodes[i].name,nodes[i].child_num,nodes[i].parent->name);
//       printf("PrevName: %s\t",nodes[i].prev->name);
//       printf("NextName: %s\t",nodes[i].next->name);
//       printf("ChildName: %s\t",nodes[i].child->name);
//       printf("\n");
//     }
//   }
//   printf("===============================\n");
// }


int my_strlen(char* str){
  int idx=0;
  while(str[idx] != 0) idx += 1;
  return idx;
}

void my_strcpy(char* dst, char* src){
  int idx=0;
  while(src[idx] != 0){
    dst[idx] = src[idx];
    idx+=1;
  }
  dst[idx] = '\0';
}

int my_strcmp(char* str1, char* str2){
  int idx=0;
  while(str2[idx]){
    if(str1[idx] != str2[idx]) break;
    idx += 1;
  }
  return str1[idx] - str2[idx];
}

int my_strcmp_sub(char* star, char* str2){
  int len = my_strlen(star);
  int i=0;
  for(i=0;i<len-2;i++){
    if(star[i] != str2[i]) break;
  }
  return star[i] - str2[i];
}

node* find_str(node* cur_folder,char* keyword){
  node* target;
  node* cur = cur_folder->child;
  while(cur){
    if(my_strcmp(keyword,cur->name) == 0){
      target = cur;
      return target;
    }
    cur = cur->next;
  }
  return 0;
}

node* find_sub(node* cur_folder,char* keyword){
  node* target=0;
  node* cur =cur_folder->child;
  while(cur){
    if(my_strcmp_sub(keyword,cur->name) == 0){
      if(target == 0){
        target = cur;
      }
      else {
        if(my_strcmp(cur->name,target->name) < 0){
          target = cur;
        }
      }
    }
    cur = cur->next;
  }
  return target;
}

node* find_star(node* cur_folder){
  node* target=0;
  node* cur = cur_folder->child;
  while(cur){
    if(target==0){
      target = cur;
    }
    else{
      if(my_strcmp(cur->name,target->name)<0){
        target = cur;
      }
    }
    cur = cur->next;
  }
  return target;
}

int remove_all(node* cur_folder){
  int ret = cur_folder->child_num;
  node* child = cur_folder->child;
  node* next;
  while(child){
    next = child->next;
    ret += remove_all(child);
    child = next;
  }
  if(cur_folder->prev){
    cur_folder->prev->next = cur_folder->next;
  }
  else{
    // head
    cur_folder->parent->child = cur_folder->next;
  }

  if(cur_folder->next){
    cur_folder->next->prev = cur_folder->prev;
  }

  cur_folder->child_num=0;
  cur_folder->child=0;
  cur_folder->next=0;
  cur_folder->parent=0;
  cur_folder->prev=0;
  return ret;
}

int remove_star(node* cur_folder){
  int ret = cur_folder->child_num;
  node* child = cur_folder->child;
  node* next;
  while(child){
    next = child->next;
    ret += remove_all(child);
    child = next;
  }

  cur_folder->child=0;
  cur_folder->child_num=0;
  return ret;
}

int remove_str(node* cur_folder, char* keyword){
  int ret=0;
  node* target = find_str(cur_folder,keyword);
  // find_str(cur_folder,keyword,target);
  if(target){
    ret = remove_all(target) + 1;
    cur_folder->child_num-=1;
  }
  return ret;
}

int remove_sub(node* cur_folder, char* keyword){
  int ret=0;
  node* target = find_sub(cur_folder,keyword);
  while(target){
    ret += (remove_all(target) + 1);
    cur_folder->child_num -= 1;
    target = find_sub(cur_folder,keyword);
  }
  return ret;
}

int find_star_all(node* cur_folder){
  int ret = cur_folder->child_num;
  node* child = cur_folder->child;
  while(child){
    ret += find_star_all(child);
    child = child->next;
  }

  return ret;
}
int find_sub_all(node* cur_folder, char* keyword){
  int ret = 0;
  node* child = cur_folder->child;
  while(child){
    if(my_strcmp_sub(keyword,child->name) == 0){
      ret += 1;
    }
    ret += find_sub_all(child,keyword);
    child = child->next;
  }
  return ret;
}
int find_str_all(node* cur_folder, char* keyword){
  int ret=0;
  node* child = cur_folder->child;
  while(child){
    if(my_strcmp(keyword,child->name) == 0){
      ret += 1;
    }
    ret += find_str_all(child,keyword);
    child = child->next;
  }
  return ret;
}


void init()
{
  node_idx=1;
  nodes[ROOT].name[0] = '/';
  nodes[ROOT].name[1] = 0;
  nodes[ROOT].child_num=0;
  nodes[ROOT].next=0;
  nodes[ROOT].prev=0;
  nodes[ROOT].child=0;
  nodes[ROOT].parent=&nodes[ROOT];
  cur_state = &nodes[ROOT];
  for(int i=1;i<MAX_NODE;i++){
    nodes[i].child_num=0;
    nodes[i].next=0;
    nodes[i].prev=0;
    nodes[i].parent=0;
    nodes[i].child=0;
  }
}
void make(char keyword[])
{
  // printf("Make %s\n",keyword);
  // print_node();
  if(find_str(cur_state,keyword)) return;

  if(cur_state->child == 0){
    my_strcpy(nodes[node_idx].name,keyword);
    nodes[node_idx].child_num = 0;
    nodes[node_idx].next = 0;
    nodes[node_idx].prev = 0;
    nodes[node_idx].parent = cur_state;
    nodes[node_idx].child = 0;
    cur_state->child = &nodes[node_idx++];
    cur_state->child_num +=1;
  }
  else{
    my_strcpy(nodes[node_idx].name,keyword);
    nodes[node_idx].child_num = 0;
    nodes[node_idx].next = cur_state->child;
    cur_state->child->prev = &nodes[node_idx];
    nodes[node_idx].prev = 0;
    nodes[node_idx].parent = cur_state;
    nodes[node_idx].child = 0;
    cur_state->child = &nodes[node_idx++];
    cur_state->child_num +=1;
  }
}
void change(char keyword[])
{
  // printf("Change %s\n",keyword);
  // print_node();
  int len = my_strlen(keyword);
  node* target;
  if(keyword[0] == '/'){
    cur_state = &nodes[ROOT];
  }
  else if(keyword[0] == '.' && keyword[1] == '.'){
    cur_state = cur_state->parent;
  }
  else if(keyword[0] == '*'){
    target = find_star(cur_state);
    if(target){
      cur_state = target;
    }
  }
  else if(keyword[len-1] == '*'){
    target = find_sub(cur_state,keyword);
    if(target){
      cur_state = target;
    }
  }
  else{
    target = find_str(cur_state,keyword);
    if(target){
      cur_state = target;
    }
  }
}
int remove(char keyword[])
{
  // printf("Remove %s\n",keyword);
  // print_node();
  int len = my_strlen(keyword);
  int ret =0;
	if(keyword[0] == '*'){
    ret = remove_star(cur_state);
  }
  else if(keyword[len-1] == '*'){
    ret = remove_sub(cur_state,keyword);
  }
  else{
    ret = remove_str(cur_state,keyword);
  }

	return ret;
}
int find(char keyword[])
{
  // printf("Find %s\n",keyword);
  // print_node();
	int len = my_strlen(keyword);
  int ret =0;
	if(keyword[0] == '*'){
    ret = find_star_all(cur_state);
  }
  else if(keyword[len-1] == '*'){
    ret = find_sub_all(cur_state,keyword);
  }
  else{
    ret = find_str_all(cur_state,keyword);
  }

	return ret;
}

