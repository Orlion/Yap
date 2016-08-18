#ifndef PUBLIC_MEM_H
#define PUBLIC_MEM_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    MEM_FAIL_AND_EXIT,
    MEM_FAIL_AND_RETURN
} MEM_FailMode;

typedef struct MEM_Controller_tag *MEM_Controller;
typedef void (*MEM_ErrorHandler)(MEM_Controller, char *, int, char *);
typedef struct MEM_Storage_tag *MEM_Storage;

extern MEM_Controller mem_default_controller;

#ifdef MEM_CONTROLLER
#define MEM_CURRENT_CONTROLLER MEM_CONTROLLER
#else /* MEM_CONTROLLER */
#define MEM_CURRENT_CONTROLLER mem_default_controller
#endif /* MEM_CONTROLLER */

MEM_Storage MEM_open_storage_func(MEM_Controller controller, char *filename, int line, int page_size);

#define MEM_open_storage(page_size) (MEM_open_storage_func(MEM_CURRENT_CONTROLLER, __FILE__, __LINE__, page_size))

void *MEM_storage_malloc_func(MEM_Controller controller, char *filename, int line, MEM_Storage storage, size_t size);

#define MEM_storage_malloc(storage, size) (MEM_storage_malloc_func(MEM_CURRENT_CONTROLLER, __FILE__, __LINE__, storage, size))

void *MEM_realloc_func(MEM_Controller controller, char *filename, int line, void *ptr, size_t size);

#define MEM_realloc(ptr, size) (MEM_realloc_func(MEM_CURRENT_CONTROLLER, __FILE__, __LINE__, ptr, size))

#define MEM_dump_blocks(fp) (MEM_dump_blocks_func(MEM_CURRENT_CONTROLLER, fp))

void MEM_free_func(MEM_Controller controller, void *ptr);

#define MEM_free(ptr) (MEM_free_func(MEM_CURRENT_CONTROLLER, ptr))

void *MEM_malloc_func(MEM_Controller controller, char *filename, int line, size_t size);

#define MEM_malloc(size) (MEM_malloc_func(MEM_CURRENT_CONTROLLER, __FILE__, __LINE__, size))

char *MEM_strdup_func(MEM_Controller controller, char *filename, int line, char *str);

#define MEM_strdup(str) (MEM_strdup_func(MEM_CURRENT_CONTROLLER, __FILE__, __LINE__, str))

void MEM_dispose_storage_func(MEM_Controller controller, MEM_Storage storage);

#define MEM_dispose_storage(storage) (MEM_dispose_storage_func(MEM_CURRENT_CONTROLLER, storage))

#endif  /* PUBLIC_MEM_H */