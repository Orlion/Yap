#define STRING_ALLOC_SIZE 	(256)

static int st_string_literal_buffer_size = 0;
static char *st_string_literal_buffer = NULL;
static int st_string_literal_buffer_alloc_size = 0;

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

DVM_Char *dkc_close_string_literal()
{
	DVM_Char *new_str;
	int new_str_len;

	dkc_add_string_literal('\0');
	new_str_len = dvm_mbstows_len(st_string_literal_buffer);
	if (new_str_len < 0) {
		dkc_compiler_error(dkc_get_current_compiler()->current_line_number, "Bad char");
	}
	new__str = MEM_malloc(sizeof(DVM_Char) * (new_str_len+1));
	dvm_mbstowcs(st_string_literal_buffer, new_str);

	return new_str;
}

char *dkc_create_identifier(char *str)
{
	char *new_str;

	new_str = dkc_malloc(strlen(str) + 1);

	strcpy(new_str, str);

	return new_str;
}