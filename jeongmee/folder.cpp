const int MAX_CHAR = 21;
const int MAX_NUM = 270001;
const int ROOT = 0;
const int NONE = -1;

struct Node {
	char name[MAX_CHAR];
	int parent;
	int first_child;
	int num_child;
	int prev;
	int next;
};

Node d[MAX_NUM];
int cur_folder = 0;
int idx = 0;

void _strcpy(char* str1, char* str2) {
	int i = 0;
	while (str2[i]) {
		str1[i] = str2[i];
		i++;
	}
	str1[i] = '\0';
}

int _strcmp(char* str1, char* str2) {
	int i = 0;
	while (str1[i]) {
		if (str1[i] != str2[i]) break;
		i++;
	}
	return str1[i] - str2[i];
}

int _strcmp_pre(char* str1, char* str2 , int len) { //접두어 
	int i = 0;
	for (i = 0; i < len; i++) {
		if (str1[i] != str2[i]) break;
	}

	if (i == len) return str1[i - 1] - str2[i - 1];
	return str1[i] - str2[i];
}

int _strlen(char* str) {
	int i = 0;
	while (str[i]) i++;
	return i;
}

int isExist(int cur, char keyword[]) {
	int ret = 0;
	int child = d[cur].first_child;

	while (child != NONE) {
		if (!_strcmp(d[child].name, keyword)) return child;
		child = d[child].next;
	}
	return ret;
}

int search_star(int cur) {
	char child_name[MAX_CHAR];
	int child = d[cur].first_child;
	if (child == NONE) return 0;

	int ret = child;
	_strcpy(child_name, d[child].name);

	while (child != NONE) {
		if (_strcmp(child_name, d[child].name) > 0) {
			_strcpy(child_name, d[child].name);
			ret = child;
		}
		child = d[child].next;
	}
	return ret;
}

int search_pre(int cur, char keyword[], int len) {
	char child_name[MAX_CHAR];
	int child = d[cur].first_child;
	if (child == NONE) return 0;
	
  int ret = 0;
	while (child != NONE) {
		if (_strcmp_pre(d[child].name, keyword, len) == 0) {
			if (ret == 0) {
				_strcpy(child_name, d[child].name);
				ret = child;
			}
			else {
				if (_strcmp(child_name, d[child].name) > 0) {
					_strcpy(child_name, d[child].name);
					ret = child;
				}
			}
		}
		child = d[child].next;
	}
	return ret;
}

int add_child(int cur) {
	int ret = d[cur].num_child;
	int child = d[cur].first_child;

	while (child != NONE) {
		ret += add_child(child);
		child = d[child].next;
	}
	return ret;
}

int remove_star(int cur) {
	int ret = d[cur].num_child;
	int child = d[cur].first_child;

	while (child != NONE) {
		ret += add_child(child);
		child = d[child].next;
	}

	d[cur].first_child = NONE;
	d[cur].num_child = 0;
	return ret;
}

int remove_pre(int cur, char keyword[], int len) {
	int ret = 0;
	int child = d[cur].first_child;

	while (child != NONE) {
		int tmp = d[child].next;
		if (_strcmp_pre(d[child].name, keyword, len) == 0) {
			d[cur].num_child -= 1;
			ret += add_child(child) + 1;

			int child_prev = d[child].prev;
			if (child_prev == NONE) {
				d[cur].first_child = d[child].next;
				if (tmp != NONE) d[tmp].prev = NONE;
			}
			else {
				d[child_prev].next = d[child].next;
				if (tmp != NONE) d[tmp].prev = child_prev;
			}
		}
		child = tmp;
	}
	return ret;
}

int remove_str(int cur, char keyword[]) {
	int ret = 0;
	int child = d[cur].first_child;

	while (child != NONE) {
		int tmp = d[child].next;
		if (_strcmp(d[child].name, keyword) == 0) {
			d[cur].num_child -= 1;
			ret += add_child(child) + 1;

			int child_prev = d[child].prev;
			if (child_prev == NONE) {
				d[cur].first_child = d[child].next;
				if (tmp != NONE) d[tmp].prev = NONE;
			}
			else {
				d[child_prev].next = d[child].next;
				if (tmp != NONE) d[tmp].prev = child_prev;
			}
			break;
		}
		child = tmp;
	}
	return ret;
}

int find_star(int cur) {
	int ret = d[cur].num_child;
	int child = d[cur].first_child;

	while (child != NONE) {
		ret += find_star(child);
		child = d[child].next;
	}
	return ret;
}

int find_pre(int cur, char keyword[], int len) {
	int ret = 0;
	int child = d[cur].first_child;

	while (child != NONE) {
		if (_strcmp_pre(d[child].name, keyword, len) == 0) ret += 1;
		ret += find_pre(child, keyword, len);
		child = d[child].next;
	}
	return ret;
}

int find_str(int cur, char keyword[]) {
	int ret = 0;
	int child = d[cur].first_child;

	while (child != NONE) {
		if (_strcmp(d[child].name, keyword) == 0) ret += 1;
		ret += (find_str(child, keyword));
		child = d[child].next;
	}
	return ret;
}

void init()
{
	d[ROOT].name[0] = '/';
	d[ROOT].first_child = NONE;
	d[ROOT].num_child = 0;
	d[ROOT].parent = ROOT;
	d[ROOT].next = NONE;
	d[ROOT].prev = NONE;
	cur_folder = ROOT;
	idx = 1;
}

void make(char keyword[])
{
	Node& cur = d[cur_folder];
	int child = cur.first_child;
	if (isExist(cur_folder, keyword)) return;

	Node& _node = d[idx];
	if (child != NONE) d[child].prev = idx;

	_strcpy(_node.name, keyword);
	_node.parent = cur_folder;
	_node.first_child = NONE;
	_node.next = child;
	_node.prev = NONE;
	_node.num_child = 0;

	cur.first_child = idx;
	cur.num_child += 1;
	idx += 1;
}

void change(char keyword[])
{
	if (keyword[0] == '/') {
		cur_folder = ROOT;
		return;
	}
	else if (keyword[0] == '.' && keyword[1] == '.') {
		cur_folder = d[cur_folder].parent;
		return;
	}
	else if (keyword[0] == '*') {
		int tmp = search_star(cur_folder);
		if (tmp) cur_folder = tmp;
		return;
	}
	else if (keyword[_strlen(keyword) - 1] == '*') {
		int tmp = search_pre(cur_folder, keyword, _strlen(keyword) - 1);
		if (tmp) cur_folder = tmp;
		return;
	}
	else {
		int tmp = isExist(cur_folder, keyword);
		if (tmp) cur_folder = tmp;
	}
}

int remove(char keyword[])
{
	int ret = 0;

	if (keyword[0] == '*') {
		ret = remove_star(cur_folder);
	}
	else if (keyword[_strlen(keyword) - 1] == '*') {
		ret = remove_pre(cur_folder, keyword, _strlen(keyword) - 1);
	}
	else {
		ret = remove_str(cur_folder, keyword);
	}
	return ret;
}

int find(char keyword[])
{
	int ret = 0;

	if (keyword[0] == '*') {
		ret = find_star(cur_folder);
	}
	else if (keyword[_strlen(keyword) - 1] == '*') {
		ret = find_pre(cur_folder, keyword, _strlen(keyword) - 1);
	}
	else {
		ret = find_str(cur_folder, keyword);
	}
	return ret;
}
