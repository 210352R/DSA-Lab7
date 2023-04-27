#include <iostream>
using namespace std;

struct node {
  int key;
  struct node *left, *right;
};

struct node* FindMin(struct node* node);

// Inorder traversal
void traverseInOrder(struct node *root) {
    if(root==NULL){
        return;
    }
    traverseInOrder(root->left);
    cout<<root->key<<" ";
    traverseInOrder(root->right);
}

// Insert a node
struct node *insertNode(struct node *node, int key) {

    struct node* new_node =(struct node*) malloc(sizeof(node));
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;

    if (node == NULL){
        node = new_node;
        return node;
    }else{
        if(key<= node->key){
            node->left = insertNode(node->left,key);
            return node;
        }else{
            node->right = insertNode(node->right,key);
            return node;
        }
    }

}

// Deleting a node
struct node *deleteNode(struct node *root, int key) {
    if(root == NULL) {
        return root;
	}
	else if(key < root->key){
        root->left = deleteNode(root->left,key);
	}
	else if (key > root->key) {
        root->right = deleteNode(root->right,key);
	}

	else {
		// Case 1:  No child
		if(root->left == NULL && root->right == NULL) {
			delete root;
			root = NULL;
		}
		//Case 2: One child
		else if(root->left == NULL) {
			struct node *temp = root;
			root = root->right;
			delete temp;
		}
		else if(root->right == NULL) {
			struct node *temp = root;
            root = root->left;
			delete temp;
		}
		// case 3: 2 children
		else {
			struct node *temp = FindMin(root->right);
			root->key = temp->key;
			root->right = deleteNode(root->right,temp->key);
		}
	}
	return root;
}



struct node* FindMin(struct node* node){
    struct node* minNode = node;
    struct node* temp = node;

    while(temp!= NULL){
        if(minNode->key > temp->key){
            minNode = temp;
        }
        temp = temp->left;
    }

    return minNode;

}




// Driver code
int main() {
  struct node *root = NULL;

  int operation;
  int operand;
  cin >> operation;

  while (operation != -1) {
    switch(operation) {
      case 1: // insert
        cin >> operand;
        root = insertNode(root, operand);
        cin >> operation;
        break;
      case 2: // delete
        cin >> operand;
        root = deleteNode(root, operand);
        cin >> operation;
        break;
      default:
        cout << "Invalid Operator!\n";
        return 0;
    }
  }

  traverseInOrder(root);
}
