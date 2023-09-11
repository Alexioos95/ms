/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_1-5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:25:41 by eewu              #+#    #+#             */
/*   Updated: 2023/09/11 16:20:22 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	ft_errors_1_5(int error, char *str)
{
	if (error == 0)
		printf ("minishell: syntax error near unexpected token `%s'\n", str);
	else if (error == 1)
		printf ("%s\n", str);
	else if (error == 2)
		printf ("%s\n", str);
	else if (error == 3)
		printf ("%s\n", str);
	else
		printf ("%s\n", str);
	return (-2);
}

void	ft_exitchild(t_pipex *m, int status_code)
{
	t_shell	*ms;

	ms = m->ms;
	ft_closefds(m);
	ft_freefds(m);
	ft_closeoutin(m);
	ft_lstclearpipex(&m->headplus, ms->lexer);
	free(ms->tabenv);
	free (m);
	// ft_lexerclear(m->ms, ms->lexer);
	frees(ms, status_code);
}

void	ft_error(char *file, char *error, int pid, t_pipex *m)
{
	ft_dupcheck(2, 1, m);
	printf("minishell: %s: %s\n", file, error);
	// printf("in: %d\nout: %d\ncmd: %d\n", m->in_rok, m->out_rok, m->cmd->i);
	if ((m->in_rok > 0 || m->out_rok > 0) && pid == 0)
		ft_exitchild(m, 1);
	else if ((m->cmd->i == 13) && pid == 0)
		ft_exitchild(m, 126);
	else if ((m->cmd->i > 0) && pid == 0)
		ft_exitchild(m, 127);
}
