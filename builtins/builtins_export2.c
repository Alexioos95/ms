/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:35:18 by apayen            #+#    #+#             */
/*   Updated: 2023/06/15 14:15:25 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	isvalid(char c, int i)
{
	if (i == 0 && c >= '0' && c <= '9')
		return (0);
	else if (c == '`' || c == '~' || c == '!' || c == '@' || c == '#' || c == '$' \
		|| c == '%' || c == '^' || c == '&' || c == '*' || c == '(' \
		|| c == ')' || c == '-' || c == '{' || c == '}' || c == '[' || c == ']' \
		|| c == '\\' || c == '|' || c == ';' || c == ':' || c == '"' || c == '\'' \
		|| c == '<' || c == '>' || c == ',' || c == '.' || c == '?' || c == '/')
		return (0);
	return (1);
}

int	searchequal(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i] != '\0' && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (-1);
	if (i == 0)
		printf("minishell: export: `%s': not a valid identifier\n", str);
	return (i);
}

int	parsingexport(char *str)
{
	int	i;
	int	equal;

	equal = searchequal(str);
	if (equal < 1)
		return (0);
	i = equal;
	while (i > -1)
	{
		if (isvalid(str[i], i) == 0)
		{
			printf("minishell: export: `%s': not a valid identifier\n", str);
			return (0);
		}
		i--;
	}
	return (equal);
}
