#define CUBE_SIZE   3
#define FRONT       0
#define BACK        1
#define UP          2
#define DOWN        3
#define LEFT        4
#define RIGHT       5

extern void rotate(int face, bool clockwise);


struct emp {
	// 6면 숫자
	int data[6];
	// 바뀐 순서
	int from[5];
	// 바뀐 횟수
	int index;
}cnt[300000];

// 최초 실행여부
bool st = false;
// cnt의 크기
int sz;
// 최적횟수 및 정답기록
int min, ans[10];

void transform(int temp[6][3][3], int face, bool clockwise) {
	int preCube[6][CUBE_SIZE][CUBE_SIZE];

	register int s, i, j;
	for (s = 0; s < 6; ++s)
		for (i = 0; i < CUBE_SIZE; ++i)
			for (j = 0; j < CUBE_SIZE; ++j)
				preCube[s][i][j] = temp[s][i][j];

	if (clockwise) {
		for (i = 0; i < CUBE_SIZE; ++i)
			for (j = 0; j < CUBE_SIZE; ++j)
				temp[face][j][CUBE_SIZE - 1 - i] = preCube[face][i][j];
	}
	else {
		for (i = 0; i < CUBE_SIZE; ++i)
			for (j = 0; j < CUBE_SIZE; ++j)
				temp[face][CUBE_SIZE - 1 - j][i] = preCube[face][i][j];
	}

	switch (face)
	{
	case FRONT:
		if (clockwise) {
			temp[UP][2][0] = preCube[LEFT][2][2];
			temp[UP][2][1] = preCube[LEFT][1][2];
			temp[UP][2][2] = preCube[LEFT][0][2];

			temp[RIGHT][0][0] = preCube[UP][2][0];
			temp[RIGHT][1][0] = preCube[UP][2][1];
			temp[RIGHT][2][0] = preCube[UP][2][2];

			temp[DOWN][0][0] = preCube[RIGHT][2][0];
			temp[DOWN][0][1] = preCube[RIGHT][1][0];
			temp[DOWN][0][2] = preCube[RIGHT][0][0];

			temp[LEFT][0][2] = preCube[DOWN][0][0];
			temp[LEFT][1][2] = preCube[DOWN][0][1];
			temp[LEFT][2][2] = preCube[DOWN][0][2];
		}
		else {
			temp[UP][2][0] = preCube[RIGHT][0][0];
			temp[UP][2][1] = preCube[RIGHT][1][0];
			temp[UP][2][2] = preCube[RIGHT][2][0];

			temp[RIGHT][0][0] = preCube[DOWN][0][2];
			temp[RIGHT][1][0] = preCube[DOWN][0][1];
			temp[RIGHT][2][0] = preCube[DOWN][0][0];

			temp[DOWN][0][0] = preCube[LEFT][0][2];
			temp[DOWN][0][1] = preCube[LEFT][1][2];
			temp[DOWN][0][2] = preCube[LEFT][2][2];

			temp[LEFT][0][2] = preCube[UP][2][2];
			temp[LEFT][1][2] = preCube[UP][2][1];
			temp[LEFT][2][2] = preCube[UP][2][0];
		}
		break;
	case BACK:
		if (clockwise) {
			temp[UP][0][2] = preCube[RIGHT][2][2];
			temp[UP][0][1] = preCube[RIGHT][1][2];
			temp[UP][0][0] = preCube[RIGHT][0][2];

			temp[LEFT][0][0] = preCube[UP][0][2];
			temp[LEFT][1][0] = preCube[UP][0][1];
			temp[LEFT][2][0] = preCube[UP][0][0];

			temp[DOWN][2][2] = preCube[LEFT][2][0];
			temp[DOWN][2][1] = preCube[LEFT][1][0];
			temp[DOWN][2][0] = preCube[LEFT][0][0];

			temp[RIGHT][0][2] = preCube[DOWN][2][2];
			temp[RIGHT][1][2] = preCube[DOWN][2][1];
			temp[RIGHT][2][2] = preCube[DOWN][2][0];
		}
		else {
			temp[UP][0][2] = preCube[LEFT][0][0];
			temp[UP][0][1] = preCube[LEFT][1][0];
			temp[UP][0][0] = preCube[LEFT][2][0];

			temp[LEFT][0][0] = preCube[DOWN][2][0];
			temp[LEFT][1][0] = preCube[DOWN][2][1];
			temp[LEFT][2][0] = preCube[DOWN][2][2];

			temp[DOWN][2][2] = preCube[RIGHT][0][2];
			temp[DOWN][2][1] = preCube[RIGHT][1][2];
			temp[DOWN][2][0] = preCube[RIGHT][2][2];

			temp[RIGHT][0][2] = preCube[UP][0][0];
			temp[RIGHT][1][2] = preCube[UP][0][1];
			temp[RIGHT][2][2] = preCube[UP][0][2];
		}
		break;
	case UP:
		if (clockwise) {
			temp[BACK][0][2] = preCube[LEFT][0][2];
			temp[BACK][0][1] = preCube[LEFT][0][1];
			temp[BACK][0][0] = preCube[LEFT][0][0];

			temp[RIGHT][0][2] = preCube[BACK][0][2];
			temp[RIGHT][0][1] = preCube[BACK][0][1];
			temp[RIGHT][0][0] = preCube[BACK][0][0];

			temp[FRONT][0][0] = preCube[RIGHT][0][0];
			temp[FRONT][0][1] = preCube[RIGHT][0][1];
			temp[FRONT][0][2] = preCube[RIGHT][0][2];

			temp[LEFT][0][0] = preCube[FRONT][0][0];
			temp[LEFT][0][1] = preCube[FRONT][0][1];
			temp[LEFT][0][2] = preCube[FRONT][0][2];
		}
		else {
			temp[BACK][0][2] = preCube[RIGHT][0][2];
			temp[BACK][0][1] = preCube[RIGHT][0][1];
			temp[BACK][0][0] = preCube[RIGHT][0][0];

			temp[RIGHT][0][2] = preCube[FRONT][0][2];
			temp[RIGHT][0][1] = preCube[FRONT][0][1];
			temp[RIGHT][0][0] = preCube[FRONT][0][0];

			temp[FRONT][0][0] = preCube[LEFT][0][0];
			temp[FRONT][0][1] = preCube[LEFT][0][1];
			temp[FRONT][0][2] = preCube[LEFT][0][2];

			temp[LEFT][0][0] = preCube[BACK][0][0];
			temp[LEFT][0][1] = preCube[BACK][0][1];
			temp[LEFT][0][2] = preCube[BACK][0][2];
		}
		break;
	case DOWN:
		if (clockwise) {
			temp[FRONT][2][0] = preCube[LEFT][2][0];
			temp[FRONT][2][1] = preCube[LEFT][2][1];
			temp[FRONT][2][2] = preCube[LEFT][2][2];

			temp[RIGHT][2][0] = preCube[FRONT][2][0];
			temp[RIGHT][2][1] = preCube[FRONT][2][1];
			temp[RIGHT][2][2] = preCube[FRONT][2][2];

			temp[BACK][2][2] = preCube[RIGHT][2][2];
			temp[BACK][2][1] = preCube[RIGHT][2][1];
			temp[BACK][2][0] = preCube[RIGHT][2][0];

			temp[LEFT][2][2] = preCube[BACK][2][2];
			temp[LEFT][2][1] = preCube[BACK][2][1];
			temp[LEFT][2][0] = preCube[BACK][2][0];
		}
		else {
			temp[FRONT][2][0] = preCube[RIGHT][2][0];
			temp[FRONT][2][1] = preCube[RIGHT][2][1];
			temp[FRONT][2][2] = preCube[RIGHT][2][2];

			temp[RIGHT][2][0] = preCube[BACK][2][0];
			temp[RIGHT][2][1] = preCube[BACK][2][1];
			temp[RIGHT][2][2] = preCube[BACK][2][2];

			temp[BACK][2][2] = preCube[LEFT][2][2];
			temp[BACK][2][1] = preCube[LEFT][2][1];
			temp[BACK][2][0] = preCube[LEFT][2][0];

			temp[LEFT][2][2] = preCube[FRONT][2][2];
			temp[LEFT][2][1] = preCube[FRONT][2][1];
			temp[LEFT][2][0] = preCube[FRONT][2][0];
		}
		break;
	case LEFT:
		if (clockwise) {
			temp[UP][0][0] = preCube[BACK][2][2];
			temp[UP][1][0] = preCube[BACK][1][2];
			temp[UP][2][0] = preCube[BACK][0][2];

			temp[FRONT][0][0] = preCube[UP][0][0];
			temp[FRONT][1][0] = preCube[UP][1][0];
			temp[FRONT][2][0] = preCube[UP][2][0];

			temp[DOWN][2][0] = preCube[FRONT][2][0];
			temp[DOWN][1][0] = preCube[FRONT][1][0];
			temp[DOWN][0][0] = preCube[FRONT][0][0];

			temp[BACK][0][2] = preCube[DOWN][2][0];
			temp[BACK][1][2] = preCube[DOWN][1][0];
			temp[BACK][2][2] = preCube[DOWN][0][0];
		}
		else {
			temp[UP][0][0] = preCube[FRONT][0][0];
			temp[UP][1][0] = preCube[FRONT][1][0];
			temp[UP][2][0] = preCube[FRONT][2][0];

			temp[FRONT][0][0] = preCube[DOWN][0][0];
			temp[FRONT][1][0] = preCube[DOWN][1][0];
			temp[FRONT][2][0] = preCube[DOWN][2][0];

			temp[DOWN][2][0] = preCube[BACK][0][2];
			temp[DOWN][1][0] = preCube[BACK][1][2];
			temp[DOWN][0][0] = preCube[BACK][2][2];

			temp[BACK][0][2] = preCube[UP][2][0];
			temp[BACK][1][2] = preCube[UP][1][0];
			temp[BACK][2][2] = preCube[UP][0][0];
		}
		break;
	case RIGHT:
		if (clockwise) {
			temp[UP][2][2] = preCube[FRONT][2][2];
			temp[UP][1][2] = preCube[FRONT][1][2];
			temp[UP][0][2] = preCube[FRONT][0][2];

			temp[BACK][0][0] = preCube[UP][2][2];
			temp[BACK][1][0] = preCube[UP][1][2];
			temp[BACK][2][0] = preCube[UP][0][2];

			temp[DOWN][0][2] = preCube[BACK][2][0];
			temp[DOWN][1][2] = preCube[BACK][1][0];
			temp[DOWN][2][2] = preCube[BACK][0][0];

			temp[FRONT][0][2] = preCube[DOWN][0][2];
			temp[FRONT][1][2] = preCube[DOWN][1][2];
			temp[FRONT][2][2] = preCube[DOWN][2][2];
		}
		else {
			temp[UP][2][2] = preCube[BACK][0][0];
			temp[UP][1][2] = preCube[BACK][1][0];
			temp[UP][0][2] = preCube[BACK][2][0];

			temp[BACK][0][0] = preCube[DOWN][2][2];
			temp[BACK][1][0] = preCube[DOWN][1][2];
			temp[BACK][2][0] = preCube[DOWN][0][2];

			temp[DOWN][0][2] = preCube[FRONT][0][2];
			temp[DOWN][1][2] = preCube[FRONT][1][2];
			temp[DOWN][2][2] = preCube[FRONT][2][2];

			temp[FRONT][0][2] = preCube[UP][0][2];
			temp[FRONT][1][2] = preCube[UP][1][2];
			temp[FRONT][2][2] = preCube[UP][2][2];
		}
		break;
	}
}

