# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apayen <apayen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 11:13:47 by apayen            #+#    #+#              #
#    Updated: 2023/06/20 16:32:53 by apayen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		minishell
HEADER =	header.h

SRC = $(addprefix $(OBJDIR)/,		\
		minishell.c					\
		signals.c					\
		init/init.c					\
		init/init_env.c				\
		parsing/parsing.c			\
		parsing/checkorphans.c		\
		builtins/builtins.c			\
		builtins/builtins_cd.c		\
		builtins/builtins_cd2.c		\
		builtins/builtins_echo.c	\
		builtins/builtins_export.c	\
		builtins/builtins_export2.c	\
		utils/utils.c				\
		utils/utils_env.c			\
		utils/utils_env2.c			\
		utils/ft_split.c			\
		utils/frees.c)

OBJ =	$(SRC:.c=.o)

OBJDIR	=	obj

CC =	cc
FLAGS =	-Wall -Wextra -Werror -g3
RM =	rm -rf

all :	$(NAME)

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
