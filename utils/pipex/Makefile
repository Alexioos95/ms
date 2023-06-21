# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 10:26:52 by eewu              #+#    #+#              #
#    Updated: 2023/06/20 10:37:17 by eewu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 	./libpipex.a

PRJEXEC	= 	pipex

SRCS	=	$(addprefix $(OBJDIR)/,	\
			./pipex.c				\
			./pipex_ftprintf1.c		\
			./pipex_ftprintf2.c		\
			./pipex_ftprintf3.c		\
			./pipex_minilib.c		\
			./pipex_parth.c			\
			./pipex_split.c			\
			./pipex_util.c			\
			./pipex_test.c			\
			./pipex_open.c			\
			./pipex_close.c			\
			./pipex_gnl.c			\
			./pipex_lst.c			\
			./main.c)

OBJS	=	$(SRCS:.c=.o)

OBJDIR	=	obj

CC		=	scan-build-12 cc

CFLAGS	+=	-Wall -Wextra -Weverything -g3

LIB		=	-L. -lpipex

RM		=	rm -rf

CLEAN	=	clean

HEADER 	=	./libpipex.h

$(OBJDIR)/%.o : %.c
			@mkdir -p $(@D)
			$(CC) $(CFLAGS) -c -o $@ $^
		
all		: 	$(NAME)

$(NAME)	:	$(OBJS) $(HEADER)
			@ar -rcs $(NAME) $(OBJS)
			$(CC) $(CFLAGS) $(LIB) -o $(PRJEXEC)

clean	:
			@$(RM) $(OBJS) $(OBJDIR)
		
fclean	:	clean
			@$(RM) $(NAME) $(PRJEXEC)

re		:	fclean 
			make --no-print-directory

.PHONY	:	all clean fclean re
		