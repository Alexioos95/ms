/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:47:00 by eewu              #+#    #+#             */
/*   Updated: 2023/06/27 15:42:21 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_print_lexerlst(t_lexer *lst)
{
	int		i;
	int		c;
	t_lexer	*tmp;

	i = 0;
	tmp = lst;
	c = tmp->len;
	while (i < c)
	{
		printf("Commande: %s\n", tmp->str);
		printf("Token: %s\n", tmp->token.token);
		printf("Arg: %s\n", tmp->token.arg);
		tmp = tmp->next;
		i++;
	}
}

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

t_lexer	*ft_lstnew_lexer(char *str, t_tokens token)
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

void	ft_lstaddback_lexer(t_lexer **head, t_lexer *new)
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
	// new->len = (*head)->len;
	ft_lstresetindex_lexer((*head));
}



// int	ft_tokeninstr(char *tokens, t_tokens *new_token, char *tab, int y)
// {
// 	int			len;
// 	int			cmp;
// 	char		*strcmp;
// 	char		**split;

// 	strcmp = ft_strnstr_cmp(tab[y], tokens, ft_strlen(tab[y]));
// 	if (strcmp)
// 	{
// 		split = ft_split(tab[y], tokens);
// 		len = ft_tablen(split);
// 		(*new_token) = ft_newtoken(tokens, NULL);
// 		if (((ft_tabcmp(tab[y + 1], tokens) || !tab[y + 1]) && len == 1) \
// 			|| ((ft_tabcmp(split[1], tokens) || !split[1]) && len == 2))
// 			cmp = ft_errors_1_5(0, tab[y + 1]);
// 	}
// 	return (cmp);
// }


// ls>test>test>>test>test>test|

// if strnstrcmp(tab) trouve un token	// int	i;
	// int	nb_cmd;

// split = split au token
// split[0] -> lstadd_back
// token -> lst_addback


// int ft_whichtoken(char **tokens, t_tokens *new_token, char **tab, int y)
// {
// 	int			cmp;
// 	int			i;
// 	char		*strcmp;

// 	i = 0;
// 	cmp = 0;
// 	(*new_token) = ft_newtoken(NULL, NULL);
// 	while (tokens[i] && cmp == 0)
// 	{
// 		cmp = ft_tokeninstr(tokens[i], new_token, tab, y);
// 		if (cmp)
// 			return (cmp);
// 		cmp = ft_strcmp(tab[y], tokens[i]);
// 		if (cmp)
// 		{
// 			(*new_token) = ft_newtoken(tokens[i], NULL);
// 			if (ft_tabcmp(tab[y + 1], tokens) || !tab[y + 1])
// 				cmp = ft_errors_1_5(0, tab[y + 1]);
// 			else if (tab[y + 1] && !ft_strcmp(tab[y], "|"))
// 				(*new_token) = ft_newtoken(tokens[i], tab[y + 1]);
// 			return (cmp);
// 		}
// 		i++;
// 	}
// 	return (cmp);
// }

// int	ft_istoken(t_lexer **head, char **tab, int y)
// {
// 	int			i;
// 	int			bool;
// 	t_tokens	new_token;
// 	char		**tokens;

// 	i = 0;
// 	tokens = ft_split("< > << >> | &", ' ');
// 	new_token = ft_newtoken(NULL, NULL);
// 	bool = ft_whichtoken(tokens, &new_token, tab, y);
// 	if (bool)
// 		ft_lstaddback_lexer(head, ft_lstnew_lexer(NULL, new_token));
// 	else
// 		ft_lstaddback_lexer(head, ft_lstnew_lexer(tab[y], new_token));
// 	if (ft_strcmp(tab[y], "|"))
// 		return (-1);
// 	return (bool);
// }

// t_lexer	*ft_lexer(char **tab, t_lexer *new)
// {
// 	int		i;
// 	int		istoken;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		istoken = ft_istoken(&new, tab, i);
// 		if (istoken == 1)
// 			i++;
// 		else if (istoken == -2)
// 			return (0);
// 		i++;
// 	}
// 	return (new);
// }

// t_lexer	*split_pipe(char *str, t_shell *ms)
// {
// 	t_lexer	*lst_lexer;
// 	char	**split_pipe;
// 	char	**split_cmd;
// 	int		i;

// 	i = 0;
// 	split_pipe = ft_split(str, '|');
// 	ms->nb_pipe = ft_tablen(split_pipe) - 1;
// 	lst_lexer = NULL;
// 	split_cmd = ft_split(str, ' ');
// 	lst_lexer = ft_lexer(split_cmd, lst_lexer);
// 	return (lst_lexer);
// }
