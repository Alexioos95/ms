# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 11:13:47 by apayen            #+#    #+#              #
#    Updated: 2023/06/21 10:16:54 by eewu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
HEADER = header.h

SRC = $(addprefix $(OBJDIR)/,				\
		minishell.c							\
		init.c								\
		signals.c							\
		parsing/parsing.c					\
		parsing/checkfororphans.c			\
		parsing/separator.c					\
		builtins/builtins.c					\
		builtins/builtins_cd.c				\
		builtins/builtins_export.c			\
		utils/pipex/pipex.c					\
		utils/pipex/pipex_minilib.c			\
		utils/pipex/pipex_util.c			\
		utils/pipex/pipex_open.c			\
		utils/pipex/pipex_close.c			\
		utils/pipex/pipex_gnl.c				\
		utils/pipex/pipex_lst.c				\
		utils/pipex/pipex_init.c			\
		utils/utils.c						\
		utils/lst.c							\
		utils/minilib.c						\
		utils/ft_split.c					\
		utils/ft_splitline.c				\
		utils/utils_env.c					\
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
