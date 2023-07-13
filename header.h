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

# include "pipex.h"
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
}						t_builtins;

typedef struct s_tokens
{
	char				*token;
	char				*arg;
	char				*pipe;
}						t_tokens;

typedef struct s_lexer
{
	char				*str;
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

typedef struct s_shell
{
	char				*line;
	char				*pwdpath;
	char				*oldpwdpath;
	char				**split;
	char				*tmp;
	int					orphan;
	int					symlink;
	int					nb_pipe;
	struct s_tokens		token;
	struct s_lst		*env;
	struct s_cmd		*cmd;
	struct s_pipex		*pex;
	struct s_lexer		*lexer;
	struct s_cmd_lst	*cmd_lst;
	struct sigaction	sigact[3];
	struct stat			stat;
}						t_shell;

// ************************** INIT ************************** \\

// init/init.c
void				ft_lstadd_back(struct s_lst **lst, struct s_lst *new);
struct s_lst		*ft_lstnew(struct s_shell *ms, char *str);
void				init(struct s_shell *ms, char **envp);
// init/init_env.c
void				increaseshlvl(struct s_shell *ms);
void				ft_setpwd(struct s_shell *ms);
void				recreatepwd(struct s_shell *ms);
void				createminienv(struct s_shell *ms);
void				ft_setenv(struct s_shell *ms, char **envp);

// ************************** PROG ************************** \\

// signals.c
void				ft_sigquit(int sig);
void				ft_sigint(int sig);
void				*ft_memset(void *s, int c, size_t n);

// ************************ PARSING ************************ \\

// parsing/parsing.c
int					parser(struct s_shell *ms);
int					ft_state(char c, int state);
int					ft_istoken(char c);
int					ft_isthereatoken(char *line, t_lexer **lexer);
void				ft_browse(t_shell *ms);
// parsing/checkorphans
int					isspecial(char c);
// parsing/lst_lexer.c
t_tokens			ft_newtoken(char *token, char *arg);
t_lexer				*ft_lexer_new(char *str, t_tokens token);
t_lexer				*ft_lstlast_lexer(t_lexer *head);
void				ft_lexer_addback(t_lexer **head, t_lexer *new);
void				ft_lstresetindex_lexer(t_lexer *head);
// utils/lst.c
void				ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
t_cmd				*ft_lstnew_cmd(char **str, char **redir, char **built);
int					checkorphanquote(char *line);
int					checkorphanbracket(char *line);
void				ft_print_lexerlst(t_lexer *lst);

// ************************ BUILT-INS ************************ \\

// builtins/builtins.c
void				ft_exit(struct s_shell *ms, char **tab);
int					ft_pwd(struct s_shell *ms);
int					ft_unset(struct s_shell *ms, char **tab);
int					ft_env(struct s_shell *ms, char **tab);
// builtins/builtins_echo.c
int					ft_echo_isfulln(char *str);
int					ft_echo(char **tab);
// builtins/builtins_export.c
int					ft_export_newnode(struct s_shell *ms, char *str);
int					ft_export_oldnode(struct s_lst *node, char *str);
int					ft_export_refreshenv(struct s_shell *ms, char *str,
						int equal);
int					ft_export(struct s_shell *ms, char **tab);
// builtins/builtins_export2.c
int					ft_export_isvalid(char c, int i);
int					ft_export_searchequal(char *str);
int					ft_export_parsing(char *str);
// builtins/builtins_cd.c
int					ft_cd_home(struct s_shell *ms, char *tmp);
int					ft_cd_oldpwd(struct s_shell *ms, char *tmp);
int					ft_cd_nothome(struct s_shell *ms, char *str, char *tmp);
int					ft_cd(struct s_shell *ms, char **tab);
// builtins/builtins_cd2.c
void				ft_echo_actualizepwd(struct s_shell *ms);
void				ft_echo_changeenv(struct s_shell *ms, char *tmp,
						char *str);
char				*ft_cd_symlink(struct s_shell *ms, char *tmp,
						char *str);
void				ft_echo_actualizeenv(struct s_shell *ms, char *tmp);

// ************************* UTILS ************************* \\

// utils/utils.c
int					ft_strlen(char *str);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strdup(char *s);
int					ft_atoi(char *nptr);
int					ft_tablen(char **str);
int					ft_strncmp(char *s1, char *s2, size_t n);
// utils/utils_env.c
char				*ft_strjoinenv(char *s1, char c, char *s2);
char				*ft_substr(char *s, int start, int len);
char				*ft_strnstr(char *big, char *little, int equal);
struct s_lst		*ft_getenv(struct s_shell *ms, char *str);
char				*ft_itoa(int nb);
// utils/utils_env2.c
int					countvalablenodes(struct s_lst *lst);
char				**listtotab(struct s_shell *ms);
char				*ft_subnstr(char *s, unsigned int start, size_t len);
// utils/ft_split.c
char				**ft_split(char *s, char c);
// utils/frees.c
void				ft_lstclear(struct s_lst *lst);
void				ft_lexerclear(t_lexer *lexer);
void				freesplit(char **strmalloc);
void				frees(struct s_shell *ms, int code);
void				throwerror(struct s_shell *ms, char *str);
// utils/minilib.c
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_bzero(void *s, size_t n);
int					ft_strcmp(char *s1, char *s2);
int					ft_tabcmp(char *str, char **tab);
char				*ft_strnstr_cmp(char *big, char *little, int len);
//errors/errors_1-5.c
int					ft_errors_1_5(int error, char *str);

#endif