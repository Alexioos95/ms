/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:48:23 by eewu              #+#    #+#             */
/*   Updated: 2023/09/12 12:38:26 by apayen           ###   ########.fr       */
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
		m->headplus = *lst;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

void	ft_lstclearpipex(t_cmd_lst **lst, t_lexer *lexer)
{
	t_cmd_lst	*exec;
	t_redir		*redir;

	if (!lst)
		return ;
	while (*lst)
	{
		exec = (*lst)->next;
		free((*lst)->tab);
		free((*lst)->name);
		while ((*lst)->redirlst)
		{
			redir = (*lst)->redirlst->next;
			free((*lst)->redirlst);
			(*lst)->redirlst = redir;
		}
		free((*lst));
		(*lst) = exec;
	}
	ft_lexerclear(lexer);
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
