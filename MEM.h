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

#define MEM_open_storage(page_size) (MEM_open_storage_func(MEM_CURRENT_CONTROLLER, __FILE__, __LINE__, page_size))
#define MEM_storage_malloc(storage, size) (MEM_storage_malloc_func(MEM_CURRENT_CONTROLLER, __FILE__, __LINE__, storage, size))

#define MEM_realloc(ptr, size) (MEM_realloc_func(MEM_CURRENT_CONTROLLER, __FILE__, __LINE__, ptr, size))

#define MEM_dump_blocks(fp) (MEM_dump_blocks_func(MEM_CURRENT_CONTROLLER, fp))

#define MEM_free(ptr) (MEM_free_func(MEM_CURRENT_CONTROLLER, ptr))

#define MEM_malloc(size) (MEM_malloc_func(MEM_CURRENT_CONTROLLER, __FILE__, __LINE__, size))

#endif  /* PUBLIC_MEM_H */