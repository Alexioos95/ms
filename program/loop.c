/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:40:00 by apayen            #+#    #+#             */
/*   Updated: 2023/09/12 12:40:35 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	execution(struct s_shell *ms, struct s_lexer *lexer)
{
	ft_add_tokenword(lexer, ms);
	ft_add_word_to_tab(lexer, ms);
	ft_heredoc(lexer, ms);
	if (ms->status == -1)
	{
		ft_lexerclear(ms->lexer);
		return (1);
	}
	setsigaction(ms, 2);
	ft_expand(lexer, ms);
	ft_start(ms);
	return (0);
}

// Hub du parser.
int	parser(struct s_shell *ms)
{
	t_lexer	*lexer;

	if (g_glob > 1)
		ms->status = 130;
	g_glob = 0;
	if (ms->split != NULL)
	{
		freesplit(ms->split);
		ms->split = NULL;
	}
	if (ms->line == NULL)
		return (0);
	if (checkorphans(ms->line) == 1)
		return (2);
	ft_browse(ms);
	if (ms->lexer)
	{
		lexer = ms->lexer;
		if (execution(ms, lexer) == 1)
			return (130);
		ft_lstclearpipex(&ms->pex->headplus, ms->head);
		free(ms->pex);
		ms->pex = NULL;
	}
	return (ms->status);
}
// ft_print_lexerlst(ms->lexer);
// Pour debug.
