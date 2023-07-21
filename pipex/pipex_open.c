/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:03:42 by eewu              #+#    #+#             */
/*   Updated: 2023/07/21 17:25:40 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	ft_openin(t_pipex *m, char *token, char *file)
{
	if (!token)
		m->in[0] = open("/dev/stdin", O_RDONLY);
	else if (token && ft_strcmp(token, "<"))
	{
		m->in[0] = open(file, O_RDONLY);
		if (m->in[0] >= 0)
			m->in_rok = -2;
	}
	if (m->in[0] >= 0 && m->in_rok != -2)
		m->in_rok = 0;
	else if (m->in[0] == -1 && m->in_rok != -2)
	{
		m->in_rok = errno;
		ft_error(m->cmd->redirlst->token.file, strerror(m->in_rok), 42, m);
	}
	return (m->in[0]);
}

int	ft_openout(t_pipex *m, char *token, char *file)
{
	if (!token)
		m->out = open("/dev/stdout", O_WRONLY);
	else if (ft_strcmp(token, ">") || ft_strcmp(token, ">>"))
	{
		if (ft_strcmp(token, ">"))
			m->out = open(file, O_WRONLY | O_TRUNC);
		else if (ft_strcmp(token, ">>"))
			m->out = open(file, O_WRONLY | O_APPEND);
		if (m->out == -1)
			m->out = open(file, O_WRONLY | O_CREAT, 0644);
		if (m->out >= 0)
			m->out_red = 1;
		else
		{
			m->out_rok = errno;
			ft_error(file, strerror(errno), 42, m);
		}
	}
	return (m->out);
}
void	ft_dupcheck(int fd, int stdfd, t_pipex *m)
{
	if (dup2(fd, stdfd) == -1)
		ft_free_process(m, errno);
}

int	ft_error(char *file, char *error, int pid, t_pipex *m)
{
	if (pid == 0)
	{
		if (m->cmd->i == 13)
			ft_free_process(m, 126);
		else
			ft_free_process(m, 127);
	}
	else
	{
		if (m->cmd->i == 13)
			printf("bash: permission denied: %s\n", file);
		else
			printf("bash: %s: %s\n", file, error);
		return (0);
	}
}
