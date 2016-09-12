void *MEM_malloc_func(char *filename, int line, size_t size)
{
	void *ptr;
	size_t alloc_size;

	alloc_size = size;

	ptr = malloc(alloc_size);
	if (ptr == NULL) {
		fprintf(stderr, "Malloc error in %s:%d line\n", filename, line);
	}

	memset(ptr, 0xCC, alloc_size);

	return ptr;
}