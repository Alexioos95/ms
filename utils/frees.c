/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:36:20 by apayen            #+#    #+#             */
/*   Updated: 2023/05/26 13:28:04 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstclear(struct s_shell *ms, struct s_lst *lst)
{
	struct s_lst	*tmp;

	if (lst == NULL)
		return ;
	while (lst != NULL)
	{
		tmp = lst->next;
		if (lst->flag == NEW)
			free(lst->line);
		free(lst);
		lst = tmp;
	}
	ms->lsthead = NULL;
}

void	frees(struct s_shell *ms, int code)
{
	if (ms->line != NULL)
		free(ms->line);
	if (ms->split != NULL)
		ft_free(ms->split);
	if (ms->env != NULL)
		ft_lstclear(ms, ms->env);
	rl_clear_history();
	exit(code);
}
