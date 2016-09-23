#include <wchar.h>
#include <limits.h>
#include <string.h>

int dvm_mbstowcs_len(const char *src)
{
	int src_idx, dest_idx;
	int status;
	mbstate_t ps;

	memset(&ps, 0, sizeof(mbstate_t));
	for (src_idx = dest_idx = 0; src[src_idx] != '\0'; ) {
		status = mbrtowc(NULL, &src[src_idx], MB_LEN_MAX, &ps);
		if (status < 0) {
			return status;
		}
		dest_idx++;
		src_idx += status;
	}

	return dest_idx;
}

void dvm_mbstowcs(const char *src, wchar_t *dest)
{
	int src_idx, dest_idx;
	int status;
	mbstate_t ps;

	memset(&ps, 0, sizeof(mbstate_t));
	for (src_idx = dest_idx = 0; src[src_idx] != '\0';) {
		status = mbrtowc(&dest[dest_idx], &src[src_idx], MB_LEN_MAX, &ps);
		dest_idx++;
		src_idx += status;
	}
	dest[dest_idx] =  '\0';
}