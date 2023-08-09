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
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
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

typedef struct s_builtins
{
	int					cd;
	int					pwd;
	int					exit;
	int					unset;
	int					env;
	int					echo;
	int					export;
}						t_builtins; // A quoi ca sert ?

typedef struct s_expand
{
	int				i;
	int				j;
	char			c;
	char			*split[3];
	char			*tmp;
	char			*buff;
	struct s_lst	*node;
	struct s_lexer	*lex;
	struct s_shell	*ms;
}						t_expand;

typedef struct s_tokens
{
	char				*token;
	char				*file;
	char				*pipe;
}						t_tokens;

typedef struct s_lexer
{
	char				*str;
	char				**tab;
	t_tokens			token;
	int					i;
	int					len;
	struct s_lexer		*next;
	struct s_lexer		*back;
}						t_lexer;

typedef struct s_lst
{
	int					print;
	char				*line;
	struct s_lst		*next;
	struct s_shell		*ms;
}						t_lst;

typedef struct s_redir
{
	struct s_tokens		token;
	struct s_redir		*next;
}						t_redir;

typedef struct s_cmd_lst
{
	char				**tab;
	char				*name;
	struct s_redir		*redirlst;
	struct s_cmd_lst	*next;
	int					i;
	char				pad[4];
}						t_cmd_lst;

typedef struct s_pipex
{
	int					count;
	int					i;
	int					eror;
	int					in[2];
	int					out;
	int					bhole;
	int					in_rok;
	int					out_rok;
	int					out_red;
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
	struct s_redir		*tokenhead;
	struct s_shell		*ms;
}						t_pipex;

typedef struct s_shell
{
	char				*line;
	char				*pwdpath;
	char				*oldpwdpath;
	char				**split;
	char				*tmp;
	int					orphan;
	int					nb_pipe;
	int					status;
	struct s_tokens		token;
	struct s_lst		*env;
	struct s_cmd		*cmd;
	struct s_pipex		*pex;
	struct s_lexer		*lexer;
	struct s_cmd_lst	*cmd_lst;
	struct sigaction	sigact[4];
}						t_shell;

// ************************** INIT ************************** //
// init/init.c
void		ft_lstadd_back(struct s_lst **lst, struct s_lst *new);
t_lst		*ft_lstnew(struct s_shell *ms, char *str);
t_tokens	ft_newtoken(char *token, char *file);
void		init(struct s_shell *ms, char **envp);
int			ft_nb_cmd(t_lexer *lexer);
// init/init_env.c
void		increaseshlvl(struct s_shell *ms);
void		ft_setpwd(struct s_shell *ms);
void		recreatepwd(struct s_shell *ms);
void		createminienv(struct s_shell *ms);
void		ft_setenv(struct s_shell *ms, char **envp);

// ************************ PIPEX ************************ //
// pipex/pipex.c
void		ft_dup_redir(t_pipex *m, t_cmd_lst *cmd);
void		ft_process(t_pipex *m);
void		ft_pipex(t_pipex *m);
int			ft_start(t_shell *ms);
// pipex/pipex_util.c
void		ft_pipe(t_pipex *m);
int			ft_fdspipe(t_pipex *m);
void		ft_fork(t_pipex *m);
void		ft_childprocess(t_pipex *m)
			__attribute__((noreturn));
void		ft_cmdex(char **cmd, char **ev, t_pipex *m)
			__attribute__((noreturn));
// pipex/pipex_util2.c
char		*ft_pipex_strlcpy(char *dest, const char *src);
char		*ft_pipex_strlcat(char *dest, const char *src, int size);
char		*ft_pipex_join(char *path, char *cmd);
// pipex/pipex_open.c
int			ft_openin(t_pipex *m, char *token, char *file);
int			ft_openout(t_pipex *m, char *token, char *file);
void		ft_dupcheck(int fd, int stdfd, t_pipex *m);
int			ft_error(char *ft, char *error, int pid, t_pipex *m);
// pipex/pipex_init.c
void		ft_mallocpipe(t_pipex *m);
void		ft_theone(t_pipex *m, t_shell *ms);
t_pipex		*ft_init(t_pipex *m, int nb_cmd, char **ev);
// pipex/pipex_close.c
void		ft_free_process(t_pipex *m, int r)
			__attribute__((noreturn));
void		ft_free_tab(char **tab);
void		ft_closeoutin(t_pipex *m);
void		ft_closefds(t_pipex *m);
void		ft_freefds(t_pipex *m);
// pipex/pipex_lst.c
t_cmd_lst	*ft_pipex_lstnew(char **cmd, char *name, int i);
t_cmd_lst	*ft_lstlast(t_cmd_lst *lst);
void		ft_pipex_lstadd_back(t_cmd_lst **lst, t_cmd_lst *new, t_pipex *m);
void		ft_lstclearpipex(t_cmd_lst **lst);
int			ft_lstsize(t_cmd_lst *lst);
// pipex/pipex_parsing.c
char		**ft_find_nodecmd(t_lexer **lexer);
void		ft_access(t_pipex *m, char **tab_cmd, int j, int p);
void		ft_cmd_list(t_pipex *m, t_shell *ms);
void		find_cmd(t_pipex *m, t_shell *ms);
// pipex/pipex_parsing2.c
t_redir		*ft_redir_lstnew(t_tokens token);
t_redir		*ft_redir_lstlast(t_redir *lst);
void		ft_redir_lstadd_back(t_redir **lst, t_redir *new, t_pipex *m);
void		ft_redir_in_cmd(t_pipex *m, t_lexer **lexer, t_cmd_lst *cmd);
void		ft_redir_list(t_pipex *m, t_shell *ms);
// pipex/pipex_test.c
void		print_allcmd(t_pipex *m);
void		print_list(char *tab, int i);
void		print_tab(char **tab);

