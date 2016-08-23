# include <iostream>
# include <cstdlib>
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

void InOrder(RBTreeNode* root);
void PreOrder(RBTreeNode* root);
//左旋

void Debug(RBTreeNode* root) {
	cout << "here" << endl;
	cout << "PreOrder: " << endl;
	PreOrder(root);
	cout << "InOrder: " << endl;
	InOrder(root);
}

void LeftRotate(RBTreeNode* &root, RBTreeNode* x) {
	if (x == NULL) {
		cout << "Wrong input!\n";
		return;
	}
	
	RBTreeNode* y = x->right; 	//暂存旋转前x的右子树
	
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
	} else { //x旋转前是双亲的右子树
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
	x->parent = y->parent;

	//让旋转前y的双亲指向x
	if (y->parent == Tnull) {	//y旋转前是树根
		root = x;
	} else if (y == y->parent->left) { //y旋转前是双亲的左子树
		y->parent->left = x;
	} else { //y旋转前是双亲的右子树
		y->parent->right = x;
	}

	x->right = y; //设置旋转后x的右子树
	y->parent = x; //设置旋转后y的双亲为x
}

void InsertFixUp(RBTreeNode* & root, RBTreeNode* &z) {	
	while(z->parent && z->parent->color == RED) { //因为z的颜色被设置为红色，此时违反性质4
		
		if (z->parent->parent != Tnull&& z->parent == z->parent->parent->left) {  
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
			if (z->parent != Tnull) {
				z->parent->color = BLACK;
				if (z->parent->parent != Tnull) {
					z->parent->parent->color = RED;
					RightRotate(root, z->parent->parent);
				}
			}

		} else if (z->parent->parent != Tnull && z->parent == z->parent->parent->right){ 																		
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

			if (z->parent != Tnull) {
				z->parent->color = BLACK;
				if (z->parent->parent != Tnull ) {
					z->parent->parent->color = RED;
					LeftRotate(root, z->parent->parent);
				}
			}
		}
	}
	
	root->color = BLACK;
}

void InOrder(RBTreeNode* root) {
	if (root && root != Tnull) {
		InOrder(root->left);
		cout << root->value << " " << root->color << endl;
		InOrder(root->right);
	}
}

void PreOrder(RBTreeNode* root) {
	if (root && root != Tnull) {
		cout << root->value << " " << root->color << endl;
		PreOrder(root->left);
		PreOrder(root->right);
	}
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
	//InOrder(root);
	InsertFixUp(root, z);
}



RBTreeNode* Min(RBTreeNode* root) {
	RBTreeNode* ans = Tnull;
  while (root != Tnull ) {
    ans  = root;
    root = root->left;
  }
  return ans;
}

//以v为根的子树替换一棵以u为根的子树
void TransPlant(RBTreeNode* & root, RBTreeNode* u, RBTreeNode* & v) {
	
	if (u->parent == Tnull) {
		root = v;		
	} else if (u == u->parent->left) {
		u->parent->left = v;
	} else {
		u->parent->right = v;
	}
	v->parent = u->parent;
}

void DeleteFixUp(RBTreeNode* & root, RBTreeNode* x) {
	RBTreeNode* w; //保持w为x的兄弟
	while(x != root && x->color == BLACK) {
		if (x == x->parent->left) {
			w = x->parent->right;
			if (w->color == RED) { //case 1 w的颜色为红色
				w->color = BLACK;
				x->parent->color = RED;
				LeftRotate(root, x->parent);
				w = x->parent->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) { //case 2 
				w->color = RED;
				x = x->parent;	//向上尾递归
			}
			else {
				if (w->right->color == BLACK) { //case 3  w的右子树为黑色
					w->left->color = BLACK;
					w->color = RED;
					RightRotate(root, w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				LeftRotate(root, x->parent);

				x = root;
			}

		
		} else {
			w = x->parent->left;
			if (w->color == RED) { //case 1 w的颜色为红色
				w->color = BLACK;
				x->parent->color = RED;
				RightRotate(root, x->parent);
				w = x->parent->left;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) { //case 2 
				w->color = RED;
				x = x->parent;	//向上尾递归
			}
			else {
				if (w->left->color == BLACK) { //case 3  w的左子树为黑色
					w->right->color = BLACK;
					w->color = RED;
					LeftRotate(root, w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				RightRotate(root, x->parent);
				x = root;
			}
		}
	}
	x->color = BLACK;

}

RBTreeNode* Search_(RBTreeNode* root, int x) {
	while( root!= Tnull && x != root->value) {
		if (x > root->value) {
			root = root->right;
		} else {
			root = root->left;
		}
	}
	return root;
}

void Delete(RBTreeNode* & root, RBTreeNode* z) {
	if (root == Tnull) {
		cout << "Already empty!" << endl;
		return;
	}
	if (z == Tnull) {
		cout << "Doesn`t exist!" << endl;
		return;
	}
	//	y节点有两种情况：
	//	1. z节点删除后，y节点是要在树中去替代z节点的节点
	//	2. y节点指向被删除的z节点
	//	但是无论哪种情况，如果y的原来的颜色为黑色，那么就会引起红黑树性质的破坏
	RBTreeNode* y = z; //指向待删除节点
	RBTreeNode* x; //x来记录删除后（移动到y节点的原始位置）的节点的位置
	bool y_original_color = y->color; //记录原来待删除节点的颜色
	//以下两个case是待删除节点只有一个子树或者没有子树
	
	if (z->left == Tnull) {
		x = z->right;
		TransPlant(root, z, z->right);
	} else if (z->right == Tnull) {
		x = z->left;
		TransPlant(root, z, z->left);
	} else { //待删除节点有两个子树
		y = Min(z->right); //记录待删除节点的后继
		y_original_color = y->color; //记录待删除节点的后继的颜色
		x = y->right;
		
		if (y->parent == z) { //说明后继是待删除节点的右子树的树根
				x->parent = y;	
		} else { //把后继换到右子树的树根
				
			TransPlant(root, y, y->right); 
			
			y->right = z->right;
			y->right->parent = y;
		}
		TransPlant(root, z, y);
		
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}

	if (y_original_color == BLACK)
		DeleteFixUp(root, x); 
}

int main() {
	Tnull = new RBTreeNode; // initialed by construct function
	
	// //for test
	// RBTreeNode* root = NULL;
	// int a[10] = {4, 3, 5, 1, 8, 6, 2, 7, 9, 77};
	// for (int i = 0; i < 10; i ++) {
	// 	RBTreeNode* temp = new RBTreeNode;
	// 	temp->parent = temp->left = temp->right = Tnull;
	// 	temp->value = a[i];
	// 	Insert(root, temp);
	// }
	// int b;
	// for (int i = 0; i < 10; i ++) {
	// 	cin >> b;
	// 	RBTreeNode* temp = Search_(root, b);
	// 	Delete(root, temp);
	// 	Debug(root);
	// }
	return 0;
}


