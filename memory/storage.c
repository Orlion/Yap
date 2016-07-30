#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "memory.h"

typedef union {
    long        l_dummy;
    double      d_dummy;
    void        *p_dummy;
} Cell;

#define CELL_SIZE               (sizeof(Cell))
#define DEFAULT_PAGE_SIZE       (1024)  /* cell num */

typedef struct MemoryPage_tag MemoryPage;
typedef MemoryPage *MemoryPageList;

struct MemoryPage_tag {
    int                 cell_num;
    int                 use_cell_num;
    MemoryPageList      next;
    Cell                cell[1];
};

struct MEM_Storage_tag {
    MemoryPageList      page_list;
    int                 current_page_size;
};

MEM_Storage MEM_open_storage_func(MEM_Controller controller, char *filename, int line, int page_size)
{
    MEM_Storage storage;

    storage = MEM_malloc_func(controller, filename, line, sizeof(struct MEM_Storage_tag));
    storage->page_list = NULL;
    assert(page_size >= 0);
    if (page_size > 0) {
        storage->current_page_size = page_size;
    } else {
        storage->current_page_size = DEFAULT_PAGE_SIZE;
    }

    return storage;
}
