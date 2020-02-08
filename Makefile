NAME = ush

HEADER = header.h \

FILES = example \
	mx_strsplit \
	mx_count_words \
	mx_strnew \
	mx_strlen \
	mx_read_env \
	mx_del_strarr \
	mx_strdel \
	mx_strjoin_two \
	mx_strjoin \
	mx_strcat \
	mx_parcing \
	mx_execute_func \

INC_H = $(addprefix "inc/", $(HEADER))

ROOT_C = $(addsuffix ".c", $(FILES))

SRC = $(addprefix "src/", $(ROOT_C))

ROOT_O = $(addsuffix ".o", $(FILES))

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: install clean

install:
	@cp $(SRC) .
	@cp $(INC_H) .
	@clang $(CFLAGS) -c $(ROOT_C)
	@clang $(CFLAGS) $(ROOT_O) -o $(NAME)
	@mkdir -p obj
	@cp $(ROOT_O) obj/
	@rm -rf $(ROOT_O)

uninstall: clean
	@rm -rf $(NAME)

clean:
	@rm -rf $(ROOT_O)
	@rm -rf $(ROOT_C)
	@rm -rf $(HEADER)
	@rm -rf obj

reinstall: uninstall install
