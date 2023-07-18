/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:21:57 by eewu              #+#    #+#             */
/*   Updated: 2023/07/18 12:29:37 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// char	*ft_expected_token(char *curr_token)
// {
// 	int		i;
// 	char	**token;

// 	i = 0;
// 	token = ft_split("< > << >> |", ' ');
// 	if (ft_tabcmp(curr_token, token))
// 		return (curr_token);
// 	return (NULL);
// }

int	ft_goodtoken(char *line, t_tokens *token, char **word, int state)
{
	int		i;
	char	c;
	char	**good_tokens;
	char	*curr_token;

	i = 0;
	c = line[i];
	good_tokens = ft_split("< > << >> |", ' ');
	while ((ft_istoken(line[i]) && state == 0) && line[i] && (c == line[i]))
		state = ft_state(line[++i], state);
	curr_token = ft_subnstr(line, 0, i);
	if (!ft_tabcmp(curr_token, good_tokens))
	{
		free (curr_token);
		curr_token = NULL;
	}
	freesplit (good_tokens);
	*token = ft_newtoken(curr_token, NULL);
	*word = NULL;
	return (i);
}

int	ft_goodword(char *line, t_tokens *token, char **word, int state)
{
	int		i;

	i = 0;
	while ((!ft_istoken(line[i]) || state > 0) && line[i])
		state = ft_state(line[++i], state);
	*token = ft_newtoken(NULL, NULL);
	*word = ft_subnstr(line, 0, i);
	return (i);
}

void	ft_add_tokenword(t_lexer *lexer, t_shell *ms)
{
	t_lexer	*tmp;

	while (lexer)
	{
		if (lexer->token.token && \
		(lexer->next && lexer->next->str && lexer->next->i != 0))
		{
			tmp = lexer->next->next;
			lexer->token.arg = lexer->next->str;
			lexer->next->str = NULL;
			free (lexer->next);
			lexer->next = tmp;
			lexer = tmp;
			ms->lexer->len--;
		}
		else
			lexer = lexer->next;
	}
}

void	ft_add_word_to_tab(t_lexer *lexer, t_shell *ms)
{
	int		nb_tab;
	t_lexer	*node_cmd;


	while (lexer)
	{
		node_cmd = lexer;
		nb_tab = 0;
		while (lexer && lexer->str)
		{
			nb_tab++;
			lexer = lexer->next;
		}
		if (nb_tab)
			ft_tabptr(ms, node_cmd, node_cmd, nb_tab);
		while (lexer && !lexer->str)
			lexer = lexer->next;
	}
}


void	ft_tabptr(t_shell *ms, t_lexer *node_cmd, t_lexer *tmp, int nb_tab)
{
	int			i;

	i = 0;
	(tmp) = node_cmd;
	(node_cmd)->tab = ft_calloc(sizeof (char *), (nb_tab + 1));
	if (!(node_cmd)->tab)
		return ;
	(node_cmd)->tab[i++] = (tmp)->str;
	(tmp)->str = NULL;
	(tmp) = (tmp)->next;
	while (i < nb_tab && (tmp) && (tmp)->str)
		ft_lexer_delone((&tmp), i++);
	ms->lexer->len -= nb_tab - 1;
}