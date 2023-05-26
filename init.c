/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:21:32 by apayen            #+#    #+#             */
/*   Updated: 2023/05/26 12:32:35 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(struct s_lst **lst, struct s_lst *new)
{
	struct s_lst	*tmp;

	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

struct s_lst	*ft_lstnew(struct s_shell *ms, char **envp, int i)
{
	struct s_lst	*new;

	new = malloc(sizeof(struct s_lst));
	if (new == NULL)
		return (NULL);
	if (envp != NULL)
		new->line = envp[i];
	else
		new->line = NULL;
	new->print = 1;
	new->flag = CONST;
	new->next = NULL;
	new->ms = ms;
	if (i == 0)
		ms->lsthead = new;
	return (new);
}

int	ft_setenv(struct s_shell *ms, char **envp)
{
	int				i;
	struct s_lst	*tmp;

	i = 1;
	if (envp == NULL)
		return (0);
	ms->env = ft_lstnew(ms, envp, 0);
	if (ms->env == NULL)
		return (1);
	while (envp[i] != NULL)
	{
		tmp = ft_lstnew(ms, envp, i);
		if (tmp == NULL)
		{
			ft_lstclear(ms, ms->env);
			return (1);
		}
		ft_lstadd_back(&ms->env, tmp);
		i++;
	}
	return (0);
}

// Set les variables, et construit la liste chainee du env.
int	init(struct s_shell *ms, char **envp)
{
	ms->line = NULL;
	ms->split = NULL;
	ms->prompt = "apayen&eewu@minishell$ ";
	ms->orphan = -1;
	ms->env = NULL;
	ms->lsthead = NULL;
	if (ft_setenv(ms, envp) == 1)
		return (1);
	return (0);
}
