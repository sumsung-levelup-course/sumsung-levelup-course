#include <iostream>

using namespace std;

struct _stack {
	int top = 0;
	int s[1001][2]; //(type, index)
};

int n;
int b[1001];
_stack st;

void find() {

	for (int i = 0; i < n; i++) {
		if (i == 0) {
			st.s[st.top][0] = b[i];
			st.s[st.top][1] = i;
			st.top++;
		}
		else {
			if (b[i] == 1) {
				st.s[st.top][0] = b[i];
				st.s[st.top][1] = i;
				st.top++;
			}
			else {
				if (st.s[st.top - 1][0] == 1)
				{
					st.top--;
				}
				else {
					st.s[st.top][0] = b[i];
					st.s[st.top][1] = i;
					st.top++;
				}
			}
		}
	}
}

int main() {

	//freopen("sample_input.txt", "r", stdin);
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		
		st.top = 0; int i = 0;
		cin >> n;

		for (i = 0; i < n; i++) {
			char a;
			cin >> a;
			if (a == '(')
				b[i] = 1;
			else
				b[i] = -1;
		}

		if (n % 2) {
			cout << '#' << tc << ' ' << -1 << endl;
			continue;
		}

		find();

		int ans = 0;
		int _ans[10][2];

		//반으로 나눠서 확인하기
		for (i = 0; i < st.top / 2; i++) {
			if (st.s[i][0] == 1) {
				continue;
			}
			else {
				_ans[ans][0] = st.s[i][1];

				while (i < st.top/2 && st.s[i][0] == -1) {
					i++;
				}
				
				_ans[ans][1] = st.s[i - 1][1];
				ans++;

				if (ans > 10) break;
			}
		}

		for (i = st.top/2 ; i < st.top; i++) {
			if (st.s[i][0] == -1) {
				continue;
			}
			else {
				_ans[ans][0] = st.s[i][1];

				while (i < st.top && st.s[i][0] == 1) {
					i++;
				}

				_ans[ans][1] = st.s[i - 1][1];
				ans++;

				if (ans > 10) break;
			}
		}


		if (ans <= 10) {
			cout << '#' << tc << ' ' << ans << endl;


			for (i = 0; i < ans; i++) {
				cout << _ans[i][0] << ' ' << _ans[i][1] << endl;
			}
		}
		else {
			cout << '#' << tc << ' ' << -1 << endl;
		}
	}
	return 0;
}
