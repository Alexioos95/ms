/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:53:38 by apayen            #+#    #+#             */
/*   Updated: 2023/07/18 10:37:29 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// Parser.
int	parser(struct s_shell *ms)
{
	t_lexer	*lexer;

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
		// lexer = ms->lexer;
		ft_add_word_to_tab(lexer, ms);
		ft_print_lexerlst(ms->lexer);
		ft_lexerclear(ms->lexer);
	}
	return (0);
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

int	ft_isthereatoken(char *line, t_lexer **lexer)
{
	int			i;
	int			s;
	t_tokens	token;
	char		*word;

	i = 0;
	s = ft_state(line[i], 0);
	if (ft_istoken(line[i]) && s == 0)
		i = ft_goodtoken(line, &token, &word, s);
	else if (!ft_istoken(line[i]) || ft_state(line[i], s) > 0)
		i = ft_goodword(line, &token, &word, s);
	if (0 != i)
		ft_lexer_addback(lexer, ft_lexer_new(word, token));
	return (i);
}

void	ft_browse(t_shell *ms)
{
	int			i;
	int			n;
	char		*line;
	t_lexer		*lexer;
	char		**split;

	line = ms->line;
	i = 0;
	lexer = NULL;
	split = ft_split(ms->line, ' ');
	while (split[i])
	{
		n = 0;
		while (n != ft_strlen(split[i]))
			n += ft_isthereatoken(&split[i][n], &lexer);
		i++;
	}
	freesplit (split);
	ms->lexer = lexer;
}
