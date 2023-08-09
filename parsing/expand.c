/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 10:24:27 by apayen            #+#    #+#             */
/*   Updated: 2023/08/09 10:24:27 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_expand_dollar(struct s_expand *exp, char *str)
{
	int	len;

	len = ft_strlen(&str[1]);
	if (ft_strncmp(str, "$?", 2) == 0)
	{
		free(str);
		exp->split[0] = ft_itoa(exp->ms->status);
		if (exp->split[0] == NULL)
			ft_expand_error(exp);
	}
	else
	{
		exp->node = ft_getenv(exp->ms, &str[1]);
		if (str[1] == '\0' || exp->node == NULL || exp->node->print != 1)
			str[0] = '\0';
		else
		{
			free(str);
			exp->split[0] = ft_strdup(&exp->node->line[len + 1]);
			if (exp->split[0] == NULL)
				ft_expand_error(exp);
		}
	}
	exp->buff = ft_expand_join(exp, exp->buff, exp->split[0]);
	exp->split[0] = NULL;
}

void	ft_expand_replace(struct s_expand *exp, char *str)
{
	if (exp->c == '$')
		ft_expand_dollar(exp, str);
	else if (exp->c == '\'')
	{
		exp->buff = ft_expand_join(exp, exp->buff, \
		ft_substr(exp->split[0], 1, ft_strlen(exp->split[0]) - 2));
		free(exp->split[0]);
	}
	else if (exp->c == '"')
		ft_expand_dquote(exp, str);
	exp->c = '\0';
	if (exp->split[1] != NULL && exp->split[1][0] != '\0')
		ft_expand_start(exp, exp->split[1]);
	else
	{
		free(exp->split[1]);
		exp->split[1] = NULL;
	}
}

void	ft_expand_init(struct s_expand *exp, char *str, int i, int j)
{
	exp->buff = ft_expand_join(exp, exp->buff, ft_substr(str, 0, i));
	if (exp->c == '"')
		exp->split[0] = ft_substr(str, i + 1, j - i - 1);
	else
		exp->split[0] = ft_substr(str, i, j - i + 1);
	exp->split[1] = ft_substr(str, j + 1, ft_strlen(str) - j);
	if (exp->split[0] == NULL || exp->split[1] == NULL)
		ft_expand_error(exp);
}

char	*ft_expand_start(struct s_expand *exp, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0' && str[i] != '$' && str[i] != '\'' && str[i] != '"')
		i++;
	if (str[i] == '\0')
	{
		exp->buff = ft_expand_join(exp, exp->buff, str);
		return (exp->buff);
	}
	exp->c = str[i];
	j = i + 1;
	while ((exp->c == '$' && isexp(str, i, j) == 0) \
		|| (exp->c != '$' && str[j] != '\0' && str[j] != exp->c))
		j++;
	ft_expand_init(exp, str, i, j);
	ft_expand_replace(exp, exp->split[0]);
	free(str);
	return (exp->buff);
}

void	ft_expand(struct s_lexer *lexer, struct s_shell *ms)
{
	int				i;
	struct s_expand	exp;

	while (lexer != NULL)
	{
		if (lexer->tab != NULL)
		{
			i = 0;
			while (lexer->tab[i] != NULL)
			{
				ft_expand_initstruct(&exp, ms, lexer);
				lexer->tab[i] = ft_expand_start(&exp, lexer->tab[i]);
				i++;
			}
		}
		else if (lexer->token.file != NULL)
		{
			ft_expand_initstruct(&exp, ms, lexer);
			lexer->token.file = ft_expand_start(&exp, lexer->token.file);
		}
		lexer = lexer->next;
	}
}
