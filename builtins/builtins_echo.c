/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:37:39 by apayen            #+#    #+#             */
/*   Updated: 2023/06/14 13:42:21 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	isfulln(char *str)
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

// Print la str.
// Si l'argument est "-n", ne pas print le \n a la fin.
int	ft_echo(char **tab)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (tab[i] != NULL && ft_strncmp(tab[i], "-n", 2) == 0)
	{
		if (isfulln(tab[i]) == 0)
			break;
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
