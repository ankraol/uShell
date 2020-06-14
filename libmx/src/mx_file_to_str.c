#include "libmx.h"

char *mx_file_to_str(const char *file){
	int size = 0;
	int p = open(file, O_RDONLY);
	char c;
		if (p < 0) {
			return NULL;
		}
		if (p > 0) {
			while(read(p, &c, 1)){
				size++;
			}
		close(p);
		p = open(file, O_RDONLY);
		char *str = mx_strnew(size);
		read(p, str, size);
		close(p);
		return str;
		}
	return NULL;
}

