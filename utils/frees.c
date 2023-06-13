/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:36:20 by apayen            #+#    #+#             */
/*   Updated: 2023/06/13 11:17:34 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_lstclear(struct s_shell *ms, struct s_lst *lst)
{
	struct s_lst	*tmp;

	if (lst == NULL)
		return ;
	while (lst != NULL)
	{
		tmp = lst->next;
		if (lst->flag == ALLOC)
			free(lst->line);
		free(lst);
		lst = tmp;
	}
	ms->lsthead = NULL;
}

void	freesplit(char **strmalloc)
{
	int	i;

	i = 0;
	if (strmalloc == NULL)
		return ;
	while (strmalloc[i] != NULL)
	{
		free(strmalloc[i]);
		i++;
	}
	free(strmalloc);
}

void	frees(struct s_shell *ms, int code)
{
	if (ms->line != NULL)
		free(ms->line);
	if (ms->split != NULL)
		freesplit(ms->split);
	if (ms->env != NULL)
		ft_lstclear(ms, ms->env);
	if (ms->pwdpath != NULL)
		free(ms->pwdpath);
	if (ms->oldpwdpath != NULL)
		free(ms->oldpwdpath);
	rl_clear_history();
	exit(code);
}
