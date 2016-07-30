#define MARK_SIZE       (4)

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

union Header_tag {
    HeaderStruct        s;
    Align               u[HEADER_ALIGN_SIZE];
};

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
    int conter = 0;

    for (pos = controller->block_header; pos; pos = pos->s.next) {
        check_mark(pos);
        fprintf(fp, "[%04d]%p******************\n", counter, (char*)pos + sizeof(Header));
        fprintf(fp, "%s line %d size..%d\n", pos->s.filename, pos->s.line, pos->s.size);
        counter++;
    }
#endif
}
