# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apayen <apayen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 11:13:47 by apayen            #+#    #+#              #
#    Updated: 2023/05/24 16:15:48 by apayen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
HEADER = minishell.h

SRC = minishell.c	\
		init.c	\
		utils.c	\
		ft_split.c	\
		parsing.c	\
		builtins.c	\
		builtins_cd.c	\
		frees.c
OBJ = $(SRC:.c=.o)

CC = cc
FLAGS = -Wall -Wextra -Werror -g3
RM = rm -f

all : $(NAME)

$(NAME) : $(OBJ) $(HEADER)
		$(CC) $(FLAGS) $(OBJ) -lreadline -o $(NAME)

%.o : %.c
		$(CC) $(FLAGS) -c -o $@ $^

clean :
		$(RM) $(OBJ) $(BOBJ)

fclean : clean
		$(RM) $(NAME)

re : fclean
		make all

.PHONY: all clean fclean