//cnt 데이터 삽입
void conver(int temp[6][3][3], int x, int S[5]) {
	for (int i = 0; i < 6; i++) {
		int sum = 0;
		for (int j = 0, mul = 1; j < 9; j++, mul *= 6) sum += temp[i][j / 3][j % 3] * mul;
		cnt[sz].data[i] = sum;
	}
	for (int i = 0; i < x; i++) cnt[sz].from[i] = S[i] >= 10 ? S[i] - 10 : S[i] + 10;
	cnt[sz].index = x;
}

// 5번 섞는 모든 경우 12^5 가지
void make_cnt(int x, int S[5]) {
	int temp[6][3][3];
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++)temp[i][j][k] = i;
		}
	}
	for (int i = 0; i < x; i++)transform(temp, S[i] % 10, S[i] / 10);
	sz++;
	conver(temp, x, S);
	if (x == 5)return;
	for (int i = 0; i < 6; i++) {
		S[x] = i;
		make_cnt(x + 1, S);
		S[x] = i + 10;
		make_cnt(x + 1, S);
	}
}

// 대소 비교 a가클경우 0 b가클경우 1
int cnt_comp(emp &a, emp &b) {
	for (register int i = 0; i < 6; i++) {
		if (a.data[i] == b.data[i])continue;
		return a.data[i] < b.data[i];
	}
	return 2;
}
// 퀵 소트
void quickSort(int first, int last)
{
	int pivot, i, j;
	emp t;
	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;

		while (i < j)
		{
			while (cnt_comp(cnt[i], cnt[pivot]) && i < last) i++;
			while (cnt_comp(cnt[pivot], cnt[j]) == 1) j--;
			if (i < j)
			{
				t = cnt[i];
				cnt[i] = cnt[j];
				cnt[j] = t;
			}
		}
		t = cnt[pivot];
		cnt[pivot] = cnt[j];
		cnt[j] = t;

		quickSort(first, j - 1);
		quickSort(j + 1, last);
	}
}
void init() {
	int S[5] = { 0, };
	for (register int i = 0; i < 6; i++)cnt[sz].data[i] = -1e9;
	make_cnt(0, S);
	sz++;
	for (register int i = 0; i < 6; i++)cnt[sz].data[i] = 1e9;
	quickSort(0, sz);
}
// 이분탐색 pos 초과
int low_bound(int x, int l, int r, int pos) {
	while (l < r) {
		int m = (l + r) / 2;
		if (pos > cnt[m].data[x]) l = m + 1;
		else r = m;
	}
	return r;
}

