# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/09 16:07:30 by tblink            #+#    #+#              #
#    Updated: 2022/02/11 18:30:14 by dgallard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = libft.a
SRC     = ft_strnstr.c \
          ft_isalpha.c \
          ft_isdigit.c \
          ft_isalnum.c \
		  ft_itoa.c \
		  ft_putstr_fd.c \
		  ft_strchr.c \
		  ft_strdup.c \
		  ft_strjoin.c \
		  ft_strlen.c \
		  ft_strncmp.c \
		  ft_substr.c \
		  ft_putchar_fd.c

OBJ     = $(SRC:.c=.o)

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror
.c.o:
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
all:  $(NAME)
bonus: @$(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
clean:
	@rm -rf $(OBJ)
fclean: clean
	@rm -rf $(NAME)
re: @fclean all
