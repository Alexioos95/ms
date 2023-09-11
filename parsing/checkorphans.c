/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkorphans.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:07:37 by apayen            #+#    #+#             */
/*   Updated: 2023/09/11 20:00:35 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// Print l'erreur.
int	printsyntaxerror(char *line, int i)
{
	if (line[i] == '\0')
		printf("minishell: syntax error near unexpected token 'newline'\n");
	else
	{
		if (i >= 1 && line[i - 1] == line[i])
			printf("minishell: syntax error near unexpected token '%c%c'\n", \
				line[i - 1], line[i]);
		else if (i >= 1 && line[i] == line[i + 1])
			printf("minishell: syntax error near unexpected token '%c%c'\n", \
				line[i], line[i + 1]);
		else
			printf("minishell: syntax error near unexpected token '%c'\n", \
				line[i]);
	}
	return (1);
}

// Cherche une redirection sans fichier.
int	checkorphanredir(char *line)
{
	int		i;

	i = 0;
	while (line[i] != '\0')
	{
		while (line[i] == ' ')
			i++;
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