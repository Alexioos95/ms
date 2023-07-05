/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:01:50 by eewu              #+#    #+#             */
/*   Updated: 2023/06/22 11:47:25 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"


void	ft_pipe(t_struct *m)
{
	int	i;

	i = 0;
	while (i < m->nb_cmd)
	{
		m->pids[i] = -1;
		if (i < 2)
		{
			if (pipe(m->fds[i]) == -1)
				ft_free_process(m, errno);
			m->pipe++;
		}
		i++;
	}
}

int	ft_fdspipe(t_struct *m)
{
	int	i;

	i = 0;
	m->i = m->nb_cmd % 2;
	if (m->i == 0)
		i = 1;
	return (i);
}

void	ft_fork(t_struct *m)
{
	if (m->nb_cmd >= 1)
	{
		m->pids[m->count] = fork();
		if (m->pids[m->count] == -1)
		{
			perror("fork");
			ft_free_process(m, errno);
		}
	}
}

void	ft_childprocess(t_struct *m, char *out)
{
	int	i;

	i = 0;
	if (m->i == 0)
		i = 1;
	if (m->count > 0)
	{
		close(m->fds[i][1]);
		ft_dupcheck(m->fds[i][0], STDIN_FILENO, m);
	}
	if (m->nb_cmd > 1)
	{
		close(m->fds[m->i][0]);
		ft_dupcheck(m->fds[m->i][1], STDOUT_FILENO, m);
	}
	else
	{
		ft_openout(m, out);
		if (m->out >= 0)
			ft_dupcheck(m->out, STDOUT_FILENO, m);
		else
			ft_free_process(m, errno);
	}
	ft_cmdex(m->cmd->tab, m->ev, m);
}

void	ft_cmdex(char **cmd, char **ev, t_struct *m)
{
	ft_closefds(m);
	ft_closeoutin(m);
	if (m->cmd->i != 0)
		ft_error(cmd[0], "error", m->pids[m->count], m);
	if (m->in_rok == 0)
		execve(cmd[0], cmd, ev);
	ft_free_process(m, errno);
}
