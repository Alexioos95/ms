/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:08:14 by eewu              #+#    #+#             */
/*   Updated: 2023/09/11 14:15:37 by apayen           ###   ########.fr       */
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

void	ft_which_builtin(char **tab, t_shell *ms)
{
	if (ft_strncmp(tab[0], "echo", 4) == 0)
		ms->status = ft_echo(tab);
	else if (ft_strncmp(tab[0], "pwd", 3) == 0)
		ms->status = ft_pwd(ms);
	else if (ft_strncmp(tab[0], "cd", 2) == 0)
		ms->status = ft_cd(ms, tab);
	else if (ft_strncmp(tab[0], "exit", 4) == 0)
		ms->status = ft_exit(ms, tab);
	else if (ft_strncmp(tab[0], "env", 3) == 0)
		ms->status = ft_env(ms, tab);
	else if (ft_strncmp(tab[0], "unset", 5) == 0)
		ms->status = ft_unset(ms, tab);
	else if (ft_strncmp(tab[0], "export", 6) == 0)
		ms->status = ft_export(ms, tab);
}

char	*ft_isabuiltin(char **tab, t_shell *ms, int state)
{
	char	**built;
	char	*is;
	int		in;
	int		out;

	(void)ms;
	if (!tab)
		return (0);
	built = ft_split("cd echo env exit export pwd unset", ' ');
	is = ft_tabcmp(tab[0], built);
	if (is && state == 1 && ft_dup_redir(ms->pex, ms->pex->cmd) >= 0)
	{
		in = dup(STDIN_FILENO);
		out = dup(STDOUT_FILENO);
		ft_which_builtin(tab, ms);
		ft_dupcheck(in, STDIN_FILENO, ms->pex);
		ft_dupcheck(out, STDOUT_FILENO, ms->pex);
		close(in);
		close(out);
	}
	return (freesplit(built), is);
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
	m->out_red = 0;
	m->out_rok = 0;
	m->bhole = -1;
	m->in_rok = -1;
	m->cmd_i = 0;
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
