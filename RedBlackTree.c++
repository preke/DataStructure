# include <iostream>
using namespace std;

#define RED 0
#define BLACK 1

typedef struct RBTreeNode {
	bool color;	
	int value;
	RBTreeNode* left;
	RBTreeNode* right;
	RBTreeNode* parent;

	RBTreeNode(){
		color = BLACK;
		value = -1;
		left  = right = parent = NULL;
	}
}RBTreeNode;

RBTreeNode* Tnull;

//左旋
void LeftRotate(RBTreeNode* &root, RBTreeNode* x) {
	if (x == NULL) {
		cout << "Wrong input!\n";
		return;
	}
	
	RBTreeNode* y = x->right; 	//暂存旋转前x的右子树
	
	if (y == NULL) {
		return;
	}
	
	x->right = y->left;				//设置旋转后x的右子树
	if (y->left != Tnull){
		y->left->parent = x;		//设置旋转后x的右子树的双亲
	}
	y->parent = x->parent;

	//先设置旋转后y的双亲是因为此时x的双亲还没有变
	//让旋转前x的双亲指向y
	if (x->parent == Tnull) {	//x旋转前是树根
		root = y;
	} else if (x == x->parent->left) { //x旋转前是双亲的左子树
		x->parent->left = y;
	} else if (x == x->parent->right) { //x旋转前是双亲的右子树
		x->parent->right = y;
	}

	y->left = x; 	//设置旋转后y的左子树
	x->parent = y; 	//设置旋转后x的双亲为旋转后的y
}

//右旋
void RightRotate(RBTreeNode* &root, RBTreeNode* y) {
	if (y == NULL) {
		cout << "Wrong input!\n";
		return;
	}
	
	RBTreeNode* x = y->left; 	//暂存旋转前y的左子树
	
	if (x == NULL) {
		return;
	}
	
	y->left = x->right;				//设置旋转后y的左子树
	if (x->right != Tnull){
		x->right->parent = y;		//设置旋转后y的左子树的双亲
	}
	y->parent = x->parent;

	//让旋转前y的双亲指向x
	if (y->parent == Tnull) {	//y旋转前是树根
		root = x;
	} else if (y == y->parent->left) { //y旋转前是双亲的左子树
		y->parent->left = x;
	} else if (y == y->parent->right) { //y旋转前是双亲的右子树
		y->parent->right = x;
	}

	x->right = y; //设置旋转后x的右子树
	y->parent = x; //设置旋转后y的双亲为x
}

void InsertFixUp(RBTreeNode* & root, RBTreeNode* z) {	
	while(z->parent && z->parent->color == RED) { //因为z的颜色被设置为红色，此时违反性质4
		
		if (z->parent->parent && z->parent == z->parent->parent->left) {  
			//插入点的父节点是爷爷节点的左子树	
			RBTreeNode* y = z->parent->parent->right; //y是叔叔节点
			if (y->color == RED) {    //case 1 叔叔节点是红色
				z->parent->color = BLACK; //父亲节点
				y->color = BLACK;	//叔叔节点
				z->parent->parent->color =  RED; //爷爷节点
				z = z->parent->parent; //此时爷爷节点有可能也违反规则，我们尾递归上去
			} else if (z == z->parent->right) { //case 2 叔叔节点是黑色
				z = z->parent;
				LeftRotate(root, z); //如果插入节点是父节点的右子树，旋过去
			}
			if (z->parent)
				z->parent->color = BLACK;
			if (z->parent->parent) {
				z->parent->parent->color = RED;
				RightRotate(root, z->parent->parent);
			}

		} else if (z->parent->parent && z->parent == z->parent->parent->right){ 																		
			//插入点的父节点是爷爷节点的右子树
			RBTreeNode* y = z->parent->parent->left; //y是叔叔节点
			if (y->color == RED) {    //case 1 叔叔节点是红色
				z->parent->color = BLACK; //父亲节点
				y->color = BLACK;	//叔叔节点
				z->parent->parent->color =  RED; //爷爷节点
				z = z->parent->parent; //此时爷爷节点有可能也违反规则，我们尾递归上去
			} else if (z == z->parent->left) { //case 2 叔叔节点是黑色
				z = z->parent;
				RightRotate(root, z); //如果插入节点是父节点的左子树，旋过去
			}
			if (z->parent)
				z->parent->color = BLACK;
			if (z->parent->parent) {
				z->parent->parent->color = RED;
				LeftRotate(root, z->parent->parent);
			}
		}
	}
	
	root->color = BLACK;
}

//先在外面创建好节点z再插入，过程很像二叉搜索树的插入
void Insert(RBTreeNode* &root, RBTreeNode* z) {
	
	RBTreeNode* y = Tnull;
	RBTreeNode* x = root;
	while(x && x != Tnull) { //用x遍历去找合适的插入位置, y始终保持是x的双亲
		y = x;
		if (z->value < x->value) {
			x = x->left;
		} else {
			x = x->right;
		}
	}

	z->parent = y;
	if (y == Tnull) {
		root = z;
	} else if (z->value < y->value) {
		y->left = z;
	} else {
		y->right = z;
	}
	z->left = z->right = Tnull;
	z->color = RED;

	InsertFixUp(root, z);
}

void InOrder(RBTreeNode* root) {
	if (root && root != Tnull) {
		InOrder(root->left);
		cout << root->value << " " << root->color << endl;
		InOrder(root->right);
	}
}


int main() {
	Tnull = new RBTreeNode; // initialed by construct function
	
	// for test
	// RBTreeNode* root;
	// int a;
	// for (int i = 0; i < 10; i ++) {
	// 	cin >> a;
	// 	RBTreeNode* temp = new RBTreeNode;
	// 	temp->value = a;
	// 	Insert(root, temp);
	// 	InOrder(root);
	// }
	return 0;
}


