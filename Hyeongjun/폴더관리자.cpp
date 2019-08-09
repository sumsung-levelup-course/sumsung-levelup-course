const int MAX_NODE = 27001;
const int MAX_CHAR = 21;
const int ROOT = 0;
const int NOT = -1;

struct node {
	char name[MAX_CHAR];
	int parent;
	int child;
	int prev;
	int next;
	int child_num;
};

node folders[MAX_NODE];
int cur_idx = ROOT;
int node_idx = 1;

//void print_folder() {
//
//	printf("Cur Folder:%s\n", folders[cur_idx].name);
//	for (int i = 0; i < node_idx; i++) {
//		node& cur = folders[i];
//		if (folders[192].parent == NOT && i > 192) {
//			int a = 0;
//		}
//
//		if (cur.parent != NOT) {
//			printf("I:%d Name:(%s) parent:%d child:%d prev:%d next:%d child_num:%d\n",
//				i, cur.name, cur.parent, cur.child, cur.prev, cur.next, cur.child_num);
//		}
//		
//	}
//}

void my_strcpy(char* dst, char* src) {
	int idx = 0;
	while (src[idx] != 0) {
		dst[idx] = src[idx];
		idx += 1;
	}
	dst[idx] = '\0';
}

int my_strcmp(char* str1, char* str2) {
	int idx = 0;
	while (str1[idx] != 0) {
		if (str1[idx] != str2[idx]) break;
		idx += 1;
	}

	return str1[idx] - str2[idx];
}

int my_strcmp_sub(char* str, char* keyword, int len) {
	int i = 0;
	for (i = 0; i < len; i++) {
		if (str[i] != keyword[i]) break;
	}

	if (i == len) {
		return str[i - 1] - keyword[i - 1];
	}

	return str[i] - keyword[i];
}

int my_strlen(char* str) {
	int idx = 0;
	while (str[idx] != 0) idx += 1;

	return idx;
}

void init()
{
	char root_name[2] = "/";
	node& root_node = folders[ROOT];
	my_strcpy(root_node.name, root_name);
	root_node.parent = ROOT;
	root_node.child = NOT;
	root_node.prev = NOT;
	root_node.next = NOT;
	root_node.child_num = 0;

	node_idx = 1;
	cur_idx = ROOT;
}

int is_exist(int cur, char keyword[]) {
	int ret = 0;
	int child = folders[cur].child;

	while (child != NOT) {
		if (my_strcmp(folders[child].name, keyword) == 0) return child;
		child = folders[child].next;
	}

	return ret;
}

void make(char keyword[])
{
	node& cur = folders[cur_idx];
	int child = cur.child;

	if (is_exist(cur_idx, keyword)) return;

	node& new_node = folders[node_idx];
	if (child != NOT) {
		folders[child].prev = node_idx;
	}
	my_strcpy(new_node.name, keyword);
	new_node.parent = cur_idx;
	new_node.child = NOT;
	new_node.next = cur.child;
	new_node.prev = NOT;
	new_node.child_num = 0;
	cur.child = node_idx;
	cur.child_num += 1;
	node_idx += 1;
}

int search_star(int cur) {
	int child = folders[cur].child;
	
	if (child == NOT) return 0;

	int ret = child;
	char child_name[MAX_CHAR];
	my_strcpy(child_name, folders[child].name);

	while (child != NOT) {
		if (my_strcmp(child_name, folders[child].name) > 0) {
			my_strcpy(child_name, folders[child].name);
			ret = child;
		}
		child = folders[child].next;
	}
	return ret;
}
int search_sub(int cur, char keyword[], int len) {
	int child = folders[cur].child;

	if (child == NOT) return 0;

	int ret = 0;
	char child_name[MAX_CHAR];
	while (child != NOT) {
		if (my_strcmp_sub(folders[child].name, keyword, len - 1) == 0) {
			if (ret == 0) {
				my_strcpy(child_name, folders[child].name);
				ret = child;
			}
			else {
				if (my_strcmp(child_name, folders[child].name) > 0) {
					my_strcpy(child_name, folders[child].name);
					ret = child;
				}
			}
		}
		child = folders[child].next;
	}

	return ret;
}
int search_str(int cur, char keyword[]) {
	int ret = is_exist(cur, keyword);

	return ret;
}

void change(char keyword[])
{
	if (keyword[0] == '/') {
		cur_idx = 0;
	}
	else if (keyword[0] == '.' && keyword[1] == '.') {
		cur_idx = folders[cur_idx].parent;
	}
	else if (keyword[0] == '*') {
		int tmp = search_star(cur_idx);
		if (tmp) cur_idx = tmp;
	}
	else if (keyword[my_strlen(keyword) - 1] == '*') {
		int tmp = search_sub(cur_idx, keyword, my_strlen(keyword) - 1);
		if (tmp) cur_idx = tmp;
	}
	else {
		int tmp = search_str(cur_idx, keyword);
		if (tmp) cur_idx = tmp;
	}
}

