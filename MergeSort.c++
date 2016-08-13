# include <iostream>
using namespace std;

# define MAXN 100000000
void Merge(int* a, int p, int q, int r) {
	int n1 = q - p + 1;
	int n2 = r - q;
	int L[n1 + 1], R[n2 + 1];
	for (int i = 0; i < n1; i++) {
		L[i] = a[p+i];
	}
	for (int i = 0; i < n2; i++) {
		R[i] = a[q+i+1];
	}

	L[n1] = R[n2] = MAXN;	//哨兵牌
	//for debug:
	// cout << "debug\n";
	// cout << "p: " << p << " q: " << q << " r: " << r << endl;
	// for (int i = 0; i < n1 + 1; i ++) cout << L[i] << " ";
	// cout << endl;
	// for (int i = 0; i < n2 + 1; i ++) cout << R[i] << " ";
	// cout << endl;

	
	int i = 0, j = 0;
	for (int k = p; k <= r; k ++) {
		if (L[i] > R[j]) {
			a[k] = R[j];
			j++;
		} else {
			a[k] = L[i];
			i++;
		}
	}
}

void MergeSort(int* a, int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;
		MergeSort(a, p, q);
		MergeSort(a, q + 1, r);
		Merge(a, p, q, r);
	}
}

int a[100];
int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i ++) cin >> a[i];
	//验证算法部分
	MergeSort(a,0,n-1);
	cout << "ans:\n";
	for (int i = 0; i < n; i ++) cout << a[i] << " ";
	cout << endl;
}

