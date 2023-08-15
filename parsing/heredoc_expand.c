/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:31:20 by apayen            #+#    #+#             */
/*   Updated: 2023/08/15 13:55:35 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_heredoc_error(struct s_heredoc *hd)
{
	if (hd->name != NULL)
	{
		unlink(hd->name);
		free(hd->line);
	}
	throwerror(hd->ms, "malloc");
}

char	*ft_heredoc_expand(struct s_heredoc *hd, char *str)
{
	struct s_expand	exp;

	ft_expand_initstruct(&exp, hd->ms, hd->ms->lexer);
	exp.hd = hd;
	exp.i = 0;
	if (str[0] == '\0')
		return (str);
	while (str[exp.i] != '\0')
	{
		exp.j = exp.i;
		while (str[exp.i] != '\0' && str[exp.i] != '$')
			exp.i++;
		if (str[exp.i] == '\0')
		{
			exp.buff = ft_expand_join(&exp, exp.buff, &str[exp.j]);
			dprintf(2, "buff: %s\n", exp.buff);
			return (exp.buff);
		}
		while (isexp(&exp, str, exp.i, exp.j + 1) == 0)
			exp.j++;
		dprintf(2, "str[j]: %s\n", &str[exp.j]);
		ft_expand_init(&exp, str, exp.i, exp.j);
		dprintf(2, "exp.buff: %s\nexp.split[0]: %s\nexp.split[1]: %s\n", exp.buff, exp.split[0], exp.split[1]);
		dprintf(2, "i: %d\nj: %d\n", exp.i, exp.j);
		ft_expand_dollar(&exp, exp.split[0]);
		exp.i = exp.j + 1;
	}
	return (exp.buff);
}
