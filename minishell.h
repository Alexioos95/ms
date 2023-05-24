/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:06:58 by apayen            #+#    #+#             */
/*   Updated: 2023/05/24 15:38:49 by apayen           ###   ########.fr       */
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
	UNSET,
	NEW
};

struct				s_lst
{

	int				id;
	char			*line;
	struct s_lst	*next;
	struct s_shell	*ms;
	enum e_enum		flag;
};

struct				s_shell
{
	char			*prompt;
	char			*line;
	char			**split;
	int				orphan;
	struct s_lst	*env;
	void			*lsthead;
};

int					init(struct s_shell *ms, char **envp);
int					parser(struct s_shell *ms);

struct s_lst		*ft_lstnew(struct s_shell *ms, char **envp, int i);
void				ft_lstclear(struct s_shell *ms, struct s_lst *lst);
void				ft_lstdelone(struct s_lst *lst);
void				frees(struct s_shell *ms);

char				**ft_split(char *s, char c);
void				ft_free(char **strmalloc);

char				*ft_strnstr(char *big, char *little, int equal);
int					ft_strncmp(char *s1, char *s2, size_t n);
int					ft_atoi(char *nptr);
char				*ft_strjoin(char *s1, char *s2);

int					ft_echo(char *str, char *opt);
int					ft_exit(struct s_shell *ms, char *opt);
int					ft_env(struct s_shell *ms, char *opt);
int					ft_unset(struct s_shell *ms, char *str, char *opt);
int					ft_pwd(void);
int					ft_cd(struct s_shell *ms, char *str);

#endif
