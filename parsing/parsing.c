/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:53:38 by apayen            #+#    #+#             */
/*   Updated: 2023/06/21 10:45:57 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	ft_start(int nb_cmd, t_struct *pars_lst, char **ev)
{
	char		*in;
	char		*out;
	t_struct	*m;

	m = NULL;
	m = ft_init(m, nb_cmd, av, ev);
	if (!m)
		return (1);
	m->bhole = open("/dev/null", O_WRONLY);
	ft_openin(m, in);
	m->hdoc = ft_heredoc(in);
	if (nb_cmd >= 2 && ev)
		ft_pipex(m, out, in);
	else if (nb_cmd == 1 && ev)
		ft_forkex(m, in, out);
	ft_free_process(m, errno);
	return (1);
}

// Parser.
int	parser(struct s_shell *ms)
{
	int	nb_cmd;

	if (ms->split != NULL)
	{
		freesplit(ms->split);
		ms->split = NULL;
	}
	if (ms->line == NULL)
		return (0);
	if (checkorphanbracket(ms->line) == 1 || checkorphanquote(ms->line) == 1)
		return (2);
	ms->pex->cmd = split_pipe(ms->line);
	nb_cmd = ft_lstsize(ms->pex->cmd);
	ft_start(nb_cmd, ms->pex->cmd, ms->env);
	return (0);
}


	// if (ft_strncmp(ms->line, "echo", 4) == 0)		// .
	// 	ft_echo(ms->split[1], ms->split[2]);		// .
	// else if (ft_strncmp(ms->line, "pwd", 3) == 0)	// .
	// 	ft_pwd(ms);									// .
	// else if (ft_strncmp(ms->line, "cd", 2) == 0)	// .
	// 	ft_cd(ms, ms->split[1]);					// .
	// else if (ft_strncmp(ms->line, "exit", 4) == 0)	// .
	// 	ft_exit(ms, ms->split[1]);					// .
	// else if (ft_strncmp(ms->line, "env", 3) == 0)	// .
	// 	ft_env(ms, ms->split[1]);					// .
	// else if (ft_strncmp(ms->line, "unset", 5) == 0)	// .
	// 	ft_unset(ms, ms->split[1], ms->split[2]);	// .
	// else if (ft_strncmp(ms->line, "export", 6) == 0)// .
	// 	ft_export(ms, ms->split[1]);				// -----------------------