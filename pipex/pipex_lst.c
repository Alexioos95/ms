/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:48:23 by eewu              #+#    #+#             */
/*   Updated: 2023/07/20 17:38:20 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"



t_cmd_lst	*ft_pipex_lstnew(char **cmd, char *name, int i)
{
	t_cmd_lst	*new;

	new = malloc(sizeof(t_cmd_lst));
	if (!new)
		return (0);
	new->tab = cmd;
	new->name = name;
	new->redirlst = NULL;
	new->i = i;
	new->next = NULL;
	return (new);
}

t_cmd_lst	*ft_lstlast(t_cmd_lst *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_pipex_lstadd_back(t_cmd_lst **lst, t_cmd_lst *new, t_pipex *m)
{
	t_cmd_lst	*last;

	if (*lst == NULL)
	{
		*lst = new;
		m->head = *lst;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

void	ft_lstclearpipex(t_cmd_lst **lst)
{
	t_cmd_lst	*tmp;
	int			i;

	if (!lst)
		return ;
	while (*lst)
	{
		i = 0;
		tmp = (*lst)->next;
		while ((*lst)->tab && (*lst)->tab[i])
			free((*lst)->tab[i++]);
		free((*lst)->tab);
		free(*lst);
		*lst = tmp;
	}
}

int	ft_lstsize(t_cmd_lst *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
