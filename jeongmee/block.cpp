const int MAX_NUM = 30000;
const int NONE = -1;
const int KEY = 4304;

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
Node table[KEY + 1];
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
	int n = 1;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ret += n * (matrix[i][j]);
			n *= 3;
		}
	}
	return ret;
}

int rotate(int n, int matrix[4][4]) {
	int tmp[4][4], tmp2[4][4];
	n += 1;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tmp2[i][j] = matrix[i][j];
		}
	}

	while (n) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				tmp[j][3 - i] = tmp2[i][j];
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				tmp2[i][j] = tmp[i][j];
			}
		}
		n-=1;
	}
	return find_idx(tmp);
}

int isExist(int idx, int block) {
	int ret = NONE;
	int _max = 0;
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
			if (ret == NONE)
			{
				ret = ptr->idx;
				_max = d[ptr->idx]._max + d[idx].base;
			}
			else {
				if (_max < (d[ptr->idx]._max + d[idx].base)) {
					ret = ptr->idx;
					_max = d[ptr->idx]._max + d[idx].base;
				}
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
			list[i][j].next = 0;
		}
	}

	for (i = 0; i <= KEY; i++) {
		table[i].idx = NONE;
		table[i].next = 0;
	}

	for (i = 0; i < MAX_NUM; i++) {
		int matrix[4][4];
		find_base(i, module[i]);

		for (int i1 = 0; i1 < 4; i1++) {
			for (int i2 = 0; i2 < 4; i2++) {
				matrix[i1][i2] = module[i][i1][i2] - d[i].base;
			}
		}

		d[i].block = find_idx(matrix);
		d[i].check = false;
		
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
				int _max = 0, _maxId = NONE, idx = NONE;
				int matrix[4][4];
				for (int i1 = 0; i1 < 4; i1++) {
					for (int i2 = 0; i2 < 4; i2++) {
						matrix[i1][i2] = d[ptr->idx]._max - module[ptr->idx][i1][i2];
					}
				}
				int block = find_idx(matrix);
				idx = isExist(ptr->idx, block);

				if (idx != NONE) {
					_maxId = idx;
					_max = d[idx]._max + d[ptr->idx].base;
				}

				for (int i1 = 0; i1 < 3; i1++) {
					idx = NONE;
					block = rotate(i1, matrix);
					idx = isExist(ptr->idx, block);

					if (idx != NONE) {
						if (_maxId == NONE ) {
							_maxId = idx;
							_max = d[idx]._max + d[ptr->idx].base;
						}
						else {
							if (_max < (d[idx]._max + d[ptr->idx].base)) {
								_maxId = idx;
								_max = d[idx]._max + d[ptr->idx].base;
							}
						}
					}
				}
				if (_maxId != NONE) {
					d[_maxId].check = true;
					d[ptr->idx].check = true;
					ret += _max;
				}
				ptr = ptr->next;
			}
		}
	}
	return ret;
}
