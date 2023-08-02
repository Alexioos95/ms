/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:08:14 by eewu              #+#    #+#             */
/*   Updated: 2023/08/02 11:20:37 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_mallocpipe(t_pipex *m)
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

static int	ft_isabuiltin(char **tab, t_shell *ms)
{
	char	**built;
	int		i;
	int		in;
	int		out;

	if (!tab)
		return (0);
	i = 0;
	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	built = ft_split("cd echo env exit export pwd unset", ' ');
	if (ft_tabcmp(tab[0], built))
	{
		i = 1;
		ft_dup_redir(ms->pex, ms->pex->cmd);
	}
	if (ft_strncmp(tab[0], "echo", 4) == 0)
		ms->status = ft_echo(tab);
	else if (ft_strncmp(tab[0], "pwd", 3) == 0)
		ms->status = ft_pwd(ms);
	else if (ft_strncmp(tab[0], "cd", 2) == 0)
		ms->status = ft_cd(ms, tab);
	else if (ft_strncmp(tab[0], "exit", 4) == 0)
		ft_exit(ms, tab);
	else if (ft_strncmp(tab[0], "env", 3) == 0)
		ms->status = ft_env(ms, tab);
	else if (ft_strncmp(tab[0], "unset", 5) == 0)
		ms->status = ft_unset(ms, tab);
	else if (ft_strncmp(tab[0], "export", 6) == 0)
		ms->status = ft_export(ms, tab);
	ft_dupcheck(in, STDIN_FILENO, ms->pex);
	ft_dupcheck(out, STDOUT_FILENO, ms->pex);
	return ((void)freesplit(built), i);
}

void	ft_theone(t_pipex *m, t_shell *ms)
{
	int		i;

	i = 0;
	m->pids[i] = -1;
	if (!(ft_isabuiltin(m->cmd->tab, ms)))
	{
		ft_fork(m);
		if (m->pids[m->count] == 0)
			ft_childprocess(m);
		else
		{
			if (m->cmd->i > 0 && m->cmd->tab)
				ft_error(m->cmd->tab[0], "command not found", 42, m);
			m->cmd = m->cmd->next;
			m->nb_cmd--;
			m->count++;
			m->in_rok = 0;
			m->out = -1;
			m->in[0] = -1;
		}
	}
}

t_pipex	*ft_init(t_pipex *m, int nb_cmd, char **env)
{
	m = malloc(sizeof(t_pipex));
	if (!m)
		return (0);
	m->count = 0;
	m->in[0] = -1;
	m->in[1] = -1;
	m->pipe = 0;
	m->out = -1;
	m->bhole = -1;
	m->in_rok = -1;
	m->out_rok = 0; // fix mis par Alexis pour unconditionnal jump
	m->out_red = 0; // fix mis par Alexis pour unconditionnal jump
	m->cmd_i = 0;
	m->hdoc = 0;
	m->cmd_join = NULL;
	m->limit = NULL;
	m->ev = env;
	m->s_ev = NULL;
	m->av = NULL;
	m->cmd = NULL;
	m->nb_cmd = nb_cmd;
	m->i = m->nb_cmd % 2;
	m->pids = malloc (sizeof(pid_t) * (unsigned long)m->nb_cmd);
	if (!m->pids)
		ft_free_process(m, errno);
	return (m);
}
	// m->ac = nb_cmd;

	// m->limit = av[2];
	// in = av[1];
	// out = av[nb_cmd - 1];
