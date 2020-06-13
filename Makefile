NAME = ush

HEADER = header.h \

FILES = main \
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
	mx_pipe_rec \
	mx_itoa \
	mx_redirection \
	mx_fd_change \
	mx_command_cut \
	mx_file_to_str \
	mx_printstr \
	mx_works_queue \
	mx_strcmp \
	mx_logicOp \
	mx_substitute \
	mx_history_use \
	mx_input_key \
	mx_main_cycle_key \
	mx_get_width \
	mx_one_cycle \
	mx_two_cycle \
	mx_four_cycle \
	mx_byte_check \
	mx_arrow_use \
	mx_arrow_up \
	mx_arrow_down \
	mx_add_to_str \
	mx_aliasList \
	mx_aliasSearch \
	mx_implementarion_of_builtin_commands \
	mx_cd_command \
	mx_logic_path \
	mx_pwd \
	mx_echo \
	mx_back_to_str \
	mx_pid_list \
	mx_which \
	mx_printerr \
	mx_printchar \
	mx_strdup \
	mx_strcpy \
	mx_is_buildin \
	mx_fg_command \
	mx_tokenSplit \
	mx_varList \
	mx_for_fg_command \
	mx_export_list \
	mx_command_export \
	mx_for_export_com \
	mx_valid_flag_env \
	mx_unset_command \
	mx_env_list \
	mx_env_list_find \
	mx_ush_execute_env \
	mx_cd_two_args \
	mx_comand_env_one \
	mx_comand_env_two \
	mx_comand_env_three \
	mx_comand_env_four \
	mx_read_env_two \
	mx_aliasList_func \
	mx_tokenSplit_one \
	mx_subLine \
	mx_subExec \
	mx_command_cut_four \
	mx_command_cut_five \
	mx_command_cut_nine \
	mx_command_cut_therteen \
	mx_cycleOne \
	mx_mistake \
	mx_expandParameter \
	mx_expandedLine \
	mx_findParameter \
	mx_expand_parts \
	mx_exit_commnad \
	mx_findTilda \
	mx_pipeCreate \
	mx_outputCreate \
	mx_inputCreate \
	mx_taskCreate \
	mx_customSplit \
	mx_customDup \

INC_H = $(addprefix "inc/", $(HEADER))

ROOT_C = $(addsuffix ".c", $(FILES))

SRC = $(addprefix "src/", $(ROOT_C))

ROOT_O = $(addsuffix ".o", $(FILES))

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic #-g3 -glldb -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined

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
