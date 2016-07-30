#ifndef PUBLIC_MEM_H
#define PUBLIC_MEM_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    MEM_FAIL_AND_EXIT,
    MEM_FAIL_AND_RETURN
} MEM_FailMode;

typedef void (*MEM_ErrorHandler)(MEM_Controller, char *, int, char *);
typedef struct MEM_Controller_tag *MEM_Controller;

extern MEM_Controller mem_default_controller;

#ifdef MEM_CONTROLLER
#define MEM_CURRENT_CONTROLLER MEM_CONTROLLER
#else /* MEM_CONTROLLER */
#define MEM_CURRENT_CONTROLLER mem_default_controller
#endif /* MEM_CONTROLLER */

#define MEM_open_storage(page_size) (MEM_open_storage_func(MEM_CURRENT_CONTROLLER, __FILE__, __LINE__, page_size))

#define MEM_dump_blocks(fp) (MEM_dump_blocks_func(MEM_CURRENT_CONTROLLER, fp))

typedef struct MEM_storage_tag MEM_Storage;

#endif  /* PUBLIC_MEM_H */
