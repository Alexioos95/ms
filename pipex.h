/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:03:12 by eewu              #+#    #+#             */
/*   Updated: 2023/08/02 10:56:59 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef PIPEX_H
// # define PIPEX_H
// // # define HEADER_H

// // # include "header.h"
// # include <errno.h>
// # include <fcntl.h>
// # include <stdint.h>
// # include <limits.h>
// # include <readline/history.h>
// # include <readline/readline.h>
// # include <signal.h>
// # include <stddef.h>
// # include <sys/stat.h>
// # include <sys/types.h>
// # include <unistd.h>
// # include <string.h>
// # include <sys/types.h>
// # include <sys/wait.h>
// # include <sys/stat.h>

// typedef struct s_cmd_lst
// {
// 	char				**tab;
// 	struct s_cmd_lst	*next;
// 	int					i;
// 	char				pad[4];
// }						t_cmd_lst;

// typedef struct s_pipex
// {
// 	int					count;
// 	int					i;
// 	int					eror;
// 	int					in[2];
// 	int					out;
// 	int					bhole;
// 	int					status;
// 	int					in_rok;
// 	int					out_rok;
// 	int					pipe;
// 	int					cmd_i;
// 	char				pad3[4];
// 	int					**fds;
// 	int					fd[2];
// 	int					nb_cmd;
// 	int					hdoc;
// 	int					ac;
// 	char				pad[4];
// 	pid_t				*pids;
// 	char				*limit;
// 	char				*cmd_join;
// 	char				**s_ev;
// 	char				**ev;
// 	char				**av;
// 	struct s_cmd_lst	*head;
// 	struct s_cmd_lst	*cmd;
// }						t_pipex;

// // pipex/pipex.c
// void			ft_process(t_pipex *m, t_shell *ms);
// void			ft_pipex(t_pipex *m, t_shell *ms);
// int				ft_start(t_shell *ms);
// // pipex/pipex_util.c
// void			ft_pipe(t_pipex *m);
// int				ft_fdspipe(t_pipex *m);
// void			ft_fork(t_pipex *m);
// void			ft_childprocess(t_pipex *m)
// 				__attribute__((noreturn));
// void			ft_cmdex(char **cmd, char **ev, t_pipex *m)
// 				__attribute__((noreturn));
// // pipex/pipex_open.c
// void			ft_openin(t_pipex *m, char *token, char *file);
// void			ft_openout(t_pipex *m, char *token, char *file);
// void			ft_dupcheck(int fd, int stdfd, t_pipex *m);
// int				ft_error(char *ft, char *error, int pid, t_pipex *m);
// // pipex/pipex_init.c
// void			ft_mallocpipe(t_pipex *m);
// void			ft_theone(t_pipex *m, t_shell *ms);
// t_pipex		*ft_init(t_pipex *m, int nb_cmd, char **ev);
// // pipex/pipex_close.c
// void			ft_free_process(t_pipex *m, int r)
// 				__attribute__((noreturn));
// void			ft_free_tab(char **tab);
// void			ft_closeoutin(t_pipex *m);
// void			ft_closefds(t_pipex *m);
// void			ft_freefds(t_pipex *m);
// // pipex/pipex_lst.c
// t_cmd_lst			*ft_pipex_lstnew(char **cmd, char *name, int i);
// t_cmd_lst			*ft_lstlast(t_cmd_lst *lst);
// void			ft_pipex_lstadd_back(t_cmd_lst **lst, \
//	t_cmd_lst *new, t_pipex *m);
// void			ft_lstclearpipex(t_cmd_lst **lst);
// int				ft_lstsize(t_cmd_lst *lst);

// #endif
