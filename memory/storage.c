typedef struct MemoryPage_tag MemoryPage;
typedef MemoryPage *MemoryPageList;

#define larget(a, b) (((a) > (b)) ? (a) : (b))

typedef union {
	long 	l_dummy;
	double	d_dummy;
	void	*p_dummy;
} Cell;

struct MemoryPage_tag {
	int 		cell_num;
	int		use_cell_num;
	MemoryPageList	next;
	Cell 	cell[1];
};

struct MEM_Storage_tag {
	MemoryPageList	page_list;
	int				current_page_size;
};

void *MEM_open_storage_func(char *filename, int line, int page_size)
{
	MEM_Storage storage;

	storage = MEM_malloc_func(filename, line, sizeof(struct MEM_Storage_tag));
	storage->page_list = NULL;
	if (page_size > 0) {
		storage->current_page_size = page_size;
	} else {
		storage->current_page_size = DEFAULT_PAGE_SIZE;
	}

	return storage;
}

void *MEM_storage_malloc_func(char *filename, int line, MEM_Storage storage, size_t size) 
{
	int cell_num;
	MemoryPage *new_page;
	void 	*p;

	cell_num = ((size - 1) / CELL_SIZE) + 1;

	if (storage->page_list != NULL && (storage->page_list->use_cell_num + cell_num < storage->page_list->cell_num)) {
		p = &(storage->page_list->cell[storage->page_list->use_cell_num]);
		storage->page_list->use_cell_num += cell_num;
	} else {
		int alloc_cell_num;

		alloc_cell_num = larger(cell_num, storage->current_page_size);

		new_page = MEM_malloc_func(filename, line, sizeof(MemoryPage) + CELL_SIZE * (alloc_cell_num - 1));
		new_page->next = storage->page_list;
		new_page->cell_num = alloc_cell_num;
		storage->page_list = new_page;

		p = &(new_page->cell[0]);
		new_page->use_cell_num = cell_num;
	}

	return p;
}