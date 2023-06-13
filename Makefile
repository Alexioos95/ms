# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 11:13:47 by apayen            #+#    #+#              #
#    Updated: 2023/06/13 11:17:34 by eewu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
HEADER = header.h

SRC = $(addprefix $(OBJDIR)/,		\
		minishell.c					\
		init.c						\
		signals.c					\
		parsing/parsing.c			\
		parsing/checkfororphans.c	\
		builtins/builtins.c			\
		builtins/builtins_cd.c		\
		builtins/builtins_export.c	\
		utils/utils.c				\
		utils/ft_split.c			\
		utils/utils_env.c			\
		utils/frees.c)

OBJ = $(SRC:.c=.o)

OBJDIR	=	obj

CC =	 cc
FLAGS = -Wall -Wextra -Werror -g3
RM =	rm -rf

all : $(NAME)

$(NAME) : $(OBJ) $(HEADER)
		$(CC) $(FLAGS) $(OBJ) -lreadline -o $(NAME)

$(OBJDIR)/%.o : %.c
		@mkdir -p $(@D)
		$(CC) $(FLAGS) -c -o $@ $^

clean :
		$(RM) $(OBJ) $(BOBJ) $(OBJDIR)

fclean : clean
		$(RM) $(NAME)

re :	fclean
		make all

.PHONY: all clean fclean re
