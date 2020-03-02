NAME = ush

HEADER = header.h \

FILES = main \
	example \
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
	mx_pipe_rec \
	mx_ush_execute \
	mx_itoa \
	mx_redirection \
	mx_fd_change \
	mx_command_cut \
	mx_file_to_str \
	mx_printstr \
	mx_works_queue \
	mx_strcmp\
	mx_history_use \

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
	@clang $(CFLAGS) -ltermcap $(ROOT_O) -o $(NAME)
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
