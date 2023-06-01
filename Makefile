# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apayen <apayen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 11:13:47 by apayen            #+#    #+#              #
#    Updated: 2023/06/01 10:50:48 by apayen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
HEADER = minishell.h

SRC = $(addprefix $(OBJDIR)/,		\
		minishell.c					\
		init.c						\
		signals.c					\
		parsing.c					\
		builtins/builtins.c			\
		builtins/builtins_cd.c		\
		builtins/builtins_export.c	\
		utils/utils.c				\
		utils/ft_split.c			\
		utils/utils_env.c			\
		utils/frees.c)

OBJ = $(SRC:.c=.o)

OBJDIR	=	obj

CC =	cc
FLAGS =	-Wall -Wextra -Werror -g3
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

re : fclean
		make all

.PHONY: all clean fclean re
