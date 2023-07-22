/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:53:15 by eewu              #+#    #+#             */
/*   Updated: 2023/07/21 17:19:30 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_free_process(t_pipex *m, int r)
{
	int	s;

	s = m->ms->status;
	ft_lstclearpipex(&m->head);
	ft_closefds(m);
	ft_freefds(m);
	ft_closeoutin(m);
	if (m->nb_cmd == 1 && m->out < 0)
	{
		free(m);
		exit (1);
	}
	free(m);
	if (WIFEXITED(s))
		exit(WEXITSTATUS(s));
	else
		exit (r);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
}

void	ft_closeoutin(t_pipex *m)
{
	if (m->in[0] >= 0)
		close(m->in[0]);
	if (m->in[1] >= 0)
		close(m->in[1]);
	if (m->out >= 0)
		close(m->out);
	if (m->bhole >= 0)
		close(m->bhole);
}

void	ft_closefds(t_pipex *m)
{
	int	i;

	i = 0;
	while (i < m->pipe)
	{
		if (m->fds[i][1] >= 0)
			close(m->fds[i][1]);
		if (m->fds[i][0] >= 0)
			close(m->fds[i][0]);
		i++;
	}
}

void	ft_freefds(t_pipex *m)
{
	int	i;

	i = 0;
	while (i < m->pipe)
		free(m->fds[i++]);
	if (m->pipe)
	{
		free(m->fds);
		free(m->pids);
	}
}
