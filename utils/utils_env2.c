/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:32:20 by apayen            #+#    #+#             */
/*   Updated: 2023/06/21 09:45:30 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	countvalablenodes(struct s_lst *lst)
{
	int				i;
	struct s_lst	*tmp;

	i = 0;
	tmp = lst;
	while (tmp != NULL)
	{
		if (tmp->print == 1)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**listtotab(struct s_shell *ms)
{
	int				i;
	int				len;
	struct s_lst	*tmp;
	char			**tab;

	i = 0;
	len = countvalablenodes(ms->env);
	tab = malloc(sizeof(char *) * (len + 1));
	if (tab == NULL)
		throwerror(ms, "malloc");
	tmp = ms->env;
	while (tmp != NULL)
	{
		if (tmp->print == 1)
		{
			tab[i] = tmp->line;
			i++;
		}
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}
