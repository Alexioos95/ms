/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:47:00 by eewu              #+#    #+#             */
/*   Updated: 2023/07/13 14:18:54 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_lexer	*ft_lstlast_lexer(t_lexer *head)
{
	int		len;
	t_lexer	*tmp;

	tmp = head;
	len = head->len;
	while (tmp->next->i != 0)
		tmp = tmp->next;
	return (tmp);
}

void	ft_lstresetindex_lexer(t_lexer *head)
{
	t_lexer	*last;
	t_lexer	*tmp;

	tmp = head;
	last = ft_lstlast_lexer(head);
	while (tmp && (tmp->i != last->i))
	{
		tmp->next->i = tmp->i + 1;
		tmp->next->len = tmp->len;
		tmp = tmp->next;
	}
}

t_lexer	*ft_lexer_new(char *str, t_tokens token)
{
	t_lexer	*new;

	new = malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->str = str;
	new->token = token;
	new->i = 0;
	new->len = 1;
	new->next = new;
	new->back = new;
	return (new);
}

void	ft_lexer_addback(t_lexer **head, t_lexer *new)
{
	t_lexer	*last;

	if (!(*head))
	{
		(*head) = new;
		return ;
	}
	(*head)->len++;
	last = ft_lstlast_lexer((*head));
	last->next = new;
	new->next = (*head);
	new->back = last;
	(*head)->back = new;
	new->i = last->i + 1;
	ft_lstresetindex_lexer((*head));
}
