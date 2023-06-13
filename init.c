/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:21:32 by apayen            #+#    #+#             */
/*   Updated: 2023/06/13 11:17:34 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_lstadd_back(struct s_lst **lst, struct s_lst *new)
{
	struct s_lst	*last;

	if (new == NULL)
	{
		printf("minishell: malloc: %s\n", strerror(errno));
		frees(new->ms, 1);
	}
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

void	ft_setpwd(struct s_shell *ms)
{
	struct s_lst	*tmp;

	tmp = ft_getenv(ms, "PWD");
	if (tmp != NULL)
	{
		ms->pwdpath = ft_strdup(tmp->line);
		if (ms->pwdpath == NULL)
		{
			printf("minishell: malloc: %s\n", strerror(errno));
			frees(ms, 1);
		}
	}
	tmp = ft_getenv(ms, "OLDPWD");
	if (tmp != NULL)
	{
		ms->oldpwdpath = ft_strdup(tmp->line);
		if (ms->oldpwdpath == NULL)
		{
			printf("minishell: malloc: %s\n", strerror(errno));
			frees(ms, 1);
		}
	}
}

void	ft_setenv(struct s_shell *ms, char **envp)
{
	int				i;
	struct s_lst	*tmp;

	i = 0;
	if (envp == NULL)
		return ;
	while (envp[i] != NULL)
	{
		ft_lstadd_back(&ms->env, ft_lstnew(ms, envp[i]));
		i++;
	}
	tmp = ms->env;
	while (tmp != NULL)
	{
		tmp->flag = CONST;
		tmp = tmp->next;
	}
	ms->lsthead = ms->env;
	ft_setpwd(ms);
}

// Set les variables, et construit la liste chainee du env.
void	init(struct s_shell *ms, char **envp)
{
	ms->pwdpath = NULL;
	ms->oldpwdpath = NULL;
	ms->line = NULL;
	ms->split = NULL;
	ms->orphan = -1;
	ms->env = NULL;
	ms->lsthead = NULL;
	ft_memset(&ms->sigact[0], 0, sizeof(ms->sigact[0]));
	ms->sigact[0].sa_handler = SIG_DFL;
	ft_memset(&ms->sigact[1], 0, sizeof(ms->sigact[0]));
	ms->sigact[1].sa_handler = &ft_sigint;
	ft_memset(&ms->sigact[2], 0, sizeof(ms->sigact[1]));
	ms->sigact[2].sa_handler = SIG_IGN;
	ft_setenv(ms, envp);
}
