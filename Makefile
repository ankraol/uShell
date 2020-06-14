NAME = ush

ROOT_A = libmx.a \

LIB_A = ./libmx/libmx.a \

HEADER = -I inc \
	-I libmx/inc \

FILES = main \
	mx_read_env \
	mx_strjoin_two \
	mx_pipe_rec \
	mx_redirection \
	mx_fd_change \
	mx_works_queue \
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
	mx_jobSplit \
	mx_jobDup \
	mx_removeSlash \
	mx_ush_loop \
	mx_exit_func \
	mx_set_builstuct \
	mx_read_line \
	mx_struct_flag_cd \
	mx_create_file \
	mx_falid_files \
	mx_delete_Extra \
	mx_write_str_to_strstr \
	mx_for_redir_four \
	mx_deleteTasks \
	mx_two_child \
	mx_logic_pushBack \
	mx_deleteExtraSpaces \
	mx_job_deleteExtra \
	mx_create_file_echo \
	mx_struct_flag_echo \
	mx_checkSame \

ROOT_C = $(addsuffix ".c", $(FILES))

SRC = $(addprefix "src/", $(ROOT_C))

ROOT_O = $(addsuffix ".o", $(FILES))

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic #-g3 -glldb -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined

all: install clean

install:
	@make -sC libmx $@
	@cp $(SRC) .
	@cp $(LIB_A) .
	@clang $(CFLAGS) -c $(ROOT_C) $(HEADER)
	@clang $(CFLAGS) -ltermcap $(ROOT_O) $(ROOT_A) -o $(NAME) $(HEADER)
	@mkdir -p obj
	@cp $(ROOT_O) obj/
	@rm -rf $(ROOT_O)

uninstall: clean
	@make -C libmx uninstall
	@rm -rf $(NAME)

clean:
	@make -C libmx clean
	@rm -rf $(ROOT_O)
	@rm -rf $(ROOT_C)
	@rm -rf $(ROOT_A)
	@rm -rf obj

reinstall: uninstall install
