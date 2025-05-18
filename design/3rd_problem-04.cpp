#include <iostream>
using namespace std;

// �� �̵� ��θ� ����ϴ� ��� �Լ�
// n: �Űܾ� �� ���� ����
// from: ��� ���� ��ȣ
// to: ���� ���� ��ȣ
// via: ���� ���� ��ȣ
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
