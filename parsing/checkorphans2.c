/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkorphans2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:38:16 by eewu              #+#    #+#             */
/*   Updated: 2023/09/18 13:55:07 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// Cherche une redirection sans fichier.
int	checkorphanredir(char *line)
{
	int		i;

	i = 0;
	while (line[i] != '\0')
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '\0')
			return (0);
		if (line[i] == '<' || line[i] == '>')
		{
			if (line[i] == line[i + 1])
				i++;
			i++;
			while (line[i] == ' ')
				i++;
			if (line[i] == '<' || line[i] == '>' || line[i] == '|' \
				|| line[i] == '\0')
				return (printsyntaxerror(line, i));
		}
		i++;
	}
	return (0);
}

// Cherche un pipe non-ferme.
int	checkorphanpipe(char *line)
{
	int	i;

	i = 1;
	while (line[i] != '\0')
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '\0')
			return (0);
		if (line[i] == '|')
		{
			i++;
			if (line[i] == '\0')
				return (printsyntaxerror(line, i));
			while (line[i] == ' ')
				i++;
			if (line[i] == '|' || line[i] == '\0')
				return (printsyntaxerror(line, i));
		}
		i++;
	}
	return (0);
}
