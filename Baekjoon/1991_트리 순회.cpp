#include <cstdio>
using namespace std;

typedef struct Node {
    char data;
    Node *left;
    Node *right;
    
    Node(char d, Node *l, Node *r) { data = d; left = l; right = r; }
} Node;

Node* searchNode(Node *root, char data) {
	if(root != NULL) {
		if(root->data == data) return root;
		else {
			Node *tmp = searchNode(root->left, data);
			if(tmp != NULL) return tmp;
			tmp = searchNode(root->right, data);
			if(tmp != NULL) return tmp;
		}
	}
	return NULL;
}

void insertNode(Node *root, char parent, char left, char right) {
	root->data = parent;
	if(left != '.')
		root->left = new Node(left, NULL, NULL);
	if(right != '.')
		root->right = new Node(right, NULL, NULL);
}
int N;

//전위 순회(root->left->right)
void preorder(Node *root) {
	if(root != NULL) {
		printf("%c", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}
//중위 순회(left->root->right)
void inorder(Node *root) {
	if(root != NULL) {
		inorder(root->left);
		printf("%c", root->data);
		inorder(root->right);
	}
}
//후위 순회(left->right->root)
void postorder(Node *root) {
	if(root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("%c", root->data);
	}
}
int main() {
	scanf("%d", &N);
	Node *root = new Node('A', NULL, NULL);
	Node *tmp;
	while(N--) {
		char parent, left, right;
		scanf(" %c %c %c", &parent, &left, &right);
		tmp = searchNode(root, parent);
		if(tmp != NULL)
			insertNode(tmp, parent, left, right);
		else insertNode(root, parent, left, right);
	}
	preorder(root); printf("\n");
	inorder(root); printf("\n");
	postorder(root);
	return 0;
}