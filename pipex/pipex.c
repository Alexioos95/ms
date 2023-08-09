/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:09:41 by eewu              #+#    #+#             */
/*   Updated: 2023/07/25 16:12:06 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"


void	ft_pipe_process(t_pipex *m)
{
	int			i;

	i = ft_fdspipe(m);
	ft_fork(m);
	if (m->pids[m->count] == 0)
		ft_childprocess(m);
	else
	{
		close(m->fds[i][1]);
		close(m->fds[i][0]);
		if (pipe(m->fds[i]) == -1)
			ft_free_process(m, errno);
		if (m->cmd->i > 0 && m->cmd->tab)
			ft_error(m->cmd->tab[0], "command not found", 42, m);
		m->cmd = m->cmd->next;
		m->nb_cmd--;
		m->count++;
		m->in_rok = 0;
		m->out_rok = 0;
		m->out = -1;
		m->in[0] = -1;
	}
}

void	ft_nopipe_ex(t_pipex *m, t_shell *ms)
{
	m->pids[0] = -1;
	if (!(ft_isabuiltin(m->cmd->tab, ms)))
	{
		ft_fork(m);
		if (m->pids[m->count] == 0)
			ft_childprocess(m);
		else
		{
			if (m->cmd->i > 0 && m->cmd->tab)
				ft_error(m->cmd->tab[0], "command not found", 42, m);
			m->cmd = m->cmd->next;
			m->nb_cmd--;
			// m->count++;
			m->in_rok = 0;
			m->out = -1;
			m->in[0] = -1;
		}
	}
}

void	ft_pipe_ex(t_pipex *m)
{
	ft_mallocpipe(m);
	ft_pipe(m);
	while (m->nb_cmd >= 1)
		ft_pipe_process(m);
	m->count--;
}

int	ft_end(t_shell *ms)
{
	int			i;
	int			n;
	t_pipex		*m;

	n = 0;
	i = 0;
	m = ms->pex;
	ft_closefds(m);
	while (1)
	{
		if (i == m->nb_cmd)
			i = 0;
		if (waitpid(m->pids[i], &ms->status, WNOHANG) > 0)
			n++;
		if (n == m->nb_cmd)
			break ;
		i++;
	}
	ft_free_process(m, errno);
	return (1);
}

int	ft_start(t_shell *ms)
{
	int			nb_cmd;
	char		**env;
	t_pipex		*m;

	env = listtotab(ms);
	m = NULL;
	nb_cmd = ft_nb_cmd(ms->lexer);
	m = ft_init(m, nb_cmd, env);
	ms->pex = m;
	m->ms = ms;
	if (!m)
		return (1);
	find_cmd(m, ms);
	if (nb_cmd >= 2 && env)
		ft_pipe_ex(m);
	else if (nb_cmd == 1 && env)
		ft_nopipe_ex(m, ms);
	ft_end(ms);
	free(env);
	return (1);
}

	// print_allcmd(m);
