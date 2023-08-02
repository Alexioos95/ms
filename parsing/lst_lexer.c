/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:47:00 by eewu              #+#    #+#             */
/*   Updated: 2023/08/02 11:08:28 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_lexer	*ft_lstlast_lexer(t_lexer *head)
{
	// int		len;
	t_lexer	*tmp;

	tmp = head;
	// len = head->len;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_lstresetindex_lexer(t_lexer *head)
{
	// t_lexer	*last;
	t_lexer	*tmp;

	tmp = head;
	// last = ft_lstlast_lexer(head);
	while (tmp->next)
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
	new->tab = NULL;
	new->token = token;
	new->i = 0;
	new->len = 1;
	new->next = NULL;
	new->back = NULL;
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
	new->back = last;
	new->i = last->i + 1;
	ft_lstresetindex_lexer((*head));
}

void	ft_lexer_delone(t_lexer **curr_node, int i)
{
	t_lexer		*node_cmd;
	t_lexer		*tmp;

	node_cmd = (*curr_node)->back;
	node_cmd->tab[i] = ((*curr_node))->str;
	((*curr_node))->str = NULL;
	tmp = (*curr_node);
	(*curr_node) = (*curr_node)->next;
	free (tmp);
	node_cmd->next = (*curr_node);
	if ((*curr_node))
		(*curr_node)->back = node_cmd;
}

// c'at' | ls < 'Ma'ke"fil"e > "out" | echo "'hey"|c'at' | ls < 'Ma'ke"fil"e>"out" | echo "'hey" | ls -la >> fichier | awk '{"$1 print >> <<"}' | "|" autre <<< fichier | ok ok ok ok ok ok ok ok ok ok ok ok okok o ko" oijf fioejw iowef iowejfowie f"
