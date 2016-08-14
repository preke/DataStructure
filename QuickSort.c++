# include <iostream>
# include <algorithm>
using namespace std;

int Partition(int* a, int low, int high) {
	int pivot = a[high];
	int i = low - 1;
	//大的不动，小的交换
	for (int j = low; j < high; j++) {
		if (a[j] > pivot) {
			//pass
		} else {
			i ++;
			swap(a[i], a[j]);
		}
	}
	swap(a[i + 1], a[high]);
	return i+1;
}

int Partition_1(int* a, int low, int high) {
	int pivot = high;
	int index = low;
	while(1) {
		if (pivot > index) {
			if (a[pivot] < a[index]) {
				swap(a[pivot], a[index]);
				swap(pivot, index);	
				index --;
			} else {
			  index ++;	
			}
		} else if (pivot < index) {
			if (a[pivot] > a[index]) {
				swap(a[pivot], a[index]);
				swap(pivot, index);	
				index ++;
			} else {
			  index --;	
			}
		}
		else break;
	}
	return pivot;
}


void QuickSort(int* a, int low, int high) {
	if (low >= high)	return;

	int mid = Partition_1(a, low, high);
	QuickSort(a, low, mid - 1);
	QuickSort(a, mid + 1, high);
}

int a[100];
int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i ++) 	cin >> a[i];

	QuickSort(a, 0, n-1);
	for (int i = 0; i < n; i ++) 	cout << a[i] << " ";
	cout << endl;	
	

	return 0;
}