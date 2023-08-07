/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 22:41:57 by marvin            #+#    #+#             */
/*   Updated: 2023/08/06 22:42:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_expand_error(struct s_expand *exp)
{
	if (exp->split[0] != NULL)
		free(exp->split[0]);
	if (exp->split[1] != NULL)
		free(exp->split[1]);
	if (exp->split[2] != NULL)
		free(exp->split[2]);
	if (exp->buff != NULL)
		free(exp->buff);
	if (exp->tmp != NULL)
		free(exp->tmp);
	throwerror(exp->ms, "malloc");
}

char	*ft_expand_join(struct s_expand *exp, char *s1, char *s2)
{
	char	*half;

	if (s2 == NULL)
		ft_expand_error(exp);
	half = ft_strjoin(s1, s2);
	if (half == NULL)
		ft_expand_error(exp);
	free(s1);
	free(s2);
	return (half);
}

int isexp(char *str, int i, int j)
{
	if (str[j] == '\0')
		return (1);
	else if (str[i] == '$' && (str[i + 1] == '?' || str[j + 1] == ' '))
		return (1);
	else if (str[j + 1] == '\0' || str[j + 1] == '$' \
		|| str[j + 1] == '\'' || str[j + 1] == '"')
		return (1);
	return (0);
}

void	ft_expand_initstruct(struct s_expand *exp, t_shell *ms, t_lexer *lex)
{
	exp->split[0] = NULL;
	exp->split[1] = NULL;
	exp->split[2] = NULL;
	exp->tmp = NULL;
	exp->i = 0;
	exp->j = 0;
	exp->c = '\0';
	exp->node = NULL;
	exp->ms = ms;
	exp->lex = lex;
	exp->buff = malloc(sizeof(char) * 1);
	if (exp->buff == NULL)
		ft_expand_error(exp);
	exp->buff[0] = '\0';
}
