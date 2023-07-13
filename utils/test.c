/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:19:34 by eewu              #+#    #+#             */
/*   Updated: 2023/07/13 14:19:59 by eewu             ###   ########.fr       */
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
		printf("Pipe: %s\n", tmp->token.pipe);
		tmp = tmp->next;
		i++;
	}
}
