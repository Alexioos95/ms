/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:01:50 by eewu              #+#    #+#             */
/*   Updated: 2023/09/11 16:11:27 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_pipe(t_pipex *m)
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

int	ft_fdspipe(t_pipex *m)
{
	int	i;

	i = 0;
	m->i = m->nb_cmd % 2;
	if (m->i == 0)
		i = 1;
	return (i);
}

void	ft_fork(t_pipex *m)
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

void	ft_childprocess(t_pipex *m)
{
	int	i;

	i = 0;
	if (m->i == 0)
		i = 1;
	setsigaction(m->ms, 0);
	if (m->count > 0 && m->in_rok != -2)
		ft_dupcheck(m->fds[i][0], STDIN_FILENO, m);
	if (m->nb_cmd > 1 && m->out_red != 1)
		ft_dupcheck(m->fds[m->i][1], STDOUT_FILENO, m);
	ft_dup_redir(m, m->cmd);
	ft_cmdex(m->cmd->tab, m->ev, m);
}

void	ft_cmdex(char **cmd, char **ev, t_pipex *m)
{
	char	*error_type;

	error_type = "command not found";
	if (m->cmd->i == -1)
		error_type = "Is a directory";
	// printf("minishell: %s: Is a directory\n", path);
	ft_closefds(m);
	ft_closeoutin(m);
	ft_freefds(m);
	if ((m->out_rok == 0 && (m->in_rok == 0 || m->in_rok == -2)) \
			&& cmd && m->cmd->i == 0 \
			&& !(ft_isabuiltin(m->cmd->tab, m->ms, 1)))
		execve(m->cmd->name, cmd, ev);
	if (m->cmd->i == 13)
		error_type = strerror(m->cmd->i);
	if (!(ft_isabuiltin(m->cmd->tab, m->ms, 0)))
		ft_error(cmd[0], error_type, 0, m);
	ft_exitchild(m, m->ms->status);
}
