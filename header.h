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
# include <unistd.h>

enum					e_enum
{
	CONST,
	ALLOC
};

struct					s_lst
{
	int					print;
	enum e_enum			flag;
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
	int					orphan;
	struct s_lst		*env;
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
// ft_split.c
char					**ft_split(char *s, char c);
// ft_splitline.c
char					**ft_splitline(char *s, char c);
// frees.c
void					frees(struct s_shell *ms, int code);
void					freesplit(char **strmalloc);
void					ft_lstclear(struct s_shell *ms, struct s_lst *lst);
// utils.c
int						ft_strncmp(char *s1, char *s2, size_t n);
int						ft_atoi(char *nptr);
char					*ft_strjoin(char *s1, char *s2);
int						ft_strlen(char *str);
char					*ft_strdup(char *s);
// utils_env.c
char					*ft_strnstr(char *big, char *little, int equal);
char					*ft_strjoinenv(char *s1, char c, char *s2);
char					*ft_substr(char *s, int start, int len);
struct s_lst			*ft_getenv(struct s_shell *ms, char *str);
// builtins/builtins.c
void					ft_exit(struct s_shell *ms, char **tab);
int						ft_env(struct s_shell *ms, char **tab);
int						ft_unset(struct s_shell *ms, char **tab);
int						ft_pwd(struct s_shell *ms);
// builtins/builtins_echo.c
int						ft_echo(char **tab);
// builtins/builtins_cd.c
int						ft_cd(struct s_shell *ms, char **tab);
int						ft_cdhome(struct s_shell *ms, char *tmp);
void					cdenv(struct s_shell *ms, char *tmp, char *str);
void					actualizepwd(struct s_shell *ms);
void					actualizeenv(struct s_shell *ms, char *tmp);
// builtins/builtins_export.c
int						ft_export(struct s_shell *ms, char **tab);
int						searchequal(char *str);
int						newnode(struct s_shell *ms, char *str);
// builtins/builtins_export2.c
int						parsingexport(char *str);

#endif
