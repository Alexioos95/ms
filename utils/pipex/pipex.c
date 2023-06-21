/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:09:41 by eewu              #+#    #+#             */
/*   Updated: 2023/06/20 16:58:21 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	ft_process(t_struct *m, char *out)
{
	int	i;

	i = ft_fdspipe(m);
	ft_fork(m);
	if (m->pids[m->count] == 0)
	{
		if (m->in_rok != 0 || m->cmd->i != 0)
			ft_dupcheck(m->bhole, STDIN_FILENO, m);
		ft_childprocess(m, out);
	}
	else
	{
		close(m->fds[i][1]);
		close(m->fds[i][0]);
		if (pipe(m->fds[i]) == -1)
			ft_free_process(m, errno);
		if (m->cmd->i != 0)
			ft_error(m->cmd->tab[0], "command not found", 42, m);
		m->cmd = m->cmd->next;
		m->nb_cmd--;
		m->count++;
		m->in_rok = 0;
	}
}

static size_t	ft_gnllen(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\n')
		i++;
	return (i);
}

static int	ft_limiter(t_struct *m, char *line)
{
	size_t		i;

	i = 0;
	if (ft_gnllen(line) != ft_strlen(m->limit))
		return (0);
	while (line[i] != '\n')
	{
		if (line[i] != m->limit[i])
			break ;
		i++;
	}
	if (i == ft_strlen(m->limit))
		return (1);
	else
		return (0);
}

static void	ft_gnl(t_struct *m)
{
	char	*line;
	int		i;

	if (pipe(m->in) == -1)
	{
		perror("pipe");
		ft_free_process(m, errno);
	}
	m->hdoc = 0;
	while (1)
	{
		i = 0;
		ft_printheredoc(m);
		line = get_next_line(0);
		if (line == NULL || ft_limiter(m, line))
		{
			free(line);
			break ;
		}
		while (line[i])
			write(m->in[1], &line[i++], 1);
		free(line);
	}
	close(m->in[1]);
	m->in_rok = 0;
}

void	ft_pipex(t_struct *m, char *out, char *in)
{
	int	i;

	i = 0;
	// ft_openin(m, in);
	// find_cmd(m);
	// m->nb_cmd = ft_lstsize(m->cmd);
	ft_mallocpipe(m);
	if (m->hdoc && m->ac >= 6)
		ft_gnl(m);
	if (m->in[0] >= 0)
		ft_dupcheck(m->in[0], STDIN_FILENO, m);
	ft_pipe(m);
	while (m->nb_cmd >= 1)
		ft_process(m, out);
	ft_closefds(m);
	while (waitpid(m->pids[i], &m->status, 0) > 0 && i < m->count - 1)
		i++;
}
