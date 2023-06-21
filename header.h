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

struct					s_lst
{
	int					print;
	char				*line;
	struct s_lst		*next;
	struct s_shell		*ms;
};

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

#endif
