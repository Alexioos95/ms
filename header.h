/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:06:58 by apayen            #+#    #+#             */
/*   Updated: 2023/06/02 10:19:54 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <errno.h>
# include <fcntl.h>
# include <stdint.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

enum					e_enum
{
	CONST,
	ALLOC
};

typedef struct s_cmd
{
	char				**split;
	char				**redirection;
	char				**builtin;
	struct s_cmd		*next;
	struct s_cmd		*back;
	struct s_shell		*ms;
}						t_cmd;

struct					s_lst
{
	int					print;
	enum e_enum			flag;
	char				*line;
	struct s_lst		*next;
	struct s_shell		*ms;
};

typedef struct s_list
{
	char			**tab;
	struct s_list	*next;
	int				i;
	char			pad[4];
}					t_list;

typedef struct s_struct
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
	struct s_list	*cmd;
}					t_struct;

struct					s_shell
{
	char				*line;
	char				*pwdpath;
	char				*oldpwdpath;
	char				**split;
	int					orphan;
	struct s_lst		*env;
	struct s_struct		*pex;
	struct sigaction	sigact[3];
	void				*lsthead;
};

// init.c
void					init(struct s_shell *ms, char **envp);
void					ft_setenv(struct s_shell *ms, char **envp);
struct s_lst			*ft_lstnew(struct s_shell *ms, char *str);
void					ft_lstadd_back(struct s_lst **lst, struct s_lst *new);
// signals.c
void					*ft_memset(void *s, int c, size_t n);
void					ft_sigint(int sig);
void					ft_sigquit(int sig);
// parsing/parsing.c
int						parser(struct s_shell *ms);
// parsing/checkfororphans.c
int						checkorphanbracket(char *line);
int						checkorphanquote(char *line);
int						isspecial(char c);
// parsing/separator.c
t_cmd					*split_pipe(char *str);
// ft_split.c
// char					**ft_splitline(char *s, char c);
// ft_splitline.c
char					**ft_split(char *s, char c);
// utils/frees.c
void					frees(struct s_shell *ms, int code);
void					freesplit(char **strmalloc);
void					ft_lstclear(struct s_shell *ms, struct s_lst *lst);
// utils/utils.c
int						ft_strlen(char *str);
int						ft_tablen(char **str);
int						ft_atoi(char *nptr);
char					*ft_strdup(char *s);
char					*ft_strjoin(char *s1, char *s2);
// utils/lst.c
void					ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
struct s_cmd			*ft_lstnew_cmd(char **str, char **redir, char **built);
// utils/utils_env.c
char					*ft_strnstr(char *big, char *little, int equal);
char					*ft_strjoinenv(char *s1, char c, char *s2);
char					*ft_substr(char *s, int start, int len);
struct s_lst			*ft_getenv(struct s_shell *ms, char *str);
// utils/minilib.c
void					*ft_calloc(size_t nmemb, size_t size);
void					ft_bzero(void *s, size_t n);
int						ft_strcmp(char *s1, char *s2);
// builtins/builtins.c
void					ft_exit(struct s_shell *ms, char *opt);
int						ft_echo(char *opt, char *str);
int						ft_env(struct s_shell *ms, char *opt);
int						ft_unset(struct s_shell *ms, char *str, char *opt);
int						ft_pwd(struct s_shell *ms);
// builtins/builtins_cd.c
int						ft_cd(struct s_shell *ms, char *str);
int						ft_cdhome(struct s_shell *ms);
int						ft_cdenv(struct s_shell *ms, char *tmp, char *str);
// builtins/builtins_export.c
int						ft_export(struct s_shell *ms, char *str);
int						searchequal(char *str);
int						newnode(struct s_shell *ms, char *str);
// utils/pipex/pipex.c
void					ft_process(t_struct *main, char *out);
void					ft_pipex(t_struct *main, char *out, char *in);
// utils/pipex/pipex_util.c
void					ft_pipe(t_struct *m);
int						ft_fdspipe(t_struct *m);
void					ft_fork(t_struct *m);
void					ft_childprocess(t_struct *m, char *out)
						__attribute__((noreturn));
void					ft_cmdex(char **cmd, char **ev, t_struct *main)
						__attribute__((noreturn));
// utils/pipex/pipex_open.c
void					ft_openin(t_struct *main, char *in);
void					ft_openout(t_struct *main, char *out);
void					ft_dupcheck(int fd, int stdfd, t_struct *m);
int						ft_error(char *ft, char *error, int pid, t_struct *m);
// utils/pipex/pipex_init.c
void					ft_printheredoc(t_struct *m);
void					ft_mallocpipe(t_struct *m);
void					ft_forkex(t_struct	*m, int in, int out);
t_struct				*ft_init(t_struct *main, int ac, char **av, char **ev);
// utils/pipex/pipex_close.c
void					ft_free_process(t_struct *main, int r)
						__attribute__((noreturn));
void					ft_free_tab(char **tab);
void					ft_closeoutin(t_struct *m);
void					ft_closefds(t_struct *m);
void					ft_freefds(t_struct *m);
// utils/pipex/
// utils/pipex/
// utils/pipex/

#endif
