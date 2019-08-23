const int MAX_NUM = 30000;
const int NONE = -1;
const int KEY = 4305;

struct Node {
	int idx;
	Node* prev;
	Node* next;

	Node() {
		idx = NONE;
		prev = next = 0;
	}
	Node(int i, Node* ptr) {
		idx = i;
		next = ptr->next;
		prev = ptr;
		ptr->next->prev = ptr->next = this;
	}
};
struct Column {
	bool check;
	int block;
	int base;
	int diff;
	int _max;
};

Node list[9][3];
Node table[KEY];
Column d[MAX_NUM];

void find_base(int idx, int matrix[4][4]) {
	int _min = -1;
	int _max = -1;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (_min == -1 || _min > matrix[i][j]) {
				_min = matrix[i][j];
			}
			if (_max == -1 || _max < matrix[i][j]) {
				_max = matrix[i][j];
			}
		}
	}
	d[idx].base = _min;
	d[idx].diff = _max - _min;
	d[idx]._max = _max;
}

int find_idx(int matrix[4][4]) {
	int ret = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ret = ret * 3 + matrix[i][j];
		}
	}
	return ret;
}

int rotate(int n, int matrix[4][4]) {
	if (n == 0) {
		return find_idx(matrix);
	}
	int tmp[4][4];
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			tmp[j][3 - i] = matrix[i][j];
		}
	}
	return rotate(n - 1, tmp);
}

int isExist(int block) {
	int ret = NONE; //return할 idx 저장
	int _max = NONE;
	Node* ptr = table + block / 10000;
	while (ptr->next != 0) {
		if (ptr->idx == NONE) {
			ptr = ptr->next;
			continue;
		}
		if (d[ptr->idx].block == block) {
			if (d[ptr->idx].check) {
				ptr = ptr->next;
				continue;
			}
			if (_max < d[ptr->idx]._max) {
				ret = ptr->idx;
				_max = d[ptr->idx]._max;
			}
		}
		ptr = ptr->next;
	}
	return ret;
}

int makeBlock(int module[][4][4])
{
	int i = 0, ret = 0;

	//init
	for (i = 0; i < 9; i++) {
		for (int j = 0; j < 3; j++) {
			list[i][j].idx = NONE;
			list[i][j].next = list[i][j].prev = 0;
		}
	}

	for (i = 0; i < KEY; i++) {
		table[i].idx = NONE;
		table[i].next = table[i].prev = 0;
	}

	for (i = 0; i < MAX_NUM; i++) {
		int matrix[4][4];
		d[i].check = false;
		find_base(i, module[i]);

		for (int i1 = 0; i1 < 4; i1++) {
			for (int i2 = 0; i2 < 4; i2++) {
				matrix[i1][i2] = module[i][i1][i2] - d[i].base;
			}
		}

		d[i].block = find_idx(matrix);

		Node* ptr = list[d[i]._max] + d[i].diff;
		if (ptr->next == 0) {
			Node* tmp = new Node();
			tmp->idx = i;
			tmp->prev = ptr;
			ptr->next = tmp;
		}
		else
			new Node(i, ptr);

		ptr = table + d[i].block / 10000;
		if (ptr->next == 0) {
			Node* tmp = new Node();
			tmp->idx = i;
			tmp->prev = ptr;
			ptr->next = tmp;
		}
		else
			new Node(i, ptr);
	}

	for (i = 8; i > 0; i--) {
		for (int j = 0; j < 3; j++) {
			Node* ptr = list[i][j].next;
			while (ptr != 0) {
				if (d[ptr->idx].check) {
					ptr = ptr->next;
					continue;
				}
				//d[ptr->idx].check = true;
				int _max = 0, _maxId = NONE, idx = NONE;
				int matrix[4][4];
				for (int i1 = 0; i1 < 4; i1++) {
					for (int i2 = 0; i2 < 4; i2++) {
						matrix[i1][i2] = d[ptr->idx]._max - module[ptr->idx][i1][i2];
					}
				}
				//flip
				for (int i1 = 0; i1 < 4; i1++) {
					int tmp1 = matrix[i1][0];
					matrix[i1][0] = matrix[i1][3];
					matrix[i1][3] = tmp1;

					tmp1 = matrix[i1][1];
					matrix[i1][1] = matrix[i1][2];
					matrix[i1][2] = tmp1;
				}

				for (int i1 = 0; i1 <= 3; i1++) {
					idx = NONE;
					int block = rotate(i1, matrix);
					idx = isExist(block);

					if (idx != NONE) {
						if (_max < (d[idx].base + d[idx].diff + d[ptr->idx].base)) {
							_maxId = idx;
							_max = d[idx].base + d[idx].diff + d[ptr->idx].base;
						}
					}
				}
				d[ptr->idx].check = true;
				if (_maxId != NONE) {
					d[_maxId].check = true;
					ret += _max;
				}
				ptr = ptr->next;
			}
		}
	}
	return ret;
}
