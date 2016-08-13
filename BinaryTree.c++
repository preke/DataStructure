# include <iostream>
using namespace std;

typedef struct BinaryTree{
	int value;
	struct BinaryTree* pLeft;
	struct BinaryTree* pRight;
}BinaryTreeNode;

int Pre[100], In[100], Post[100];


void PreOrderTraversal (BinaryTreeNode* root) {
	if (root == NULL) {
		return;
	} else {
		cout << root->value << ' ';
		PreOrderTraversal(root->pLeft);
		PreOrderTraversal(root->pRight);
	}
}

void InOrderTraversal (BinaryTreeNode* root) {
	if (root == NULL) {
		return;
	} else {
		InOrderTraversal(root->pLeft);
		cout << root->value << ' ';
		InOrderTraversal(root->pRight);
	}
}

void PostOrderTraversal (BinaryTreeNode* root) {
	if (root == NULL) {
		return;
	} else {
		PostOrderTraversal(root->pLeft);
		PostOrderTraversal(root->pRight);
		cout << root->value << ' ';
	}
}

BinaryTreeNode* buildByPreAndIn(int* pre_order, int* in_order, int num) {
	if (pre_order == NULL || in_order == NULL || num <= 0)	return NULL;
	
	BinaryTreeNode* root = new BinaryTreeNode;
	root->value = *pre_order;
	root->pLeft = root->pRight = NULL;

	int rootPositionInOrder = -1;
	for (int i = 0; i < num; i++) {
		if (in_order[i] == root->value) {
			rootPositionInOrder = i;
			break;
		}
	}

	int num_Left  = rootPositionInOrder;
	int num_Right = num - num_Left - 1;

	int* pre_order_left  = pre_order + 1;
	int* in_order_left   = in_order;
	root->pLeft          = buildByPreAndIn(pre_order_left, in_order_left, num_Left);
	
	int* pre_order_right = pre_order + num_Left + 1;
	int* in_order_right  = in_order + num_Left + 1;
	root->pRight         = buildByPreAndIn(pre_order_right, in_order_right, num_Right);

	return root;
}

BinaryTreeNode* buildByPostAndIn(int* post_order, int* in_order, int num) {
	if (post_order == NULL || in_order == NULL || num <= 0)	return NULL;
	
	BinaryTreeNode* root = new BinaryTreeNode;
	root->value = post_order[num - 1];
	root->pLeft = root->pRight = NULL;

	int rootPositionInOrder = -1;
	for (int i = 0; i < num; i++) {
		if (in_order[i] == root->value) {
			rootPositionInOrder = i;
			break;
		}
	}

	int num_Left  = rootPositionInOrder;
	int num_Right = num - num_Left - 1;

	int* post_order_left = post_order;
	int* in_order_left   = in_order;
	root->pLeft          = buildByPostAndIn(post_order_left, in_order_left, num_Left);

	int* post_order_right = post_order + num_Left;
	int* in_order_right   = in_order + num_Left + 1;
	root->pRight          = buildByPostAndIn(post_order_right, in_order_right, num_Right);	

	return root;
}

int getNumOfElements(BinaryTreeNode* root) {
	if (root == NULL) {
		return 0;
	} else {
		return getNumOfElements(root->pLeft) + getNumOfElements(root->pRight) + 1;
	}
}

int getNumOfLeaf(BinaryTreeNode* root) {
	if (root == NULL) {
		return 0;
	}
	if (root->pLeft == root->pRight == NULL) {
		return 1;
	}
	return getNumOfLeaf(root->pLeft) + getNumOfLeaf(root->pRight);
}

int main(){
	
}








