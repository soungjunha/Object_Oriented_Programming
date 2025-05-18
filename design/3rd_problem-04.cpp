#include <iostream>
using namespace std;

// 컵 이동 경로를 출력하는 재귀 함수
// n: 옮겨야 할 컵의 개수
// from: 출발 지대 번호
// to: 도착 지대 번호
// via: 보조 지대 번호
void move(int n, int from, int to, int via) {
	if (n == 1) {
		cout << from << " " << to << "\n";
		return;
	}

	move(n - 1, from, via, to);

	cout << from << " " << to << "\n";

	move(n - 1, via, to, from);
}

int main() {
	int N;
	cin >> N;

	cout << (1 << N) - 1 << "\n";

	move(N, 1, 3, 2);

	return 0;
}
