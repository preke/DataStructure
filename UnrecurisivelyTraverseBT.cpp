/* Reference:
 * http://www.cnblogs.com/dolphin0520/archive/2011/08/25/2153720.html
 */

# include <iostream>
# include <stack>
using namespace std;

struct BinaryTreeNode {
	int value;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
};

void PreOrder(BinaryTreeNode* root) {
	stack<BinaryTreeNode* > s;
	while (root && !s.empty()) {
		while(root) {
			cout << root->value << " ";
			s.push(root);
			root = root->left;
		}
		while(!s.empty()) {
			root = s.top();
			s.pop();
			root = root->right;
		}
	}
}

void InOrder(BinaryTreeNode* root) {
	stack<BinaryTreeNode* > s;
	while(root) {
		s.push(root);
		root = root->left;
	}
	while(!s.empty()) {
		root = s.top();
		s.pop();
		cout << root->value << " ";
		root = root->right;
	}

}

/*
 * 后序思路：
 * 要保证根结点在左孩子和右孩子访问之后才能访问，
 * 因此对于任一结点P，先将其入栈。
 * 如果P不存在左孩子和右孩子，则可以直接访问它；
 * 或者P存在左孩子或者右孩子，但是其左孩子和右孩子都已被访问过了，则同样可以直接访问该结点。
 * 若非上述两种情况，则将P的右孩子和左孩子依次入栈，
 * 这样就保证了每次取栈顶元素的时候，
 * 左孩子在右孩子前面被访问，
 * 左孩子和右孩子都在根结点前面被访问。
 */

void PostOrder(BinaryTreeNode* root) {
	stack<BinaryTreeNode* > s;
	BinaryTreeNode* curr;
	BinaryTreeNode* pre = NULL;
	s.push(root);
	while(!s.empty()) {
		curr = s.top();
		if ((curr->left == NULL && curr->right == NULL)
			  ||(pre != NULL && (pre == curr->left || pre == curr->right))) {
			cout << curr->value << " ";
			s.pop();
			pre = curr;
		} else {
			if (curr->right != NULL)
				s.push(curr->right);
			if (curr->left) 
				s.push(curr->left);
		}
	}
}

int main() {

	return 0;
}