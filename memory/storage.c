typedef MemoryPage_tag MemoryPage;
typedef MemoryPage *MemoryPageList;

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
}

struct MEM_Storage_tag {
	MemoryPageList	page_list;
	int				current_page_size;
}