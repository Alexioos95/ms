/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:48:23 by eewu              #+#    #+#             */
/*   Updated: 2023/06/20 17:40:04 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

t_list	*ft_lstnew(char **cmd, int i)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->tab = cmd;
	new->i = i;
	new->next = NULL;
	return (new);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new, t_struct *m)
{
	t_list	*last;

	if (*lst == NULL)
	{
		*lst = new;
		m->head = *lst;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

void	ft_lstclearpipex(t_list **lst)
{
	t_list	*tmp;
	int		i;

	if (!lst)
		return ;
	while (*lst)
	{
		i = 0;
		tmp = (*lst)->next;
		while ((*lst)->tab[i])
			free((*lst)->tab[i++]);
		free((*lst)->tab);
		free(*lst);
		*lst = tmp;
	}
}

int	ft_lstsize(t_list *lst)
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
