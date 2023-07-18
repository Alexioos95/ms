/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:21:32 by apayen            #+#    #+#             */
/*   Updated: 2023/07/18 11:27:18 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"


void	ft_lstadd_back(struct s_lst **lst, struct s_lst *new)
{
	struct s_lst	*last;

	if (new == NULL)
		throwerror((*lst)->ms, "malloc");
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
	new->next = NULL;
	new->ms = ms;
	return (new);
}

t_tokens	ft_newtoken(char *token, char *arg)
{
	t_tokens	new;


	new.pipe = NULL;
	new.token = NULL;
	if (ft_strcmp(token, "|"))
		new.pipe = token;
	else
		new.token = token;
	new.arg = arg;
	return (new);
}

// Initialise toutes les variables, et construit la liste chainee du env.
void	init(struct s_shell *ms, char **envp)
{
	ms->line = NULL;
	ms->split = NULL;
	ms->pwdpath = NULL;
	ms->oldpwdpath = NULL;
	ms->orphan = -1;
	ms->env = NULL;
	ms->tmp = NULL;
	ft_memset(&ms->sigact[0], 0, sizeof(ms->sigact[0]));
	ms->sigact[0].sa_handler = SIG_DFL;
	ft_memset(&ms->sigact[1], 0, sizeof(ms->sigact[0]));
	ms->sigact[1].sa_handler = &ft_sigint;
	ft_memset(&ms->sigact[2], 0, sizeof(ms->sigact[1]));
	ms->sigact[2].sa_handler = SIG_IGN;
	ft_setenv(ms, envp);
}
