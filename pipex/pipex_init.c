/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:08:14 by eewu              #+#    #+#             */
/*   Updated: 2023/07/18 15:48:20 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"


void	ft_mallocpipe(t_struct *m)
{
	int	i;

	i = 0;
	m->fds = malloc (sizeof(int *) * (unsigned long)(2));
	if (!m->fds)
		ft_free_process(m, errno);
	while (i < 2)
	{
		m->fds[i] = malloc (sizeof(int) * 2);
		if (!m->fds[i])
			ft_free_process(m, errno);
		i++;
	}
}

void	ft_forkex(t_struct	*m, char *in, char *out)
{
	int	i;

	i = 0;
	(void)in;
	ft_fork(m);
	if (m->pids[m->count] == 0)
	{
		if (m->in_rok != 0 || m->cmd->i != 0)
			ft_dupcheck(m->bhole, STDIN_FILENO, m);
		ft_childprocess(m, out);
	}
	else
	{
		if (m->cmd->i != 0)
			ft_error(m->cmd->tab[0], "command not found", 42, m);
		m->cmd = m->cmd->next;
		m->nb_cmd--;
	}
	while (waitpid(m->pids[i], &m->status, 0) > 0 && i < m->count - 1)
		i++;
}

t_struct	*ft_init(t_struct *m, int nb_cmd, char **env)
{
	m = malloc(sizeof(t_struct));
	if (!m)
		return (0);
	m->count = 0;
	m->in[0] = -1;
	m->in[1] = -1;
	m->pipe = 0;
	m->status = -1;
	m->out = -1;
	m->bhole = -1;
	m->in_rok = -1;
	m->cmd_i = 0;
	m->hdoc = 0;
	m->ac = nb_cmd;
	m->cmd_join = NULL;
	m->limit = NULL;
	m->ev = env;
	m->s_ev = NULL;
	m->av = NULL;
	m->cmd = NULL;
	m->nb_cmd = nb_cmd;
	m->pids = malloc (sizeof(pid_t) * (unsigned long)m->nb_cmd);
	if (!m->pids)
		ft_free_process(m, errno);
	return (m);
}

	// m->limit = av[2];
	// in = av[1];
	// out = av[nb_cmd - 1];
