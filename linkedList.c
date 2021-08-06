#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node_ {
    char c;
    struct node_* next;
    struct node_* prev;
}node_t;

node_t* insert(node_t* root,node_t* new_node) {

    if(!root){
        new_node->next = NULL;
        new_node->prev = NULL;
        return new_node;
    }

    node_t* original_root = root;

    while(root->next) {
        root = root->next;
    }

    root->next = new_node;
    new_node->next = NULL;
    new_node->prev = root;

    return original_root;
}



node_t* findMiddle(node_t* root) {
    node_t* first_pointer=root;
    node_t* second_pointer=root;

    while(second_pointer && (second_pointer->next != NULL)) {
        second_pointer = second_pointer->next;
        if(second_pointer->next == NULL) {
            break;
        }
        second_pointer = second_pointer->next;
        first_pointer = first_pointer->next;
    }


    return first_pointer;
}

int sizeOfList(node_t* root) {
    int i=0;
    while(root){
        root =root->next;
        i++;
    }
    return i;
}

bool isPallindrom(node_t* root) {
    node_t* middle_node = findMiddle(root);
    int n = sizeOfList(root);

    node_t* forward_node;
    node_t* backward_node;

    if(n%2 == 1){
        forward_node = middle_node ->next;
        backward_node = middle_node ->prev;
    } else {
        forward_node = middle_node ->next;
        backward_node = middle_node;
    }

    while(forward_node && backward_node) {
        if (forward_node->c != backward_node->c)
            return false;
        forward_node = forward_node->next;
        backward_node = backward_node->prev;
    }

    return true;

}

void display(node_t* root) {
    while(root) {
        printf("%c ",root->c);
        root=root->next;
    }
    printf("\n");

}

int main()
{
    int n;
    char c[10] = {
        'a' , 'b' , 'b' , 'a' , 'a' , 'c' , 'd' , 'e' , 'd' , 'e'
    };


    node_t* root=NULL;

    printf("Enter num nodes:");
    scanf("%d",&n);

    for(int i=0;i<n;i++) {
        node_t* temp = (node_t *)malloc(sizeof(node_t));
        temp->c = c[i];
        root = insert(root,temp);
    }

    display(root);
    printf("Middle Element : %c\n",findMiddle(root)->c);
    printf("isPallindrom: %d\n",isPallindrom(root));

    return 0;
}
