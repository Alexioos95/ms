/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkorphans.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:07:37 by apayen            #+#    #+#             */
/*   Updated: 2023/06/20 15:02:11 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// Regarde si le char envoye est un charactere special qu'il ne faut pas gere.
int	isspecial(char c)
{
	if (c == '!' || c == '#' || c == '%' || c == '&' || c == '(' || c == ')' \
		|| c == '*' || c == ';' || c == '\\' || c == '^' || c == '`' \
		|| c == '{' || c == '}' || c == '~')
	{
		printf("minishell: syntax error near unexpected token '%c'\n", c);
		return (1);
	}
	return (0);
}

// Cherche une quote orpheline, ou des characteres speciaux.
int	checkorphanquote(char *line)
{
	int		i;
	char	c;

	i = 0;
	while (line[i] != '\0')
	{
		if (isspecial(line[i]) == 1)
			return (1);
		if (line[i] == '\'' || line[i] == '\"')
		{
			c = line[i];
			i++;
			while (line[i] != '\0' && line[i] != c)
				i++;
			if (line[i] == '\0')
			{
				printf("minishell: syntax error near unexpected token '%c'\n", \
					c);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

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
