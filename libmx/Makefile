NAME = libmx.a

HEADER = -I inc

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
	mx_isdigit

OBJ_DIR = obj/

SRC_DIR = src/

OBJ = $(FILES:%=$(OBJ_DIR)%.o)

SRC = $(FILES:%=$(SRC_DIR)%.c)


CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@clang $(HEADER) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ_DIR) $(OBJ)
	@ar rcs $(NAME) $(OBJ)

clean:
	@rm -rf $(OBJ_DIR)

uninstall: clean
	@rm -rf $(NAME)

reinstall: uninstall all
