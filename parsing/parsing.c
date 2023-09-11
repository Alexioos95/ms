/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:53:38 by apayen            #+#    #+#             */
/*   Updated: 2023/09/11 12:58:25 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

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
	if (checkorphanbracket(ms->line) == 1 || checkorphanquote(ms->line) == 1)
		return (2);
	ft_browse(ms);
	if (ms->lexer)
	{
		lexer = ms->lexer;
		ft_add_tokenword(lexer, ms);
		ft_add_word_to_tab(lexer, ms);
		ft_heredoc(lexer, ms);
		if (ms->status == -1)
		{
			ft_lexerclear(ms, ms->lexer);
			return (130);
		}
		setsigaction(ms, 2);
		ft_expand(lexer, ms);
		// ft_print_lexerlst(ms->lexer);
		ft_start(ms);
		// ft_lstclearpipex (&ms->pex->cmd);
		ft_lstclearpipex(&ms->pex->headplus, ms->head);
		// free (ms->lexer);
		ms->pex->cmd = NULL;
		free(ms->pex);
		ms->pex = NULL;
		// ft_lexerclear(ms, ms->lexer);
		// ms->lexer = NULL;
	}
	return (ms->status);
}

int	ft_state(char c, int state)
{
	if (c == '\"' && state <= 1)
		state = 2;
	else if (c == '\"' && state == 2)
		state = 0;
	else if (c == '\'' && state <= 1)
		state = 3;
	else if (c == '\'' && state == 3)
		state = 0;
	return (state);
}

int	ft_istoken(char c)
{
	int		i;
	char	*tokens;

	tokens = "<>|&";
	i = 0;
	while (tokens[i])
	{
		if (tokens[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_isthereatoken(char *line, t_lexer **lexer, t_shell *ms)
{
	int			i;
	int			s;
	t_tokens	token;
	char		*word;

	i = 0;
	s = ft_state(line[i], 0);
	if (ft_istoken(line[i]) && s == 0)
		i = ft_goodtoken(line, &token, &word, ms);
	else if (!ft_istoken(line[i]) || ft_state(line[i], s) > 0)
		i = ft_goodword(line, &token, &word, s);
	if (0 != i)
		ft_lexer_addback(lexer, ft_lexer_new(word, token), ms);
	return (i);
}

void	ft_browse(t_shell *ms)
{
	int			i;
	int			n;
	t_lexer		*lexer;
	char		**split;

	i = 0;
	lexer = NULL;
	split = ft_split(ms->line, ' ');
	while (split[i])
	{
		n = 0;
		while (n != ft_strlen(split[i]))
			n += ft_isthereatoken(&split[i][n], &lexer, ms);
		i++;
	}
	freesplit (split);
	ms->lexer = lexer;
}
