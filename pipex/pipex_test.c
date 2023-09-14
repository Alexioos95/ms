/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:58:01 by eewu              #+#    #+#             */
/*   Updated: 2023/09/14 09:31:51 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	print_allcmd(t_pipex *m)
{
	int			j;
	int			k;
	t_cmd_lst	*tmp;
	t_redir		*red;

	k = 0;
	tmp = m->head;
	while (tmp)
	{
		j = 0;
		while (tmp->tab && tmp->tab[j])
			j++;
		red = tmp->redirlst;
		while (red)
			red = red->next;
		tmp = tmp->next;
		k++;
	}
	printf("Nb_cmd: %d\n", m->nb_cmd);
}

void	print_list(char *tab, int i)
{
	printf("Tab[%d]: %s\n", i, tab);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("Tab[%d]: %s\n", i, tab[i]);
		i++;
	}
}
