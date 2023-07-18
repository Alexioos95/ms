/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:19:34 by eewu              #+#    #+#             */
/*   Updated: 2023/07/17 11:51:44 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_print_lexerlst(t_lexer *lst)
{
	int		i;
	int		c;
	t_lexer	*tmp;

	tmp = lst;
	c = tmp->len;
	printf("Taille du Lexer: %d\n", lst->len);
	while (tmp)
	{
		i = 0;
		printf("Word: %s\n", tmp->str);
		while (tmp->tab && tmp->tab[i])
			printf("Commande: %s\n", tmp->tab[i++]);
		printf("Token: %s\n", tmp->token.token);
		printf("Arg: %s\n", tmp->token.arg);
		printf("Pipe: %s\n", tmp->token.pipe);
		printf("---------\n");
		tmp = tmp->next;
		// printf("Index: %d\n", tmp->back->i);
		// i++;
	}
}
