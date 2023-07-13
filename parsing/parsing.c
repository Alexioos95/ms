/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:53:38 by apayen            #+#    #+#             */
/*   Updated: 2023/07/13 14:12:43 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

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
	if (checkorphanbracket(ms->line) == 1 || checkorphanquote(ms->line) == 1)
		return (2);
	ft_browse(ms);
	if (ms->lexer)
	{
		printf("Taille du Lexer: %d\n", ms->lexer->len);
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
	int			y;
	int			s;
	t_tokens	token;
	char		*str;

	y = 0;
	s = 0;
	if (ft_istoken(line[y]) && ft_state(line[y], s) == 0)
	{
		while ((ft_istoken(line[y]) && ft_state(line[y], s) == 0) && line[y])
			s = ft_state(line[y++], s);
		token = ft_newtoken(ft_subnstr(line, 0, y), NULL);
		str = NULL;
	}
	else if (!ft_istoken(line[y]) || ft_state(line[y], s) > 0)
	{
		while ((!ft_istoken(line[y]) || ft_state(line[y], s) > 0) && line[y])
			s = ft_state(line[y++], s);
		token = ft_newtoken(NULL, NULL);
		str = ft_subnstr(line, 0, y);
	}
	if (0 != y)
		ft_lexer_addback(lexer, ft_lexer_new(str, token));
	return (y);
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
