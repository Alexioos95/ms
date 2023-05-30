/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:06:58 by apayen            #+#    #+#             */
/*   Updated: 2023/05/30 15:09:22 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

enum				e_enum
{
	CONST,
	ALLOC
};

struct				s_lst
{
	int				print;
	enum e_enum		flag;
	char			*line;
	struct s_lst	*next;
	struct s_shell	*ms;
};

struct				s_shell
{
	char			*prompt;
	char			*line;
	char			*pwdpath;
	char			*oldpwdpath;
	char			**split;
	int				orphan;
	struct s_lst	*env;
	void			*lsthead;
};

// init.c
void				init(struct s_shell *ms, char **envp);
void				ft_setenv(struct s_shell *ms, char **envp);
struct s_lst		*ft_lstnew(struct s_shell *ms, char *str);
void				ft_lstadd_back(struct s_lst **lst, struct s_lst *new);
// parsing.c
int					parser(struct s_shell *ms);
int					checkorphan(char *line, int i, int j);
int					isspecial(char c);
// ft_split.c
char				**ft_split(char *s, char c);
void				freesplit(char **strmalloc);
// frees.c
void				frees(struct s_shell *ms, int code);
void				ft_lstclear(struct s_shell *ms, struct s_lst *lst);
// utils.c
int					ft_strncmp(char *s1, char *s2, size_t n);
int					ft_atoi(char *nptr);
char				*ft_strjoin(char *s1, char *s2);
int					ft_strlen(char *str);
char				*ft_strdup(char *s);
// utils_env.c
char				*ft_strnstr(char *big, char *little, int equal);
char				*ft_strjoinenv(char *s1, char c, char *s2);
char				*ft_substr(char *s, int start, int len);
struct s_lst		*ft_getenv(struct s_shell *ms, char *str);
// builtins.c
void				ft_exit(struct s_shell *ms, char *opt);
int					ft_echo(char *opt, char *str);
int					ft_env(struct s_shell *ms, char *opt);
int					ft_unset(struct s_shell *ms, char *str, char *opt);
int					ft_pwd(struct s_shell *ms);
// builtins_cd.c
int					ft_cd(struct s_shell *ms, char *str);
int					ft_cdhome(struct s_shell *ms);
int					ft_cdenv(struct s_shell *ms, char *tmp, char *str);
// builtins_export.c
int					ft_export(struct s_shell *ms, char *str);
int					searchequal(char *str);
int					newnode(struct s_shell *ms, char *str);

#endif
