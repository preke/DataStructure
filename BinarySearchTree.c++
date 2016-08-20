# include <iostream>
using namespace std;

typedef struct BinarySearchTreeNode {
	int value;
	BinarySearchTreeNode* parent;
	BinarySearchTreeNode* left;
	BinarySearchTreeNode* right;
}BinarySearchTreeNode;

void InOrder(BinarySearchTreeNode* root) {
	if (root != NULL) {
		InOrder(root->left);
		cout << root->value << " ";
		InOrder(root->right);
	}
}

BinarySearchTreeNode* Search(BinarySearchTreeNode* root, int x) {
	if (root == NULL || x == root->value) {
		return root;
	} else {
		if (x > root->value) {
			return Search(root->right, x);
		} else {
			return Search(root->left, x);
		}
	}
}

//非递归
BinarySearchTreeNode* Search_(BinarySearchTreeNode* root, int x) {
	while( root != NULL && x != root->value) {
		if (x > root->value) {
			root = root->right;
		} else {
			root = root->left;
		}
	}
	return root;
}

BinarySearchTreeNode* Min(BinarySearchTreeNode* root) {
	BinarySearchTreeNode* ans = NULL;
	while (root != NULL ) {
		ans  = root;
		root = root->left;
	}
	return ans;
}

BinarySearchTreeNode* Max(BinarySearchTreeNode* root) {
	BinarySearchTreeNode* ans = NULL;
	while (root != NULL ) {
		ans  = root;
		root = root->right;
	}
	return ans;
}

BinarySearchTreeNode* FindSuccessor(BinarySearchTreeNode* root) {
	if (root->right != NULL) {
		return Min(root->right);
	} else {
		BinarySearchTreeNode* ans = root->parent;
		while(ans != NULL && root == ans->right) {
			root = ans;
			ans  = ans->parent;
		}
		return ans;
	}
}

void Insert(BinarySearchTreeNode* &root, int z) {
	BinarySearchTreeNode* temp = new BinarySearchTreeNode;
	temp->value = z;
	temp->parent = temp->left = temp->right = NULL;
	BinarySearchTreeNode* index = root;
	BinarySearchTreeNode* index_parent = NULL; 
	while(index != NULL) {
		index_parent = index;
		if (temp->value > index->value) {
			index = index->right;
		} else {
			index = index->left;
		}
	}
	temp->parent = index_parent;
	if (index_parent == NULL) {
		root = temp;
	} else if (temp->value > index_parent->value) {
		index_parent->right = temp;
	} else {
		index_parent->left = temp;
	}

}

//以v为根的子树替换一棵以u为根的子树
void TransPlant(BinarySearchTreeNode* & root, BinarySearchTreeNode* u, BinarySearchTreeNode* & v) {
  if(u->parent == NULL) {
    root = v;
  } else {
    BinarySearchTreeNode* & Parent = u->parent;
    if (u == Parent->left) {
      Parent->left = v;
    } else {
      Parent->right = v;
    }
  }
  if (v != NULL) {
    v->parent = u->parent;
  }
}

void Delete(BinarySearchTreeNode* &root, BinarySearchTreeNode* z) {     //如果传入的参数是int,那就调用一次Search
  if (root == NULL) {
    cout << "Already empty!" << endl;
    return;
  }
  if (z == NULL) {
    cout << "Not exist!" << endl;
    return;
  }
  if (z->left == NULL) { 
    TransPlant(root, z, z->right);
  } else if (z->right == NULL) {
    TransPlant(root, z, z->left);
  } else { //上两种情况是只有一个子树，或者没有子树，下面的情况是有两个子树
  	BinarySearchTreeNode* y = Min(z->right);
  	if (y->parent != z) {   //如果y不是z的右子树, 把y换到z的右子树
  	  TransPlant(root, y, y->right);
  	  y->right = z->right;
  	  y->right->parent = y;
  	}
	
  	TransPlant(root, z, y);
  	y->left = z->left;
  	y->left->parent = y;
  }
}

int main() {
	//for test
	// BinarySearchTreeNode* root = NULL;
	// int a;
	// for (int i = 0; i < 10; i ++) {
	// 	cin >> a;
	// 	Insert(root, a);
	// }
	// InOrder(root);
	// cout << endl;
	// while(1) {
	// 	cin >> a;
	// 	if (a == -1) {
	// 		break;
	// 	}
	// 	Delete(root, Search_(root, a));
	// 	InOrder(root);
	// 	cout << endl;
	// }
	// cout << endl;
	return 0;
}


