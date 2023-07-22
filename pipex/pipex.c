/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:09:41 by eewu              #+#    #+#             */
/*   Updated: 2023/07/21 17:58:42 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

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
	int			i;

	i = 0;
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

void	ft_process(t_pipex *m, t_shell *ms)
{
	int			i;
	t_lexer		*redir;

	i = ft_fdspipe(m);
	redir = ms->lexer;
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

void	ft_pipex(t_pipex *m, t_shell *ms)
{
	int	i;

	i = 0;
	ft_mallocpipe(m);
	ft_pipe(m);
	while (m->nb_cmd >= 1)
		ft_process(m, ms);
}

int	ft_start(t_shell *ms)
{
	int			nb_cmd;
	char		**env;
	t_pipex		*m;
	int			i;

	i = 0;
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
		ft_pipex(m, ms);
	else if (nb_cmd == 1 && env)
		ft_theone(m, ms);
	ft_closefds(m);
	while (waitpid(m->pids[i], &m->ms->status, 0) > 0 && i <= m->count - 1)
		i++;
	// ft_lstclearpipex(&m->head);
	// ft_free_process(m, errno);
	return (1);
}

	// print_allcmd(m);