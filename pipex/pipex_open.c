/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:03:42 by eewu              #+#    #+#             */
/*   Updated: 2023/09/12 13:21:02 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	ft_openin(t_pipex *m, char *token, char *file, int ambi)
{
	if (!token)
		m->in[0] = open("/dev/stdin", O_RDONLY);
	else if (token && ambi == 0 \
		&& (ft_strcmp(token, "<") || ft_strcmp(token, "<<")))
	{
		m->in[0] = open(file, O_RDONLY);
		if (m->in[0] >= 0)
			m->in_rok = -2;
	}
	if (ambi == 1)
		m->in[0] = -1;
	if (m->in[0] >= 0 && m->in_rok != -2)
		m->in_rok = 0;
	else if (m->in[0] == -1 && m->in_rok != -2)
	{
		if (ambi == 0)
		{
			m->in_rok = errno;
			ft_error(m->cmd->redirlst->token.file, strerror(m->in_rok), \
			(int)m->pids[m->count], m);
		}
		else
			ft_error(m->cmd->redirlst->token.file, "ambiguous redirection", \
			(int)m->pids[m->count], m);
	}
	return (m->in[0]);
}

int	ft_openout(t_pipex *m, char *token, char *file, int ambi)
{
	if (!token)
		m->out = open("/dev/stdout", O_WRONLY);
	else if (ambi == 0 && (ft_strcmp(token, ">") || ft_strcmp(token, ">>")))
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
			ft_error(m->cmd->redirlst->token.file, strerror(m->in_rok), \
			(int)m->pids[m->count], m);
		}
	}
	else if (ambi == 1)
		ft_error(m->cmd->redirlst->token.file, "ambiguous redirection", \
		(int)m->pids[m->count], m);
	return (m->out);
}

void	ft_dupcheck(int fd, int stdfd, t_pipex *m)
{
	if (dup2(fd, stdfd) == -1)
		ft_free_process(m, errno);
}

int	ft_open_redir(t_cmd_lst *tmp, t_pipex *m)
{
	char		*token;
	char		*file;
	t_redir		*redir_tmp;
	int			i;

	i = 0;
	redir_tmp = tmp->redirlst;
	while (redir_tmp && i >= 0)
	{
		token = redir_tmp->token.token;
		file = redir_tmp->token.file;
		if (token && (ft_strcmp(token, "<") || ft_strcmp(token, "<<")))
			i = ft_openin(m, token, file, redir_tmp->token.ambi);
		else if (token && (ft_strcmp(token, ">>") || ft_strcmp(token, ">")))
			i = ft_openout(m, token, file, redir_tmp->token.ambi);
		redir_tmp = redir_tmp->next;
	}
	return (i);
}

int	ft_dup_redir(t_pipex *m, t_cmd_lst *cmd)
{
	t_cmd_lst	*tmp;
	int			i;

	i = 0;
	tmp = cmd;
	if (!cmd)
		return (-1);
	m->bhole = open("/dev/null", O_WRONLY);
	ft_openin(m, NULL, NULL, 0);
	ft_openout(m, NULL, NULL, 0);
	i = ft_open_redir(tmp, m);
	if (m->in_rok > 0 || m->cmd->i != 0)
		ft_dupcheck(m->bhole, STDIN_FILENO, m);
	if (m->in[0] >= 0)
		ft_dupcheck(m->in[0], STDIN_FILENO, m);
	if (m->out >= 0)
		ft_dupcheck(m->out, STDOUT_FILENO, m);
	return (i);
}
