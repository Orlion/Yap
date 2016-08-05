#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memory.h"

static void default_error_handler(MEM_Controller controller, char *filename, int line, char *msg);

static struct MEM_Controller_tag st_default_controller = {
    NULL,/* stderr */
    default_error_handler,
    MEM_FAIL_AND_EXIT
};
MEM_Controller mem_default_controller = &st_default_controller;

static void default_error_handler(MEM_Controller controller, char *filename, int line, char *msg)
{
    fprintf(controller->error_fp, "MEM:%s failed in %s at %d\n", msg, filename, line);
}

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

    alloc_size = size;

    ptr = malloc(alloc_size);
    if (ptr == NULL) {
        error_handler(controller, filename, line, "malloc");
    }

    return ptr;
}

void MEM_free_func(MEM_Controller controller, void *ptr)
{
    void        *real_ptr;
    if (ptr == NULL)
        return;

    real_ptr = ptr;

    free(real_ptr);
}

void *MEM_realloc_func(MEM_Controller controller, char *filename, int line, void *ptr, size_t size)
{
    void    *new_ptr;
    size_t  alloc_size;
    void    *real_ptr;

    alloc_size = size;
    real_ptr = ptr;
    new_ptr = realloc(real_ptr, alloc_size);
    if (new_ptr == NULL) {
        if (ptr == NULL) {
            error_handler(controller, filename, line, "realloc(malloc)");
        } else {
            error_handler(controller, filename, line, "realloc");
            free(real_ptr);
        }
    }

    return(new_ptr);
}