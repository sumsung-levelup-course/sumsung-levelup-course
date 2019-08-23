// 이문제는 메모리와 시간에서 굉장히 타이트합니다.
// 해쉬 4배열합을 20만이상 쓰게 되면 시간제한에 걸립니다. 처음엔 [20][11][40][30] 으로 했는데 힘들더군요. 
// 메모리도 테스트 케이스 마다 전부 초기화 해줘야 제한에 안걸립니다.

struct node {
	// 다음 위치
	node *next;
	int age;       // 0 ~ 19
	int passenger; // 2 ~ 12
	int engine;    // 1000 ~ 4999
	int price;     // 10000 ~ 39999
};
// 꼬리
node *tail;
// 해쉬 구조 
node *arr[20][11][20][30];
// 환불 해쉬
node *refu[20000];
// 최초 체크
bool st = false;
// S ~ E 조건
// index 주문번호
int S[4], E[4], index;

// 초기설정
void init() {
	tail = new node;
	for (register int i = 0; i < 20; i++) {
		for (register int j = 0; j < 11; j++) {
			for (register int p = 0; p < 20; p++) {
				for (register int q = 0; q < 30; q++) {
					arr[i][j][p][q] = new node;
					arr[i][j][p][q]->next = tail;
				}
			}
		}
	}
	for (register int i = 0; i < 20000; i++) {
		refu[i] = new node;
		refu[i]->next = tail;
	}
	st = true;
	index = -1;

	return;
}
// 차 입고
void buy(CAR car) {
	if (!st)init();
	node *fr = arr[car.age][car.passenger - 2][(car.engine - 1000) / 200][(car.price - 10000) / 1000];
	node *temp = fr;
	node *past;
	while (temp != tail) {
		past = temp;
		temp = temp->next;
	}
	node *date = new node;
	date->age = car.age;
	date->engine = car.engine;
	date->passenger = car.passenger;
	date->price = car.price;
	date->next = tail;
	past->next = date;
}

// 판매 조건 
void filter_by_age(int from, int to) {
	if (from < to)S[0] = from, E[0] = to;
	else S[0] = to, E[0] = from;
}
void filter_by_passenger(int from, int to) {
	if (from < to)S[1] = from, E[1] = to;
	else S[1] = to, E[1] = from;
}
void filter_by_engine(int from, int to) {
	if (from < to)S[2] = from, E[2] = to;
	else S[2] = to, E[2] = from;
}
void filter_by_price(int from, int to) {
	if (from < to)S[3] = from, E[3] = to;
	else S[3] = to, E[3] = from;
}

// 판매
int sell(void) {
	index++;
	node *now = refu[index];

	for (register int i = S[0]; i <= E[0]; i++) {
		for (register int j = S[1] - 2; j <= E[1] - 2; j++) {
			for (register int p = (S[2] - 1000) / 200; p <= (E[2] - 1000) / 200; p++) {
				for (register int q = (S[3] - 10000) / 1000; q <= (E[3] - 10000) / 1000; q++) {
					
					node *past = arr[i][j][p][q];
					node *temp = past->next;
					while (temp != tail) {
						// 판매조건 일치
						if (temp->engine >= S[2] && temp->engine <= E[2] && temp->price >= S[3] && temp->price <= E[3]) {
							// 환불 기록
							node *sol = new node;
							sol->age = temp->age;
							sol->engine = temp->engine;
							sol->passenger = temp->passenger;
							sol->price = temp->price;
							sol->next = tail;
							now->next = sol;
							now = sol;
							// 해당 차 삭제
							past->next = temp->next;
							temp = temp->next;
						}
						// 판매조건 불일치
						else {
							past = temp;
							temp = temp->next;
						}
					}
				}
			}
		}
	}
	return index;
}
// 환불 재입고
extern void refund(int order_number) {
	CAR car;

	node *temp = refu[order_number]->next;
	while (temp != tail) {
		car.age = temp->age;
		car.passenger = temp->passenger;
		car.engine = temp->engine;
		car.price = temp->price;
		buy(car);
		temp = temp->next;
	}

	return;
}
// 재고 비움 및 메모리 삭제
extern int  empty(void) {
	int sum = 0;
	for (register int i = 0; i < 20; i++) {
		for (register int j = 0; j < 11; j++) {
			for (register int p = 0; p < 20; p++) {
				for (register int q = 0; q < 30; q++) {
					node *temp = arr[i][j][p][q]->next;
					while (temp != tail) {
						sum++;
						temp = temp->next;
					}
				}
			}
		}
	}
	for (register int i = 0; i <= index; i++) {
		node *temp = refu[i];
		node *next = temp->next;
		while (next != tail) {
			delete(temp);
			temp = next;
			next = temp->next;
		}
	}

	st = false;
	return sum;
}
