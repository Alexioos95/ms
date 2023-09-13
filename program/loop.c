/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:40:00 by apayen            #+#    #+#             */
/*   Updated: 2023/09/12 18:32:42 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	execution(struct s_shell *ms, struct s_lexer *lexer)
{
	ft_add_tokenword(lexer, ms);
	ft_add_word_to_tab(lexer, ms);
	// ft_print_lexerlst(ms->lexer);
	if (ms->error == 1)
		return (1);
	ft_heredoc(lexer, ms);
	if (ms->status == -1)
	{
		ms->status = 130;
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

	ms->error = 0;
	if (ms->line == NULL)
		return (0);
	if (checkorphans(ms->line) == 1)
		return (2);
	ft_browse(ms);
	if (ms->lexer && ms->error == 0)
	{
		lexer = ms->lexer;
		if (execution(ms, lexer) == 0)
		{
			ft_lstclearpipex(&ms->pex->headplus);
			free(ms->pex);
			ms->pex = NULL;	
		}
	}
	ft_lexerclear(ms->head);
	ms->head = NULL;
	return (ms->status);
}
// ft_print_lexerlst(ms->lexer);
// Pour debug.
