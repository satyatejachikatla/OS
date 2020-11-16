#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct node_{
	int data;
	struct node_* left;
	struct node_* right;

}node;


node* head;

void insert(node* head, int data) {
	if (data < head->data) {
		if (head->left)
			insert(head->left,data);
		else {
			head->left = malloc(sizeof(head));
			head->left->data=data;
		}

	} else if (data > head->data) {
		if (head->right)
			insert(head->right,data);
		else {
			head->right = malloc(sizeof(head));
			head->right->data=data;
		}
	} else {
		return;
	}
}

node* find(node* head, int data) {
	if (data < head->data && head->left) {
			find(head->left,data);
	} else if (data > head->data && head->right) {
			find(head->right,data);
	} else if (data == head->data) {
			return head;
	}
	return NULL;
}

node* common_ancestor(node* head, int data1,int data2) {

	int t;
	if (data1 > data2) {
		t = data1;
		data1 = data2;
		data2 = t; 
	}

	// node* data1_node = find(data1);
	// node* data2_node = find(data2);

	while(head) {
		if(data1 < head->data && data2 < head-> data )
			head = head->left;
		else if(data1 > head->data && data2 > head-> data )
			head = head->right;
		else if (data1 == head->data && data2 == head->data ||
				 data1 == head->data && data2 > head->data ||
				 data2 == head->data && data1 < head->data ){
			return head;
		} else {
			return NULL;
		}
	}

	return NULL;
}

int main() {
}