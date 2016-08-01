#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memory.h"

#define MARK_SIZE       (4)

static void default_error_handler(MEM_Controller controller, char *filename, int line, char *msg);

static struct MEM_Controller_tag st_default_controller = {
    NULL,/* stderr */
    default_error_handler,
    MEM_FAIL_AND_EXIT
};
MEM_Controller mem_default_controller = &st_default_controller;

typedef union {
    long        l_dummy;
    double      d_dummy;
    void        *p_dummy;
} Align;

typedef struct {
    int         size;
    char        *filename;
    int         line;
    Header      *prev;
    Header      *next;
    unsigned char       mark[MARK_SIZE];
} HeaderStruct;

#define ALIGN_SIZE      (sizeof(Align))
#define revalue_up_align(val)   ((val) ? (((val) - 1) / ALIGN_SIZE + 1) : 0)
#define HEADER_ALIGN_SIZE       (revalue_up_align(sizeof(HeaderStruct)))
#define MARK (0xCD)

union Header_tag {
    HeaderStruct        s;
    Align               u[HEADER_ALIGN_SIZE];
};

static void default_error_handler(MEM_Controller controller, char *filename, int line, char *msg)
{
    fprintf(controller->error_fp, "MEM:%s failed in %s at %d\n", msg, filename, line);
}

#ifdef DEBUG
static void chain_block(MEM_Controller controller, Header *new_header)
{
    if (controller->block_header) {
        controller->block_header->s.prev = new_header;
    }
    new_header->s.prev = NULL;
    new_header->s.next = controller->block_header;
    controller->block_header = new_header;
}

static void rechain_block(MEM_Controller controller, Header *header)
{
    if (header->s.prev) {
        header->s.prev->s.next = header;
    } else {
        controller->block_header = header;
    }
    if (header->s.next) {
        header->s.next->s.prev = header;
    }
}

static void unchain_block(MEM_Controller controller, Header *header)
{
    if (header->s.prev) {
        header->s.prev->s.next = header->s.next;
    } else {
        controller->block_header = header->s.next;
    }
    if (header->s.next) {
        header->s.next->s.prev = header->s.prev;
    }
}

void set_header(Header *header, int size, char *filename, int line)
{
    header->s.size = size;
    header->s.filename = filename;
    header->s.line = line;
    memset(header->s.mark, MARK, (char*)&header[1] - (char*)header->s.mark);
}

void set_tail(void *ptr, int alloc_size)
{
    char *tail;
    tail = ((char*)ptr) + alloc_size - MARK_SIZE;
    memset(tail, MARK, MARK_SIZE);
}

void check_mark_sub(unsigned char *mark, int size)
{
    int i;

    for (i = 0; i < size; i++) {
        if (mark[i] != MARK) {
            fprintf(stderr, "bad mark\n");
            abort();
        }
    }
}

void check_mark(Header *header)
{
    unsigned char        *tail;
    check_mark_sub(header->s.mark, (char*)&header[1] - (char*)header->s.mark);
    tail = ((unsigned char*)header) + header->s.size + sizeof(Header);
    check_mark_sub(tail, MARK_SIZE);
}
#endif /* DEBUG */

static void error_handler(MEM_Controller controller, char *filename, int line, char *msg)
{
    if (controller->error_fp == NULL) {
        controller->error_fp = stderr;
    }
    controller->error_handler(controller, filename, line, msg);

    if (controller->fail_mode == MEM_FAIL_AND_EXIT) {
        exit(1);
    }
}

void* MEM_malloc_func(MEM_Controller controller, char *filename, int line, size_t size)
{
    void        *ptr;
    size_t      alloc_size;

#ifdef DEBUG
    alloc_size = size + sizeof(Header) + MARK_SIZE;
#else
    alloc_size = size;
#endif
    ptr = malloc(alloc_size);
    if (ptr == NULL) {
        error_handler(controller, filename, line, "malloc");
    }

#ifdef DEBUG
    memset(ptr, 0xCC, alloc_size);
    set_header(ptr, size, filename, line);
    set_tail(ptr, alloc_size);
    chain_block(controller, (Header*)ptr);
    ptr = (char*)ptr + sizeof(Header);
#endif

    return ptr;
}

void MEM_dump_blocks_func(MEM_Controller controller, FILE *fp)
{
#ifdef DEBUG
    Header *pos;
    int counter = 0;

    for (pos = controller->block_header; pos; pos = pos->s.next) {
        check_mark(pos);
        fprintf(fp, "[%04d]%p******************\n", counter, (char*)pos + sizeof(Header));
        fprintf(fp, "%s line %d size..%d\n", pos->s.filename, pos->s.line, pos->s.size);
        counter++;
    }
#endif
}

void MEM_free_func(MEM_Controller controller, void *ptr)
{
    void        *real_ptr;
#ifdef DEBUG
    int size;
#endif
    if (ptr == NULL)
        return;

#ifdef DEBUG
    real_ptr = (char*)ptr - sizeof(Header);
    check_mark((Header*)real_ptr);
    size = ((Header*)real_ptr)->s.size;
    unchain_block(controller, real_ptr);
    memset(real_ptr, 0xCC, size + sizeof(Header));
#else
    real_ptr = ptr;
#endif

    free(real_ptr);
}
