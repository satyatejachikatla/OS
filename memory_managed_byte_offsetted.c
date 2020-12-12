
#define OFFSET_ADDRESS 8 

void* my_malloc(size_t size) {

	void* ptr=malloc(size+OFFSET_ADDRESS);

	int reminder=(ptr % OFFSET_ADDRESS);
	int append_size = (OFFSET_ADDRESS-reminder);

	char* append_byte=(char*)(ptr+append_size-1);
	// Storing the append size
	*append_byte=append_size;

	//Appending and returning
	return ptr+append_size;
}

void my_free(void* ptr) {

	char append_size=*(char *)(ptr-1);

	void* original_ptr=(ptr-append_size);

	free(original_ptr);
}