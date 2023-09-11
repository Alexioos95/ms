/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:48:23 by eewu              #+#    #+#             */
/*   Updated: 2023/09/11 18:44:57 by eewu             ###   ########.fr       */
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
	t_cmd_lst	*tmp;
	t_lexer		*tmplex;
	int			i;

	if (!lst)
		return ;
	while (*lst)
	{
		i = 0;
		tmplex = lexer->next;
		tmp = (*lst)->next;
		// freesplit((*lst)->tab);
		// if (lexer->str)
		// 	free(lexer->str);
		if ((*lst)->tab)
		{
			while ((*lst)->tab && (*lst)->tab[i])
				free((*lst)->tab[i++]);
			if ((*lst)->redirlst->token.token)
				free ((*lst)->redirlst->token.token);
			free ((*lst)->redirlst);
			// freesplit((*lst)->tab);
		}
		// if (lexer->tab)
		i = 0;
		while (lexer->tab && lexer->tab[i] != NULL)
		{
			if ((lexer->tab && (*lst)->tab) && lexer->tab[i] && (lexer->tab[i] != (*lst)->tab[i]))
				free(lexer->tab[i]);
			i++;
			while (lexer->tab[i] != NULL)
				i++;
		}
		if ((*lst)->tab)
		{
			free((*lst)->tab);
			(*lst)->tab = NULL;
		}
		free(lexer->tab);
		if (lexer->token.file)
		{
			if (ft_strcmp(lexer->token.token, "<<"))
				unlink(lexer->token.file);
			free(lexer->token.file);
		}
		if (lexer->token.token)
			free(lexer->token.token);
		if (lexer->token.pipe)
			free(lexer->token.pipe);
		// freesplit(lexer->tab);
		// free(lexer->tab);
		if ((*lst)->name)
			free ((*lst)->name);
		(*lst)->name = NULL;
		(*lst)->tab = NULL;
		if ((*lst))
			free(*lst);
		(*lst) = NULL;
		// free ((*lst)->redirlst);
		// (*lst)->redirlst = NULL;
		*lst = tmp;
		free (lexer);
		lexer = tmplex;
		// if (!lexer)
		// 	break;
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
