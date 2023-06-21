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
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

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
	char				*tmp;
	int					orphan;
	int					symlink;
	struct s_lst		*env;
	struct s_struct		*pex;
	struct sigaction	sigact[3];
	struct stat			stat;
};

// ************************** INIT ************************** \\

// init/init.c
void					ft_lstadd_back(struct s_lst **lst, struct s_lst *new);
struct s_lst			*ft_lstnew(struct s_shell *ms, char *str);
void					init(struct s_shell *ms, char **envp);
// init/init_env.c
void					increaseshlvl(struct s_shell *ms);
void					ft_setpwd(struct s_shell *ms);
void					recreatepwd(struct s_shell *ms);
void					createminienv(struct s_shell *ms);
void					ft_setenv(struct s_shell *ms, char **envp);

// ************************** PROG ************************** \\

// signals.c
void					ft_sigquit(int sig);
void					ft_sigint(int sig);
void					*ft_memset(void *s, int c, size_t n);

// ************************ PARSING ************************ \\

// parsing/parsing.c
int						parser(struct s_shell *ms);
// parsing/checkorphans
int						isspecial(char c);
// parsing/separator.c
t_cmd					*split_pipe(char *str);
// utils/lst.c
void					ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
struct s_cmd			*ft_lstnew_cmd(char **str, char **redir, char **built);
int						checkorphanquote(char *line);
int						checkorphanbracket(char *line);

// ************************ BUILT-INS ************************ \\

// builtins/builtins.c
void					ft_exit(struct s_shell *ms, char **tab);
int						ft_pwd(struct s_shell *ms);
int						ft_unset(struct s_shell *ms, char **tab);
int						ft_env(struct s_shell *ms, char **tab);
// builtins/builtins_echo.c
int						ft_echo_isfulln(char *str);
int						ft_echo(char **tab);
// builtins/builtins_export.c
int						ft_export_newnode(struct s_shell *ms, char *str);
int						ft_export_oldnode(struct s_lst *node, char *str);
int						ft_export_refreshenv(struct s_shell *ms, char *str,
							int equal);
int						ft_export(struct s_shell *ms, char **tab);
// builtins/builtins_export2.c
int						ft_export_isvalid(char c, int i);
int						ft_export_searchequal(char *str);
int						ft_export_parsing(char *str);
// builtins/builtins_cd.c
int						ft_cd_home(struct s_shell *ms, char *tmp);
int						ft_cd_oldpwd(struct s_shell *ms, char *tmp);
int						ft_cd_nothome(struct s_shell *ms, char *str, char *tmp);
int						ft_cd(struct s_shell *ms, char **tab);
// builtins/builtins_cd2.c
void					ft_echo_actualizepwd(struct s_shell *ms);
void					ft_echo_changeenv(struct s_shell *ms, char *tmp,
							char *str);
char					*ft_cd_symlink(struct s_shell *ms, char *tmp,
							char *str);
void					ft_echo_actualizeenv(struct s_shell *ms, char *tmp);

// ************************* UTILS ************************* \\

// utils/utils.c
int						ft_strlen(char *str);
char					*ft_strjoin(char *s1, char *s2);
char					*ft_strdup(char *s);
int						ft_atoi(char *nptr);
int						ft_strncmp(char *s1, char *s2, size_t n);
// utils/utils_env.c
char					*ft_strjoinenv(char *s1, char c, char *s2);
char					*ft_substr(char *s, int start, int len);
char					*ft_strnstr(char *big, char *little, int equal);
struct s_lst			*ft_getenv(struct s_shell *ms, char *str);
char					*ft_itoa(int nb);
// utils/utils_env2.c
int						countvalablenodes(struct s_lst *lst);
char					**listtotab(struct s_shell *ms);
// utils/ft_split.c
char					**ft_split(char *s, char c);
// utils/frees.c
void					ft_lstclear(struct s_lst *lst);
void					freesplit(char **strmalloc);
void					frees(struct s_shell *ms, int code);
void					throwerror(struct s_shell *ms, char *str);
// utils/minilib.c
void					*ft_calloc(size_t nmemb, size_t size);
void					ft_bzero(void *s, size_t n);
int						ft_strcmp(char *s1, char *s2);
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

#endif
