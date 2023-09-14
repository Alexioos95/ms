/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:09:41 by eewu              #+#    #+#             */
/*   Updated: 2023/09/14 10:41:24 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_process(t_pipex *m, t_shell *ms)
{
	int			i;
	t_lexer		*redir;

	i = ft_fdspipe(m);
	redir = ms->lexer;
	if (m->cmd)
		ft_fork(m);
	if (m->cmd && m->pids[m->count] == 0)
		ft_childprocess(m);
	else
	{
		close(m->fds[i][1]);
		close(m->fds[i][0]);
		if (m->cmd->tab[0][0] == '\0')
		{
			free(m->cmd->tab[0]);
			free(m->cmd->tab[1]);
		}
		if (pipe(m->fds[i]) == -1)
			ft_free_process(m);
		if (m->cmd)
			m->cmd = m->cmd->next;
		m->nb_cmd--;
		m->count++;
		m->in_rok = 0;
		m->out_rok = 0;
		m->out = -1;
		m->in[0] = -1;
	}
}

void	ft_exec(t_pipex *m, t_shell *ms)
{
	char	*builtins;

	builtins = NULL;
	m->pids[0] = -1;
	builtins = (ft_isabuiltin(m->cmd->tab, ms, 1));
	if (builtins == NULL)
	{
		ft_fork(m);
		if (m->pids[m->count] == 0)
			ft_childprocess(m);
		else
		{
			if (m->cmd)
				m->cmd = m->cmd->next;
			m->nb_cmd--;
			m->count++;
			m->in_rok = 0;
			m->out_rok = 0;
			m->out = -1;
			m->in[0] = -1;
		}
	}
	else if (builtins && (m->in_rok > 0 || m->out_rok > 0))
		m->ms->status = 1;
}

void	ft_pipe_exec(t_pipex *m, t_shell *ms)
{
	ft_mallocpipe(m);
	if (ms->error == 1)
		return ;
	ft_pipe(m);
	if (ms->error == 1)
		return ;
	while (m->nb_cmd >= 1 && ms->error == 0)
		ft_process(m, ms);
}

int	ft_end(t_shell *ms)
{
	int			i;
	int			n;
	int			tmpstatus;
	t_pipex		*m;

	n = 0;
	i = 0;
	m = ms->pex;
	ft_closefds(m);
	while (1 && m->pids[0] != -1)
	{
		if (i == m->count)
			i = 0;
		if (waitpid(m->pids[i], &tmpstatus, WNOHANG) > 0)
		{
			n++;
			if (i == m->count - 1)
				ms->status = tmpstatus;
		}
		if (n == m->count)
			break ;
		i++;
	}
	return (1);
}

int	ft_start(t_shell *ms)
{
	int			nb_cmd;
	t_pipex		*m;
	int			i;

	i = 0;
	ms->tabenv = listtotab(ms);
	if (ms->tabenv == NULL)
		return (1);
	m = NULL;
	nb_cmd = ft_nb_cmd(ms->lexer);
	m = ft_init(m, nb_cmd, ms->tabenv);
	if (!m)
		return (1);
	ms->pex = m;
	m->ms = ms;
	find_cmd(m, ms);
	if (m->s_ev == NULL || ms->error == 1)
		return (ft_free_process(m), free(m), free(ms->tabenv), 1);
	if (nb_cmd >= 2)
	{
		ft_pipe_exec(m, ms);
		if (ms->error == 1)
			return (ft_lstclearpipex(&m->cmd), ft_free_process(m), free(m), free(ms->tabenv), 1);
	}
	else if (nb_cmd == 1)
		ft_exec(m, ms);
	ft_closefds(m);
	ft_end(ms);
	free(ms->tabenv);
	ft_free_process(m);
	return (0);
}

// print_allcmd(m);
// fonction permettant de faire un test et
// print toutes les commandes de l'exec
