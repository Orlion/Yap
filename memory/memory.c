#include <stdio.h>
#include <stdlib.h>

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
