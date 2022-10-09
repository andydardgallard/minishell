NAME = minishell

SRC = main.c utils_crt_path_arr_norm.c utils_lexer_norm.c ft_split.c utils_functions_norm.c utils_arrs_norm.c  unset_norm.c utils_func_norm.c\
		utils_signals_norm.c export_norm.c utils_arrs_help_norm.c\
		utils_arrs_export_norm.c utils_arrs_helper_one_norm.c utils_arrs_helper_two_norm.c utils_functions_norm.c utils_signals_norm.c\
		ft_split_modif_norm.c for_parser_norm.c utils_split_modif_norm.c utils_for_parser_norm.c utils_parser_second_norm.c\
		utils_parser_norm.c parser_norm.c redirect_one_norm.c redirect_two_norm.c redirect_three_norm.c redirect_four_norm.c utils_connect_one_norm.c\
		utils_main_three_norm.c utils_main_five_norm.c utils_main_one_norm.c utils_main_two_norm.c utils_main_four_norm.c

OBJ = $(SRC:.c=.o)

CC = gcc -Wall -Wextra -Werror -I /Users/$(USER)/.brew/opt/readline/include

HEADERS	= 		-Ilibft

LIBFT 	= 		./libft/libft.a

all: $(libft) $(NAME)

$(%.o): $(%.c)
				$(CC) -o $@ -c $(HEADERS) $^

$(LIBFT):
				make -C libft
				@echo "\nMake LIBFT done\n"

$(NAME): $(OBJ)
				@echo "\nCompiling --->"
				make -C libft
				@$(CC) -o $@ $(LIBFT) $^ -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
				@echo "Done\n"

clean:
				@make clean -C libft
				@rm -rf $(OBJ)
				@echo "\nDelete objects\n"

fclean: clean
				@make fclean -C libft
				@rm -rf $(NAME)
				@echo "\nRemoved all files\n"

re: 			mostlyclean all
				@echo  "\nRemake\n"

.PHONY:			all clean mostlyclean fclean re
