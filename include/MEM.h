#ifndef PUBLIC_MEM_H
#define PUBLIC_MEM_H

typedef struct MEM_Storage_tag *MEM_Storage;

MEM_Storage MEM_open_storage_func(char *filename, int line, int page_size);

#define MEM_open_storage(page_size) (MEM_open_storage_func(__FILE__, __LINE__, page_size))


void *MEM_storage_malloc_func(char *filename, int line, MEM_Storage storage, size_t size);

#define MEM_storage_malloc(storage, size) (MEM_storage_malloc_func(__FILE__, __LINE__, storage, size))
#endif
