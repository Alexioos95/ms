/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:43:38 by apayen            #+#    #+#             */
/*   Updated: 2023/08/09 13:44:34 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// Empeche le signal d'agir.
void	ft_sigquit(int sig)
{
	(void)sig;
}

// Deplace la ligne pour la boucle du shell.
void	ft_sigint2(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
}

// Replace une nouvelle ligne vide pour la boucle du shell.
void	ft_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s2;

	i = 0;
	s2 = s;
	while (i < n)
	{
		s2[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
