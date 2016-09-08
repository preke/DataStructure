# include <iostream>
# include <algorithm>
# define PARENT(i) (i/2)
# define LEFT(i) (2*i)
# define RIGHT(i) (2*i + 1)
# define MAXN 10000000
using namespace std;

void MaxHeapify(int* a, int i, int heap_size) {
	int maxn = i;
	if (LEFT(i) <= heap_size && a[LEFT(i)] > a[i]) {
		maxn = LEFT(i); 
	}
	if (RIGHT(i) <= heap_size && a[RIGHT(i)] > a[maxn]) {
		maxn = RIGHT(i);
	}
	if (maxn != i) {
		swap(a[i], a[maxn]);	
		MaxHeapify(a, maxn, heap_size);
	}
}

void BuildMaxHeap(int* a, int heap_size) {
	for (int i = heap_size/2; i > 0; i--) {
		MaxHeapify(a, i, heap_size);
		cout << "debug\n";
		for (int i = 0; i < 11; i ++) cout << a[i] << " ";
		cout << endl;
	}
}

void HeapSort(int* a, int heap_size) {
	BuildMaxHeap(a, heap_size);
	for (int i = heap_size; i > 1; i--) {
		swap(a[1], a[i]);
		heap_size--;
		MaxHeapify(a, 1, heap_size);
	}
}

//优先队列：
int HeapMaximum(int* a) {
	return a[1];
}

int HeapExtractMax(int* a, int heap_size) {
	if (heap_size < 1) {
		cout << "Heap Underflow\n";
		return;
	}
	int maxn = a[1];
	a[1] = a[heap_size];
	heap_size --;
	MaxHeapify(a, 1);
	return maxn;
}

void HeapIncreaseKey(int* a, int i, int k) {
	if (k < a[i]) {
		cout << "Wrong Input\n";
		return;
	}
	a[i] = k;
	while(i > 1 && a[PARENT(i)] > a[i]) {
		swap(a[i], a[PARENT(i)]);
		i = PARENT(i);
	}
}

void MaxHeapInsert(int* a, int x, int heap_size) {
	heap_size = heap_size + 1;	//这里要保证不会溢出
	a[heap_size] = -MAXN;
	HeapIncreaseKey(a, heap_size, x);
}

int main() {
	int a[11] = {0,1,2,3,4,5,6,7,8,9,0};
	HeapSort(a, 10);
	for (int i = 0; i < 11; i ++) cout << a[i] << " ";
	cout << endl;
}
