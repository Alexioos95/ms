/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:14:53 by eewu              #+#    #+#             */
/*   Updated: 2023/07/21 11:40:50 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	**ft_find_nodecmd(t_lexer **lexer)
{
	while ((*lexer) && !((*lexer)->token.pipe))
	{
		if ((*lexer)->tab)
			return ((*lexer)->tab);
		(*lexer) = (*lexer)->next;
	}
	return (NULL);
}

void	ft_access(t_pipex *m, char **tab, int j, int p)
{
	char	*join;

	if (p == 0)
		ft_pipex_lstadd_back(&m->cmd, ft_pipex_lstnew(tab, tab[0], p), m);
	else
	{
		while (m->s_ev[j] && p != 0 && (int)ft_strlen(tab[0]) >= 1)
		{
			join = ft_pipex_join(m->s_ev[j++], tab[0]);
			if (access(join, X_OK) != 0)
				free(join);
			else
			{
				p = 0;
				ft_pipex_lstadd_back(&m->cmd, ft_pipex_lstnew(tab, join, p), m);
			}
		}
		if (access(tab[0], X_OK) == 0 && p != 0)
			ft_pipex_lstadd_back(&m->cmd, ft_pipex_lstnew(tab, tab[0], 0), m);
		else if ((access(tab[0], X_OK) != 0) && p != 0)
			ft_pipex_lstadd_back(&m->cmd, ft_pipex_lstnew(tab, tab[0], p), m);
	}
}

void	ft_cmd_list(t_pipex *m, t_shell *ms)
{
	char	**tab;
	t_lexer	*lexer;

	lexer = ms->lexer;
	while (lexer)
	{
		tab = ft_find_nodecmd(&lexer);
		if (tab)
		{
			if (((int)ft_strlen(tab[0]) >= 1) && ((tab[0][0] == '.')))
			{
				if (!access(tab[0], X_OK))
					m->eror = 0;
				else
					m->eror = errno;
			}
			else
				m->eror = 2;
			ft_access(m, tab, 0, m->eror);
			while (lexer && !(lexer->token.pipe))
				lexer = lexer->next;
		}
		else
		{
			tab = ft_calloc (sizeof (char *), 2);
			if (!tab)
				return ;
			tab[0] = ft_calloc(sizeof(char), 1);
			if (!tab[0])
				return ;
			ft_pipex_lstadd_back(&m->cmd, ft_pipex_lstnew(tab, tab[0], -2), m);
		}
		if (lexer)
			lexer = lexer->next;
	}
	m->cmd_i = 0;
}

void	find_cmd(t_pipex *m, t_shell *ms)
{
	int		i;
	t_lst	*node_env;

	node_env = ft_getenv(ms, "PATH");
	i = 0;
	if (node_env)
		m->s_ev = ft_split(&node_env->line[5], ':');
	else
	{
		m->s_ev = ft_calloc(sizeof(char *), 2);
		if (!m->s_ev)
			ft_free_process(m, errno);
		m->s_ev[0] = ft_calloc(sizeof(char), 1);
		if (!m->s_ev[0])
			ft_free_process(m, errno);
	}
	ft_cmd_list(m, ms);
	ft_redir_list(m, ms);
	// print_allcmd(m);
	ft_free_tab(m->s_ev);
}
