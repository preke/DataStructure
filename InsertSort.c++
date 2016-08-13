# include <iostream>
using namespace std;


void InsertSort(int* a, int n) {
	int j, k;
	for (int i = 1; i < n; i ++) {
		j = i - 1;
		k = a[i]; //防止a[i]在下面的操作中被覆盖掉

		while(j >= 0 && k < a[j]) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = k;
	}
}


int a[100];
int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i ++) cin >> a[i];
	//验证算法部分
	InsertSort(a, n);	
	for (int i = 0; i < n; i ++) cout << a[i] << " ";
	cout << endl;
}

