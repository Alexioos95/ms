/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:37:39 by apayen            #+#    #+#             */
/*   Updated: 2023/08/02 11:06:11 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// Regarde si la str envoyee est compose que de n apres le -n initial.
int	ft_echo_isfulln(char *str)
{
	int	i;

	i = 2;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

// Print les str.
// Si la 1ere str est "-n", ne print pas le \n a la fin du resultat.
int	ft_echo(char **tab)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (tab[i] != NULL && ft_strncmp(tab[i], "-n", 2) == 0)
	{
		if (ft_echo_isfulln(tab[i]) == 0)
			break ;
		n = 1;
		i++;
	}
	while (tab[i] != NULL)
	{
		printf("%s", tab[i]);
		if (tab[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n == 0)
		printf("\n");
	return (0);
}
