/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parth.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:14:53 by eewu              #+#    #+#             */
/*   Updated: 2023/07/18 18:15:05 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"


char	**ft_find_nodecmd(t_lexer **lexer)
{
	while ((*lexer))
	{
		if ((*lexer)->tab)
			return ((*lexer)->tab);
		(*lexer) = (*lexer)->next;
	}
	return (NULL);
}

void	ft_access(t_struct *m, char **tab_cmd, int j, int p)
{
	char	*join;

	if (p == 0)
		ft_pipex_lstadd_back(&m->cmd, ft_pipex_lstnew(tab_cmd, p), m);
	else
	{
		while (m->s_ev[j] && p != 0 && (int)ft_strlen(tab_cmd[0]) >= 1)
		{
			join = ft_pipex_join(m->s_ev[j++], tab_cmd[0]);
			if (access(join, X_OK) != 0)
				free(join);
			else
			{
				free(tab_cmd[0]);
				tab_cmd[0] = join;
				p = 0;
				ft_pipex_lstadd_back(&m->cmd, ft_pipex_lstnew(tab_cmd, p), m);
			}
		}
		if (p != 0)
			ft_pipex_lstadd_back(&m->cmd, ft_pipex_lstnew(tab_cmd, p), m);
	}
}

void	ft_list_tab(t_struct *m, t_shell *ms)
{
	char	**tab_cmd;
	t_lexer	*lexer;

	lexer = ms->lexer;
	while (lexer)
	{
		tab_cmd = ft_find_nodecmd(&lexer);
		if (tab_cmd)
		{
			if (((int)ft_strlen(tab_cmd[0]) >= 1) && \
			(tab_cmd[0][0] == '/' || (tab_cmd[0][0] == '.')))
			{
				if (!access(tab_cmd[0], X_OK))
					m->eror = 0;
				else
					m->eror = errno;
			}
			else
				m->eror = 2;
			ft_access(m, tab_cmd, 0, m->eror);
		}
		lexer = lexer->next;
	}
	m->cmd_i = 0;
}

void	find_cmd(t_struct *m, t_shell *ms)
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
	ft_list_tab(m, ms);
	ft_free_tab(m->s_ev);
}
