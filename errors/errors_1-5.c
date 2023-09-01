/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_1-5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:25:41 by eewu              #+#    #+#             */
/*   Updated: 2023/08/29 17:30:01 by eewu             ###   ########.fr       */
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
	ft_lstclearpipex(&m->head);
	free(ms->tabenv);
	free (m);
	ft_lexerclear(ms->lexer);
	frees(ms, status_code);
}

void	ft_error(char *file, char *error, int pid, t_pipex *m)
{
	if (pid == 0)
	{
		if (m->cmd->i == 13)
			ft_exitchild(m, 126);
			// exit(126);
		else
			ft_exitchild(m, 127);
			// exit(127);
	}
	else
	{
		if (m->cmd->i == 13)
			printf("bash: permission denied: %s\n", file);
		else
			printf("bash: %s: %s\n", file, error);
	}
	// ft_free_process(m, errno);
}


