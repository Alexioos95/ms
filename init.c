/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:21:32 by apayen            #+#    #+#             */
/*   Updated: 2023/05/30 11:52:03 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(struct s_lst **lst, struct s_lst *new)
{
	struct s_lst	*last;

	if ((*lst) == NULL)
	{
		(*lst) = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

struct s_lst	*ft_lstnew(struct s_shell *ms, char *str)
{
	struct s_lst	*new;

	new = malloc(sizeof(struct s_lst));
	if (new == NULL)
		return (NULL);
	new->print = 1;
	new->line = str;
	new->flag = ALLOC;
	new->next = NULL;
	new->ms = ms;
	return (new);
}

int	ft_setenv(struct s_shell *ms, char **envp)
{
	int				i;
	struct s_lst	*tmp;

	i = 0;
	if (envp == NULL)
		return (0);
	while (envp[i] != NULL)
		ft_lstadd_back(&ms->env, ft_lstnew(ms, envp[i++]));
	tmp = ms->env;
	while (tmp != NULL)
	{
		tmp->flag = CONST;
		tmp = tmp->next;
	}
	ms->lsthead = ms->env;
	return (0);
}

// Set les variables, et construit la liste chainee du env.
int	init(struct s_shell *ms, char **envp)
{
	struct s_lst	*tmp;

	ms->pwdpath = NULL;
	ms->oldpwdpath = NULL;
	ms->line = NULL;
	ms->split = NULL;
	ms->prompt = "apayen&eewu@minishell$ ";
	ms->orphan = -1;
	ms->env = NULL;
	ms->lsthead = NULL;
	if (ft_setenv(ms, envp) == 1)
		return (1);
	tmp = ft_getenv(ms, "PWD");
	if (tmp != NULL)
		ms->pwdpath = ft_strdup(tmp->line);
	tmp = ft_getenv(ms, "OLDPWD");
	if (tmp != NULL)
		ms->oldpwdpath = ft_strdup(tmp->line);
	return (0);
}
