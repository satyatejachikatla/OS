#include <stdio.h>
#include <stdbool.h>

typedef struct node_{
	int data;
	struct node_* next;
}node;

#define MAX_STACK_SIZE 1000

typedef struct stack_ {
	node* data[MAX_STACK_SIZE];
	int top;
}stack;

void push(stack* s,node* e) {
	s->top++;
	if(s->top == MAX_STACK_SIZE) {
		s->top --;
		return;
	}
	s->data[s->top] = e;
}

node* pop(stack* s) {
	if(s->top == -1)
		return NULL;
	node* e = s->data[s->top];
	s->top --;
	return e;
}

void empty(stack* s) {
	s->top=-1;
}

bool is_empty(stack* s) {
	if(s->top==-1) return true;
	return false;
}

node* common_ancestor(node* n1,node* n2) {

	stack s1,s2;
	empty(&s1);
	empty(&s2);

	while(n1){
		push(&s1,n1);
		n1 = n1->next;
	}

	while(n2){
		push(&s2,n2);
		n2 = n2->next;
	}

	while(!is_empty(&s1) && !is_empty(&s2)) {
		n1 = pop(&s1);
		n2 = pop(&s2);
		if(n1 != n2)
			return n1->next;
	}
	return NULL;
}

int main() {
	node N[10];
	for(int i=0;i<10;i++){
		N[i].data=i;
	}

	N[0].next= &N[1];
	N[1].next= &N[2];
	N[2].next= &N[3];
	N[3].next= &N[4];

	N[7].next= &N[8];
	N[8].next= &N[9];
	N[9].next= &N[4];

	N[4].next= &N[5];
	N[5].next= &N[6];
	N[6].next= NULL;

	node* n = common_ancestor(&N[0],&N[7]);

	printf("common %d\n",n->data);

	return 0;

}