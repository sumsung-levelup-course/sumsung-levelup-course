
#include <cstdio>
typedef long long ll;

const int MAX_N = 200001;
//const ll INF = 1000000000000000;
const ll INF = 1000000000;
const int MAX_NODE = 1000001;
const int MAX_HEAP = MAX_NODE * 10;

struct edge {
	int idx;
	ll value;
};

struct node {
	edge road;
	node* next;
};

struct list {
	node* head;
	void add(edge road);
};

//vector<node> adj[MAX_N];
int is_visit[MAX_N];
int node_idx = 0;
int heap_size = 0;
int n = 0;
int m = 0;
ll dist[MAX_N];
list adj[MAX_N];
edge path[MAX_N];
node nodes[MAX_NODE];
edge min_heap[MAX_HEAP];



void list::add(edge road) {
	node* tmp = head;
	head = &nodes[node_idx++];
	head->road = road;
	head->next = tmp;
}

void heap_push(edge road) {
	if (heap_size + 1 > MAX_HEAP) {
		/*while (1) {
			printf("Queue is full\n");
		}*/
		return;
	}

	min_heap[heap_size] = road;
	int cur = heap_size;
	while (cur > 0 && min_heap[cur].value < min_heap[(cur - 1) / 2].value) {
		edge tmp = min_heap[(cur - 1) / 2];
		min_heap[(cur - 1) / 2] = min_heap[cur];
		min_heap[cur] = tmp;
		cur = (cur - 1) / 2;
	}

	heap_size += 1;
}

int is_empty() {
	if (heap_size <= 0) {
		return 1;
	}

	return 0;
}

edge heap_pop() {
	edge ret = min_heap[0];
	heap_size -= 1;

	min_heap[0] = min_heap[heap_size];

	int cur = 0;
	while (cur * 2 + 1 < heap_size) {
		int child;
		if (cur * 2 + 2 == heap_size) {
			child = cur * 2 + 1;
		}
		else {
			child = min_heap[cur * 2 + 1].value < min_heap[cur * 2 + 2].value ? cur * 2 + 1 : cur * 2 + 2;
		}

		if (min_heap[cur].value < min_heap[child].value) {
			break;
		}

		edge tmp = min_heap[cur];
		min_heap[cur] = min_heap[child];
		min_heap[child] = tmp;
	}

	return ret;
}


void init() {
	for (int i = 0; i < MAX_N; i++) {
		adj[i].head = 0;
		dist[i] = INF;
		path[i].value = INF;
		path[i].idx = 0;
		is_visit[i] = 0;
	}
	n = 0;
	m = 0;
	node_idx = 0;
	heap_size = 0;
}
struct cmp {
	bool operator()(edge a, edge b) {
		return a.value > b.value;
	}

};


void dijikstra() {

	dist[1] = 0;
	path[1].idx = 1;
	path[1].value = 0;
	heap_push(edge{ 1,0 });
	while (!is_empty()) {
		edge cur = heap_pop();

		if (is_visit[cur.idx]) continue;
		is_visit[cur.idx] = 1;

		if (cur.value > dist[cur.idx]) continue;

		dist[cur.idx] = cur.value;

		//int len = adj[cur.idx].size();
		node* nxt = adj[cur.idx].head;
		while (nxt != 0) {
			edge nxt_road = nxt->road;
			ll cur_value = nxt_road.value;
			if (is_visit[nxt_road.idx]) {
				nxt = nxt->next;
				continue;
			}
			nxt_road.value = dist[cur.idx] + nxt_road.value;
			if (dist[nxt_road.idx] >= nxt_road.value) {
				dist[nxt_road.idx] = nxt_road.value;
				path[nxt_road.idx].idx = cur.idx;
				path[nxt_road.idx].value = cur_value;
				heap_push(nxt_road);
			}
			nxt = nxt->next;
		}
	}
}

ll sol() {

	dijikstra();
	ll ret = 0;
	for (int i = 1; i <= n; i++) {
		//printf("I:%d Dist:%d Before:%d Before Value:%d ??:%d\n", i, dist[i],path[i].idx, path[i].value, dist[i] - dist[path[i].idx]);
		ret += (dist[i] - dist[path[i].idx]);
	}

	return ret;
}

int main() {
	int test_case = 0;
	ll ans = 0;
	scanf("%d", &test_case);
	for (int i = 0; i < test_case; i++) {
		init();
		scanf("%d %d", &n, &m);
		for (int j = 0; j < m; j++) {
			int src = 0;
			int dst = 0;
			ll value = 0;
			scanf("%d %d %lld", &src, &dst, &value);
			adj[src].add(edge{ dst, value });
			adj[dst].add(edge{ src, value });
		}
		ans = sol();
		printf("#%d %lld\n", i + 1, ans);
	}

	return 0;
}
