# include <iostream>
# define SIZE 100
using namespace std;

void error(const char* ch) {
	cout << ch << endl;
}

typedef struct queue {
	int array[SIZE];
	int head;
	int tail;
	int size;

	queue(int n) {
		tail = 0;
		head = 1;
		size = n + 1; //注意这里保持语义的正确性，保证能够保存n个元素
	}

	void EnQueue(int x) {
		if (! this->isFull()) {
			array[head] = x;
			head ++;
			head = head % size;
		} else{
			error("Full");
		}
	}

	void DeQueue() {
		if (! this->isEmpty()) {
			tail = tail + 1;
			tail = tail % size;
		}
	}

	bool isFull() {
		if (head  == tail) {
			return true;
		}
		return false;
	}

	bool isEmpty() {
		if (head == (tail + 1) % size) {
			return true;
		}
		return false;
	}

	void print() {
		if (!this->isEmpty()) {
			int i = head - 1;
			do {
					i = (i + size) % size;
					cout << array[i] << " ";
					i--;
			} while( (i + size) % size != (tail + size) % size ); 
			cout << endl;
		} else {
			error("Empty");
		}
	}

}queue;

int main() {
	// queue q(8);
	// for (int i = 0; i < 10; i ++) {
	// 	q.EnQueue(i+1);
	// }
	// q.DeQueue();
	// q.DeQueue();
	// q.print();
}