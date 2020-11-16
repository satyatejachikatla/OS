// gcc memory_manage.c  && ./a.out
#include <stdio.h>
#include <stdbool.h>

#define SIZE_OF_HEAP 1000 //bytes
#define COLUMN_SIZE 50

char my_heap_mem[SIZE_OF_HEAP];

typedef struct  node_ {
	unsigned int ptr_size;
	bool is_free;
	struct node_* next;
} node;

typedef struct  {
	unsigned int current_size;
	node* next;
} my_heap_header;

my_heap_header* head;

void init_heap() {
	head = (my_heap_header* )my_heap_mem;
	head -> current_size = SIZE_OF_HEAP - sizeof(my_heap_header) - sizeof(node);
	head -> next = (void*)head + sizeof(my_heap_header);

	head -> next -> ptr_size = head -> current_size;
	head -> next -> is_free = true;
	head -> next -> next = NULL;
}

void* search_empty_slot(unsigned int size) {

	node* start = head->next;

	while(start) {
		if (start->is_free && start->ptr_size >= size)
			return start;
		start=start -> next;
	}

	return NULL;
}

void* my_malloc(unsigned int size) {
	node* ret=NULL;
	node* t;

	if (size < head -> current_size) {
		// Try finding a space
		ret=search_empty_slot(size);
		if (ret == NULL)
			return NULL;
		
		// If found update that header
		head -> current_size -= (size + sizeof(node));

		ret->is_free = false;

		if(ret->ptr_size - size > sizeof(node)) {
			t = ret->next;
			ret->next = (void*)ret + sizeof(node) + size;
			ret->next->is_free=true;
			ret->next->next=t;

			ret->next->ptr_size= ret->ptr_size-size-sizeof(node);
			ret->ptr_size = size;
		}

		return (void*)ret+sizeof(node);
	}

	return NULL;
}

void my_free(void* ptr) {
	node* n = ptr - sizeof(node);
	n->is_free = true;
	head -> current_size += n->ptr_size;
}

void* print_heap_list() {

	node* start = head->next;

	while(start) {
		printf("Node ptr:%p\n",start);
		printf("Node ptr size:%u\n",start->ptr_size);
		printf("Is Free:%d\n",start->is_free);
		start=start -> next;
	}

	return NULL;
}

void dump_heap_mem() {

	printf("Size of my_heap_header : %lu\n",sizeof(my_heap_header));
	printf("Size of node : %lu\n",sizeof(node));

	printf("HEAP START :%p\n",my_heap_mem);
	printf("HEAP current_size :%u\n",head->current_size);
	printf("HEAP NEXT :%p\n", head->next);

	print_heap_list();

	for(int i=0;i<SIZE_OF_HEAP;)
	{
		for(int j=0;j<COLUMN_SIZE && i < SIZE_OF_HEAP;j++,i++)
			printf("%x ",my_heap_mem[i] & 0xff);
		printf("\n");
	}
	printf("----------------------------------\n");

}



int main() {

	init_heap();

	dump_heap_mem();

	int* abc = (int *)my_malloc(sizeof(int)*2);
	char* cfg = (char *)my_malloc(sizeof(char)*4);

	*abc = 0x41414141;
	cfg[0] = 'a';
	cfg[1] = 'b';
	cfg[2] = 'c';
	cfg[3] = 'd';
	
	printf("%p: %x\n",abc,*abc);
	dump_heap_mem();

	my_free(abc);
	dump_heap_mem();


	return 0;

}