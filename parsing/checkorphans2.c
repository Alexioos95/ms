/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkorphans2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:38:16 by eewu              #+#    #+#             */
/*   Updated: 2023/09/11 16:38:38 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// Cherche un '[' qui n'est pas ferme.
int	checkorphanbracket(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '[')
		{
			i++;
			while (line[i] != '\0' && line[i] != ']')
				i++;
			if (line[i] == '\0')
			{
				printf("minishell: [: missing `]'\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	checkorphans(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '|')
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		return (1);
	}
	if (checkorphanbracket(line) == 1)
		return (1);
	if (checkorphanquote(line) == 1)
		return (1);
	if (checkorphanpipe(line) == 1)
		return (1);
	if (checkorphanredir(line) == 1)
		return (1);
	return (0);
}
