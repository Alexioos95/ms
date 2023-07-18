/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:09:41 by eewu              #+#    #+#             */
/*   Updated: 2023/07/18 18:26:58 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"


void	ft_process(t_struct *m, char *out)
{
	int	i;

	i = ft_fdspipe(m);
	ft_fork(m);
	if (m->pids[m->count] == 0)
	{
		ft_openin(m, NULL);
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



void	ft_pipex(t_struct *m, char *out, char *in)
{
	int	i;

	i = 0;
	ft_mallocpipe(m);
	(void)in;
	ft_pipe(m);
	while (m->nb_cmd >= 1)
		ft_process(m, out);
	ft_closefds(m);
	while (waitpid(m->pids[i], &m->status, 0) > 0 && i < m->count - 1)
		i++;
}

int	ft_start(t_lexer *lexer, t_shell *ms)
{
	int			nb_cmd;
	char		**env;
	t_struct	*m;

	(void)lexer;
	env = listtotab(ms);
	m = NULL;
	nb_cmd = ft_nb_cmd(ms->lexer);
	m = ft_init(m, nb_cmd, env);
	if (!m)
		return (1);
	m->bhole = open("/dev/null", O_WRONLY);
	// ft_openin(m, in);
	// printf("Nombre de commade: %d\n", nb_cmd);
	find_cmd(m, ms);
	if (nb_cmd >= 2 && env)
		ft_pipex(m, NULL, NULL);
	// else if (nb_cmd == 1 && env)
	// 	ft_forkex(m, in, out);
	// print_allcmd(m);
	// ft_lstclearpipex(&m->head);
	// ft_free_process(m, errno);
	return (1);
}
