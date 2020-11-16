typedef struct node_{
	int data;
	struct node_* next;
}node;

bool has_loop(node* head) {

	if(!head)
		return false;

	node* slow_ptr=head;
	node* fast_ptr=head->next;

	while(slow_ptr != fast_ptr) {

		if(slow_ptr == NULL || fast_ptr == NULL)
			return false;
		slow_ptr = slow_ptr->next;
		fast_ptr = fast_ptr->next;
		if(fast_ptr)
			fast_ptr = fast_ptr->next;
	}

	return true;

}