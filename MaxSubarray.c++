# include <iostream>
# define MAXN 1000000
using namespace std;

typedef struct max_sub_array{
	int low;
	int high;
	int sum;

	max_sub_array(int l, int h, int s) {
		low  = l;
		high = h;
		sum  = s; 
	}
}max_sub_array;

max_sub_array FindMaxCrossingSubArray(int* a, int low, int mid, int high) {
	int leftsum  = -MAXN;
	int rightsum = -MAXN;
	int sum      = 0;
	int max_left, max_right;
	max_left = max_right = mid;
	for (int i = mid; i >= low; i--) {
		sum = sum + a[i];
		if (sum > leftsum) {
			leftsum = sum;
			max_left = i;
		}
	}
	sum = 0;
	for (int i = mid + 1; i <= high; i++) {
		sum = sum + a[i];
		if (sum > rightsum) {
			rightsum = sum;
			max_right = i;
		}
	}

	max_sub_array ans(max_left, max_right, leftsum + rightsum);
	return ans;
}

max_sub_array FindMaxSubArray(int* a, int low, int high) {
	if (high == low) {
		return max_sub_array(low, high, a[low]);
	} else {
		int mid = (low + high) / 2;
		max_sub_array left  = FindMaxSubArray(a, low, mid);
		max_sub_array right = FindMaxSubArray(a, mid + 1, high);
		max_sub_array cross = FindMaxCrossingSubArray(a, low, mid, high);

		if (left.sum >= right.sum && left.sum > cross.sum) {
			return left;
		} else if (right.sum >= left.sum && right.sum > cross.sum) {
			return right;
		} else {
			return cross;
		}
	} 
}

//搁置，跟航哥讨论一下
max_sub_array LinearSolution(int* a, int low, int high) {
	if (high == low) {
		return max_sub_array(low, high, a[low]);
	} else {
		max_sub_array temp(low, low, a[0]);
		for (int i = low + 1; i <= high; i ++) { //注意这里是<high
			if (a[i] > 0) {
				int max = a[i];
				int j   = i - 1;
				int low_ = temp.low;
				while(j >= low_) {
					max = max + a[j];
					if (max > temp.sum) {
						temp.low = j;
						temp.high = i;
						temp.sum = max;
					}
					j--;
				}
			}
		}
		return temp;
	}
}

int main() {
	int a[8] = {1, -2, 3, 10, -4, 7, 2, 5};
	max_sub_array ans = FindMaxSubArray(a, 0, 7);
	cout << ans.low << " " << ans.high << endl;
	cout << ans.sum << endl;
	ans = LinearSolution(a, 0, 7);
	cout << ans.sum << endl;
	return 0;
}
