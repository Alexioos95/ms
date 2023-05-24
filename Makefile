# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 11:13:47 by apayen            #+#    #+#              #
#    Updated: 2023/05/24 15:31:29 by eewu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
HEADER = minishell.h

SRC = $(addprefix $(OBJDIR)/,	\
		minishell.c				\
		init.c					\
		utils.c					\
		ft_split.c				\
		parsing.c				\
		builtins.c        \
		frees.c)
    
OBJ = $(SRC:.c=.o)

OBJDIR	=	obj

CC = cc
FLAGS = -Wall -Wextra -Werror -g3
RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJ) $(HEADER)
		$(CC) $(FLAGS) $(OBJ) -lreadline -o $(NAME)

$(OBJDIR)/%.o : %.c
		mkdir -p $(@D)
		$(CC) $(FLAGS) -c -o $@ $^

clean :
		$(RM) $(OBJ) $(BOBJ) $(OBJDIR)

fclean : clean
		$(RM) $(NAME)

re : fclean
		make all

.PHONY: all clean fclean re
