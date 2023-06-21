/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libpipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:03:12 by eewu              #+#    #+#             */
/*   Updated: 2023/06/20 14:38:18 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPIPEX_H
# define LIBPIPEX_H

// # define _GNU_SOURCE

# include <errno.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <limits.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct cmd_lst
{
	char			**tab;
	struct cmd_lst	*next;
	int				i;
	char			pad[4];
}					t_list;

typedef struct main
{
	int				count;
	int				i;
	int				eror;
	int				in[2];
	int				out;
	int				bhole;
	int				status;
	int				in_rok;
	int				pipe;
	int				cmd_i;
	char			pad3[4];
	int				**fds;
	int				fd[2];
	int				nb_cmd;
	int				hdoc;
	int				ac;
	char			pad[4];
	pid_t			*pids;
	char			*limit;
	char			*cmd_join;
	char			**s_ev;
	char			**ev;
	char			**av;
	t_list			*head;
	struct cmd_lst	*cmd;
}					t_struct;

int			ft_printf(const char *c, ...);
int			ft_putchar(char c);
int			ft_putstr(char *str);
int			ft_bool_args(char str);
int			ft_check_args(char str, va_list	args);
int			ft_hexa(unsigned int n, char c);
int			ft_hexa_check(unsigned long int n);
int			ft_hexa_dress(unsigned long int n);
int			ft_putnbr(int n);
int			ft_put_unsigned_nbr(unsigned int n);

void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
char		**ft_split(char *s, char c);
char		*ft_join(char *s1, char const *s2);
char		*ft_strlcat(char *dst, const char *src, int size);
char		*ft_strlcpy(char *dest, const char *src);
size_t		ft_strlen(const char *s);
t_list		*ft_lstnew(char **cmd, int i);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new, t_struct *m);
void		ft_lstclear(t_list **lst);
int			ft_lstsize(t_list *lst);

void		ft_pipex(t_struct *main, char *out, char *in);
void		find_cmd(t_struct *main);
void		ft_list_tab(t_struct *main);
void		ft_access(t_struct *m, int i, int j, int path);
void		ft_free_process(t_struct *main, int r) __attribute__((noreturn));
void		ft_cmdex(char **cmd, char **ev, t_struct *main)
			__attribute__((noreturn));
void		ft_pipe(t_struct *m);
int			ft_fdspipe(t_struct *m);
void		ft_fork(t_struct *m);
void		ft_process(t_struct *main, char *out);
void		ft_openin(t_struct *main, char *in);
void		ft_openout(t_struct *main, char *out);
void		ft_printheredoc(t_struct *m);
void		ft_closeoutin(t_struct *m);
void		ft_mallocpipe(t_struct *m);
void		ft_free_tab(char **tab);
void		ft_childprocess(t_struct *m, char *out)
			__attribute__((noreturn));
void		ft_dupcheck(int fd, int stdfd, t_struct *m);
void		ft_closefds(t_struct *m);
void		ft_freefds(t_struct *m);
int			ft_error(char *ft, char *error, int pid, t_struct *m);
int			check_path(char *tab_env);
t_struct	*ft_init(t_struct *main, int ac, char **av, char **ev);

char		*get_next_line(int fd);
char		*ft_gnljoin(char *curr, char *str, int backsn, int r);
void		ft_clear_buf(char *buf, char *bsn_i, int after);
char		*ft_read(int start, char *stash, int fd, char *buf);
int			ft_backsn(char *buf);

// ***********************Test******************************* //
void		print_allcmd(t_struct *main);
void		print_list(char *tab, int i);
void		print_tab(char **tab);
// ***********************Test******************************* //

#endif
