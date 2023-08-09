/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:03:42 by eewu              #+#    #+#             */
/*   Updated: 2023/07/25 15:01:18 by eewu             ###   ########.fr       */
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

void	ft_open_redir(t_cmd_lst *tmp, t_pipex *m)
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
		if (token && ft_strcmp(token, "<"))
			i = ft_openin(m, token, file);
		else if (token && (ft_strcmp(token, ">>") || ft_strcmp(token, ">")))
			i = ft_openout(m, token, file);
		redir_tmp = redir_tmp->next;
	}
}

void	ft_dup_redir(t_pipex *m, t_cmd_lst *cmd)
{
	t_cmd_lst	*tmp;

	tmp = cmd;
	if (!cmd)
		return ;
	m->bhole = open("/dev/null", O_WRONLY);
	ft_openin(m, NULL, NULL);
	ft_openout(m, NULL, NULL);
	ft_open_redir(tmp, m);
	if (m->in_rok > 0 || m->cmd->i != 0)
		ft_dupcheck(m->bhole, STDIN_FILENO, m);
	if (m->in[0] >= 0)
		ft_dupcheck(m->in[0], STDIN_FILENO, m);
	if (m->out >= 0)
		ft_dupcheck(m->out, STDOUT_FILENO, m);
}