int find_star(int cur) {
	int ret = folders[cur].child_num;
	int child = folders[cur].child;

	while (child != NOT) {
		ret += find_star(child);
		child = folders[child].next;
	}

	return ret;
}
int find_sub(int cur, char keyword[], int len) {
	int ret = 0;
	int child = folders[cur].child;
	while (child != NOT) {
		if (my_strcmp_sub(folders[child].name, keyword, len) == 0) {
			ret += 1;
			//printf("[For Debug]%s\n", folders[child].name);
		}
		ret += find_sub(child, keyword, len);
		child = folders[child].next;
	}

	return ret;
}
int find_str(int cur, char keyword[]) {
	int ret = 0;
	int child = folders[cur].child;
	while (child != NOT) {
		if (my_strcmp(folders[child].name, keyword) == 0) {
			ret += 1;
		}
		ret += find_str(child, keyword);
		child = folders[child].next;
	}

	return ret;
}

int find(char keyword[])
{
	int ret = 0;
	if (keyword[0] == '*') {
		ret = find_star(cur_idx);
	}
	else if (keyword[my_strlen(keyword) - 1] == '*') {
		ret = find_sub(cur_idx, keyword, my_strlen(keyword) - 1);
	}
	else {
		ret = find_str(cur_idx, keyword);
	}

	return ret;
}

int remove_sub_folder(int cur) {
	int ret = folders[cur].child_num;
	int child = folders[cur].child;
	while (child != NOT) {
		int tmp = folders[child].next;
		ret += remove_sub_folder(child);
		child = tmp;
	}

	folders[cur].parent = NOT;
	folders[cur].child = NOT;
	folders[cur].prev = NOT;
	folders[cur].next = NOT;
	folders[cur].child_num = 0;

	return ret;
}

int remove_star(int cur) {
	int ret = folders[cur].child_num;
	int child = folders[cur].child;
	while (child != NOT) {
		int tmp = folders[child].next;
		ret += remove_sub_folder(child);
		child = tmp;
		folders[cur].child_num -= 1;
	}
	folders[cur].child = NOT;

	return ret;
}
int remove_sub(int cur, char keyword[], int len) {
	int ret = 0;
	int child = folders[cur].child;
	
	/*if (cur == 171) {
		int a = 1;
	}*/

	while (child != NOT) {
		int tmp = folders[child].next;
		if (my_strcmp_sub(folders[child].name, keyword, len) == 0) {
			folders[cur].child_num -= 1;
			ret += 1;
			ret += remove_star(child);
			int prev = folders[child].prev;
			if (prev == NOT) {
				folders[cur].child = tmp;
				if (tmp != NOT) {
					folders[tmp].prev = NOT;
				}
			}
			else {
				folders[prev].next = tmp;
				if (tmp != NOT) {
					folders[tmp].prev = prev;
				}
			}
			folders[child].parent = NOT;
			folders[child].prev = NOT;
			folders[child].next = NOT;
			folders[child].child = NOT;
			folders[child].child_num = 0;
		}
		child =tmp;
	}

	return ret;
}
int remove_str(int cur, char keyword[]) {
	int ret = 0;
	int child = folders[cur].child;

	while (child != NOT) {
		int tmp = folders[child].next;
		if (my_strcmp(folders[child].name, keyword) == 0) {
			folders[cur].child_num -= 1;
			ret += 1;
			ret += remove_star(child);
			int prev = folders[child].prev;
			if (prev == NOT) {
				folders[cur].child = tmp;
				if (tmp != NOT) {
					folders[tmp].prev = NOT;
				}
			}
			else {
				folders[prev].next = tmp;
				if (tmp != NOT) {
					folders[tmp].prev = prev;
				}
			}
			folders[child].parent = NOT;
			folders[child].prev = NOT;
			folders[child].next = NOT;
			folders[child].child = NOT;
			folders[child].child_num = 0;
			break;
		}
		child = folders[child].next;
	}

	return ret;
}

int remove(char keyword[])
{
	int ret = 0;
	if (keyword[0] == '*') {
		ret = remove_star(cur_idx);
	}
	else if (keyword[my_strlen(keyword) - 1] == '*') {
		ret = remove_sub(cur_idx, keyword, my_strlen(keyword) - 1);
	}
	else {
		ret = remove_str(cur_idx, keyword);
	}

	return ret;
}
