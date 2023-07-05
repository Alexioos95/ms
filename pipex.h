/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:03:12 by eewu              #+#    #+#             */
/*   Updated: 2023/06/22 13:55:54 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdint.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

typedef struct s_cmd_lst
{
	char				**tab;
	struct s_cmd_lst	*next;
	int					i;
	char				pad[4];
}						t_list;

typedef struct s_pipex
{
	int					count;
	int					i;
	int					eror;
	int					in[2];
	int					out;
	int					bhole;
	int					status;
	int					in_rok;
	int					out_rok;
	int					pipe;
	int					cmd_i;
	char				pad3[4];
	int					**fds;
	int					fd[2];
	int					nb_cmd;
	int					hdoc;
	int					ac;
	char				pad[4];
	pid_t				*pids;
	char				*limit;
	char				*cmd_join;
	char				**s_ev;
	char				**ev;
	char				**av;
	struct s_cmd_lst	*head;
	struct s_cmd_lst	*cmd;
}						t_struct;

// pipex/pipex.c
void					ft_process(t_struct *main, char *out);
void					ft_pipex(t_struct *main, char *out, char *in);
// pipex/pipex_util.c
void					ft_pipe(t_struct *m);
int						ft_fdspipe(t_struct *m);
void					ft_fork(t_struct *m);
void					ft_childprocess(t_struct *m, char *out)
						__attribute__((noreturn));
void					ft_cmdex(char **cmd, char **ev, t_struct *main)
						__attribute__((noreturn));
// pipex/pipex_open.c
void					ft_openin(t_struct *main, char *in);
void					ft_openout(t_struct *main, char *out);
void					ft_dupcheck(int fd, int stdfd, t_struct *m);
int						ft_error(char *ft, char *error, int pid, t_struct *m);
// pipex/pipex_init.c
void					ft_printheredoc(t_struct *m);
void					ft_mallocpipe(t_struct *m);
void					ft_forkex(t_struct	*m, char *in, char *out);
t_struct				*ft_init(t_struct *main, int nb_cmd \
						, t_list *pars_lst, char **ev);
// pipex/pipex_close.c
void					ft_free_process(t_struct *main, int r)
						__attribute__((noreturn));
void					ft_free_tab(char **tab);
void					ft_closeoutin(t_struct *m);
void					ft_closefds(t_struct *m);
void					ft_freefds(t_struct *m);
// pipex/pipex_lst.c
int						ft_lstsize(t_list *lst);
void					ft_lstclearpipex(t_list **lst);
t_list					*ft_lstlast(t_list *lst);


#endif
