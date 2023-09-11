/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:14:53 by eewu              #+#    #+#             */
/*   Updated: 2023/09/11 20:03:08 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	**ft_find_nodecmd(t_lexer **lexer)
{
	char	**tab;

	tab = NULL;
	while ((*lexer) && !((*lexer)->token.pipe))
	{
		if ((*lexer)->tab)
			tab = ft_realloc_tab(tab, (*lexer)->tab);
		(*lexer) = (*lexer)->next;
	}
	return (tab);
}

void	ft_access(t_pipex *m, char **tab, int j, int p)
{
	char	*name;

	if (p == 0 || (ft_isabuiltin(tab, m->ms, 0)))
	{
		name = ft_strdup(tab[0]);
		ft_pipex_lstadd_back(&m->cmd, ft_pipex_lstnew(tab, name, 0), m);
	}
	else
	{
		while ((m->s_ev[j] && p != 0 && (int)ft_strlen(tab[0]) >= 1) \
			&& m->eror != -1)
		{
			name = ft_pipex_join(m->s_ev[j++], tab[0]);
			if (access(name, X_OK) != 0)
				free(name);
			else
			{
				p = 0;
				ft_pipex_lstadd_back(&m->cmd, ft_pipex_lstnew(tab, name, p), m);
			}
		}
		if (p != 0)
		{
			name = ft_strdup(tab[0]);
			ft_pipex_lstadd_back(&m->cmd, ft_pipex_lstnew(tab, name, p), m);
		}
	}
}

void	ft_checkaccees(t_pipex *m, t_lexer **lexer, char **tab)
{
	struct stat	dir;

	if (((int)ft_strlen(tab[0]) >= 1) && ((tab[0][0] == '.') || \
		(tab[0][0] == '/')))
	{
		if (lstat(tab[0], &dir) == -1 && errno == ENOMEM)
			ft_free_process(m, 1);
		if (!access(tab[0], X_OK))
			m->eror = 0;
		else
			m->eror = errno;
		if (S_ISDIR(dir.st_mode) || S_ISLNK(dir.st_mode))
			m->eror = -1;
	}
	else
	{
		access(tab[0], X_OK);
		m->eror = errno;
	}
	ft_access(m, tab, 0, m->eror);
	while ((*lexer) && !((*lexer)->token.pipe))
		(*lexer) = (*lexer)->next;
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
			ft_checkaccees(m, &lexer, tab);
		else
		{
			tab = ft_calloc (sizeof (char *), 2);
			if (!tab)
				return ;
			tab[0] = ft_calloc(sizeof(char), 1);
			if (!tab[0])
				return ;
			ft_pipex_lstadd_back(&m->cmd, ft_pipex_lstnew(tab, tab[0], -4), m);
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
	ft_free_tab(m->s_ev);
}

	// print_allcmd(m);