// ************************ PARSING ************************ //
// parsing/parsing.c
int			parser(struct s_shell *ms);
int			ft_state(char c, int state);
int			ft_istoken(char c);
int			ft_isthereatoken(char *line, t_lexer **lexer);
void		ft_browse(t_shell *ms);
// parsing/checkorphans
int			isspecial(char c);
// parsing/lst_lexer.c
t_lexer		*ft_lexer_new(char *str, t_tokens token);
t_lexer		*ft_lstlast_lexer(t_lexer *head);
void		ft_lexer_addback(t_lexer **head, t_lexer *new);
void		ft_lstresetindex_lexer(t_lexer *head);
void		ft_lexer_delone(t_lexer **curr_node, int i);
// parsing/tokens.c
int			ft_goodtoken(char *line, t_tokens *token, char **word, int state);
int			ft_goodword(char *line, t_tokens *token, char **word, int state);
void		ft_add_tokenword(t_lexer *lexer, t_shell *ms);
void		ft_add_word_to_tab(t_lexer *lexer, t_shell *ms);
void		ft_tabptr(t_shell *ms, t_lexer *cmd, t_lexer *cmd2, int nb_tab);
// parsing/expand.c
void		ft_expand(struct s_lexer *lexer, struct s_shell *ms);
char		*ft_expand_start(struct s_expand *exp, char *str);
void		ft_expand_init(struct s_expand *exp, char *str, int i, int j);
void		ft_expand_replace(struct s_expand *exp, char *str);
void		ft_expand_dollar(struct s_expand *exp, char *str);
// parsing/expand_dquote.c
void		ft_expand_dquote(struct s_expand *exp, char *str);
void		ft_expand_dquotereplace(struct s_expand *exp);
// parsing/expand_utils.c
void		ft_expand_initstruct(struct s_expand *exp, t_shell *ms, t_lexer *lex);
int			isexp(char *str, int i, int j);
char		*ft_expand_join(struct s_expand *exp, char *s1, char *s2);
void		ft_expand_error(struct s_expand *exp);
// utils/lst.c
void		ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
t_cmd		*ft_lstnew_cmd(char **str, char **redir, char **built);
int			checkorphanquote(char *line);
int			checkorphanbracket(char *line);
void		ft_print_lexerlst(t_lexer *lst);

// ************************ BUILT-INS ************************ //
// builtins/builtins.c
void		ft_exit(struct s_shell *ms, char **tab);
int			ft_pwd(struct s_shell *ms);
int			ft_unset(struct s_shell *ms, char **tab);
int			ft_env(struct s_shell *ms, char **tab);
// builtins/builtins_echo.c
int			ft_echo_isfulln(char *str);
int			ft_echo(char **tab);
// builtins/builtins_export.c
int			ft_export_newnode(struct s_shell *ms, char *str);
int			ft_export_oldnode(struct s_lst *node, char *str);
int			ft_export_refreshenv(struct s_shell *ms, char *str, int equal);
int			ft_export(struct s_shell *ms, char **tab);
// builtins/builtins_export2.c
int			ft_export_isvalid(char c, int i);
int			ft_export_searchequal(char *str);
int			ft_export_parsing(char *str);
// builtins/builtins_cd.c
int			ft_cd_home(struct s_shell *ms, char *tmp);
int			ft_cd_oldpwd(struct s_shell *ms, char *tmp);
int			ft_cd_nothome(struct s_shell *ms, char *str, char *tmp);
int			ft_cd(struct s_shell *ms, char **tab);
// builtins/builtins_cd2.c
void		ft_cd_actualizepwd(struct s_shell *ms);
void		ft_cd_changeenv(struct s_shell *ms, char *tmp, char *str);
char		*ft_cd_proteccwd(struct s_shell *ms, char **tab, char *tmp);
void		ft_cd_actualizeenv(struct s_shell *ms, char *tmp);

// ************************* UTILS ************************* //
// utils/utils.c
int			ft_strlen(char *str);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strdup(char *s);
int			ft_atoi(char *nptr);
int			ft_tablen(char **str);
int			ft_strncmp(char *s1, char *s2, size_t n);
// utils/utils_env.c
char		*ft_strjoinenv(char *s1, char c, char *s2);
char		*ft_substr(char *s, int start, int len);
char		*ft_strnstr(char *big, char *little, int equal);
t_lst		*ft_getenv(struct s_shell *ms, char *str);
char		*ft_itoa(int nb);
// utils/utils_env2.c
int			countvalablenodes(struct s_lst *lst);
char		**listtotab(struct s_shell *ms);
char		*ft_subnstr(char *s, unsigned int start, size_t len);
// utils/ft_split.c
char		**ft_split(char *s, char c);
// utils/frees.c
void		ft_lstclear(struct s_lst *lst);
void		ft_lexerclear(t_lexer *lexer);
void		freesplit(char **strmalloc);
void		frees(struct s_shell *ms, int code);
void		throwerror(struct s_shell *ms, char *str);
// utils/minilib.c
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *s, size_t n);
int			ft_strcmp(char *s1, char *s2);
char		*ft_tabcmp(char *str, char **tab);
char		*ft_strnstr_cmp(char *big, char *little, int len);
//errors/errors_1-5.c
int			ft_errors_1_5(int error, char *str);

// ************************* MINISHELL ************************* //
//minishell.c
void		setsigaction(struct s_shell *ms, int b);
void		nullonreadline(struct s_shell *ms);
void		loop(struct s_shell *ms)
			__attribute__((noreturn));
// signals.c
void		ft_sigquit(int sig);
void		ft_sigint(int sig);
void		ft_sigint2(int sig);
void		*ft_memset(void *s, int c, size_t n);

#endif
