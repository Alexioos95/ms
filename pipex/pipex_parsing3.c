/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsing3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:43:32 by eewu              #+#    #+#             */
/*   Updated: 2023/09/19 10:55:06 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_cmd_list(t_pipex *m, t_shell *ms)
{
	char	**tab;
	char	*name;
	t_lexer	*lexer;

	lexer = ms->lexer;
	name = NULL;
	while (lexer && ms->error == 0)
	{
		tab = ft_find_nodecmd(&lexer, ms);
		if (tab)
			ft_checkaccees(m, &lexer, tab);
		else if (!tab && ms->error == 0)
		{
			ft_fake_command(m, ms, tab, name);
			if (ms->error == 1)
				return ((void)free(tab));
		}
		if (lexer)
			lexer = lexer->next;
	}
	m->cmd_i = 0;
}

void	find_cmd(t_pipex *m, t_shell *ms)
{
	t_lst	*node_env;

	node_env = ft_getenv(ms, "PATH");
	if (node_env && node_env->print == 1)
	{
		m->s_ev = ft_split(&node_env->line[5], ':');
		if (m->s_ev == NULL)
			return ((void)free(ms->tabenv));
	}
	else
	{
		m->s_ev = ft_calloc(sizeof(char *), 2);
		if (!m->s_ev)
			return ((void)free(ms->tabenv));
		m->s_ev[0] = ft_calloc(sizeof(char), 1);
		if (!m->s_ev[0])
		{
			freesplit(m->s_ev);
			m->s_ev = NULL;
			return ((void)free(ms->tabenv));
		}
	}
	ft_cmd_list(m, ms);
	ft_redir_list(m, ms);
	ft_free_tab(m->s_ev);
}
