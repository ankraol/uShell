NAME = libmx.a

HEADER = libmx.h \

FILES = mx_count_words \
	mx_strnew \
	mx_strsplit \
	mx_strlen \
	mx_del_strarr \
	mx_strjoin \
	mx_strcat \
	mx_strdel \
	mx_itoa \
	mx_file_to_str \
	mx_printstr \
	mx_strcmp \
	mx_printchar \
	mx_strcpy \
	mx_strdup \
	mx_strncmp \
	mx_strstr \
	mx_isdigit \

INC_H = $(addprefix "inc/", $(HEADER))

ROOT_C = $(addsuffix ".c", $(FILES))

SRC_C = $(addprefix "src/", $(ROOT_C))

ROOT_O = $(addsuffix ".o", $(FILES))

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: install clean

install:
	@cp $(SRC_C) .
	@cp $(INC_H) .
	@clang $(CFLAGS) -c $(ROOT_C)
	@mkdir -p obj
	@cp $(ROOT_O) obj/
	@ar -rc $(NAME) $(ROOT_O)
	@rm -rf $(ROOT_O)

uninstall:
	@rm -rf $(NAME)

clean:
	@rm -rf $(ROOT_O)
	@rm -rf $(ROOT_C)
	@rm -rf $(HEADER)
	@rm -rf obj

reinstall: uninstall install
