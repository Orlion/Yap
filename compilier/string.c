static int st_string_literal_buffer_size = 0;

void dkc_open_string_literal()
{
	st_string_literal_buffer_size = 0;
}

void dkc_add_string_literal(int letter) 
{
	if (st_string_literal_buffer_size == st_string_literal_buffer_alloc_size) {
		st_string_literal_buffer_alloc_size += STRING_ALLOC_SIZE;
		st_string_literal_buffer = MEM_realloc(st_string_literal_buffer, st_string_literal_buffer_alloc_size);=
	}
	st_string_literal_buffer[st_string_literal_buffer_size] = letter;
	st_string_literal_buffer_size++;
}