/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:53:38 by apayen            #+#    #+#             */
/*   Updated: 2023/05/30 14:41:41 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isspecial(char c)
{
	if (c == '!' || c == '#' || c == '%' || c == '&' || c == '(' || c == ')' \
		|| c == '*' || c == ';' || c == '?' || c == '[' || c == '\\' \
		|| c == ']' || c == '^' || c == '`' || c == '{' || c == '}' || c == '~')
		return (1);
	return (0);
}

// Chercher une quote orpheline, ou des characteres speciaux qui ne sont pas entre quotes.
int	checkorphan(char *line, int i, int j)
{
	while (line[i] != '\0')
	{
		if (isspecial(line[i]) == 1)
			return (i);
		if (line[i] == '\'')
		{
			j = i;
			i++;
			while (line[i] != '\0' && line[i] != 39)
				i++;
		}
		else if (line[i] == '\"')
		{
			j = i;
			i++;
			while (line[i] != '\0' && line[i] != '\"')
				i++;
		}
		if (line[i] == '\0')
			return (j);
		i++;
	}
	return (-1);
}

// Parser.
int	parser(struct s_shell *ms)
{
	if (ms->split != NULL)
	{
		freesplit(ms->split);
		ms->split = NULL;
	}
	if (ms->line == NULL)
		return (0);
	ms->orphan = checkorphan(ms->line, 0, 0);
	if (ms ->orphan != -1)
	{
		printf("minishell: syntax error near unexpected token '%c'\n", \
			ms->line[ms->orphan]);
		return (2);
	}
	ms->split = ft_split(ms->line, ' ');			// Pour test, a delete.
	if (ft_strncmp(ms->line, "echo", 4) == 0)		// .
		ft_echo(ms->split[1], ms->split[2]);		// .
	else if (ft_strncmp(ms->line, "pwd", 3) == 0)	// .
		ft_pwd(ms);									// .
	else if (ft_strncmp(ms->line, "cd", 2) == 0)	// .
		ft_cd(ms, ms->split[1]);					// .
	else if (ft_strncmp(ms->line, "exit", 4) == 0)	// .
		ft_exit(ms, ms->split[1]);					// .
	else if (ft_strncmp(ms->line, "env", 3) == 0)	// .
		ft_env(ms, ms->split[1]);					// .
	else if (ft_strncmp(ms->line, "unset", 5) == 0)	// .
		ft_unset(ms, ms->split[1], ms->split[2]);	// .
	else if (ft_strncmp(ms->line, "export", 6) == 0)// .
		ft_export(ms, ms->split[1]);				// -----------------------
	return (0);
}
