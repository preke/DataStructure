# include <iostream>
# define SIZE 100
using namespace std;

void error(const char* str) {
	cout << str << endl;
	return;
}

typedef struct stack {
	int array[SIZE];
	int top_index;

	stack() {
		top_index = -1;
	}

	int top() {
		if (top_index < 0) {
			error("Underflow");
			return -1;
		} else {
			return array[top_index];
		}
	}

	void pop() {
		if (top_index < 0) {
			error("Underflow");
		} else {
			top_index --;
		}
	}

	void push(int a) {
		if (top_index < SIZE - 1) {
			top_index ++;
			array[top_index] = a;
			return;
		} else {
			error("Full Stack");
		}
	}	
}stack;

int main() {

}

