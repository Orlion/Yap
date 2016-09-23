#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *MEM_malloc_func(char *filename, int line, size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (ptr == NULL) {
		fprintf(stderr, "Malloc error in %s:%d line\n", filename, line);
	}

	memset(ptr, 0xCC, size);

	return ptr;
}

void *MEM_realloc_func(char *filename, int line, void *ptr, size_t size)
{
	void *new_ptr;

	new_ptr = realloc(ptr, size);
	if (new_ptr == NULL) {
		if (ptr == NULL) {
			fprintf(stderr, "Realloc(malloc) error in %s:%d line\n", filename, line);
		} else {
			fprintf(stderr, "Realloc error in %s:%d line\n", filename, line);
		}
	}

	return (new_ptr);
}