void find_cube(int cube[6][3][3], int x, int S[5]) {
	// 찾기
	int s = 0, e = sz;
	for (register int i = 0; i < 6 && s <= e; i++) {
		int sum = 0;
		for (register int j = 0, mul = 1; j < 9; j++, mul *= 6)sum += cube[i][j / 3][j % 3] * mul;
		int l = low_bound(i, s, e, sum);
		int r = low_bound(i, s, e, sum + 1);
		s = l;
		e = r;
	}
	// 최적값 검색
	for (register int i = s; i < e; i++) {
		if (min > x + cnt[i].index) {
			min = x + cnt[i].index;
			for (register int j = 0; j < x; j++)ans[j] = S[j];
			for (register int j = 0; j < cnt[i].index; j++)ans[x + j] = cnt[i].from[cnt[i].index - 1 - j];
		}
	}
	// 다음 탐색
	if (x == 5)return;
	for (register int i = 0; i < 6; i++) {
		S[x] = i;
		transform(cube, i, 0);
		find_cube(cube, x + 1, S);
		transform(cube, i, 1);

		S[x] = i + 10;
		transform(cube, i, 1);
		find_cube(cube, x + 1, S);
		transform(cube, i, 0);
	}
}
void runtest(int cube[6][CUBE_SIZE][CUBE_SIZE])
{
	if (!st)init(), st = true;
	int S[5] = { 0, };
	min = 1e9;
	find_cube(cube, 0, S);
	for (int i = 0; i < min; i++)rotate(ans[i] % 10, ans[i] / 10);
}
