/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:03:42 by eewu              #+#    #+#             */
/*   Updated: 2023/06/20 16:58:21 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	ft_openin(t_struct *m, char *in)
{
	m->in[0] = open(in, O_RDONLY);
	if (m->in[0] >= 0)
		m->in_rok = 0;
	else
		m->in_rok = errno;
}

void	ft_openout(t_struct *m, char *out)
{
	if (access(out, W_OK) == 0 && m->out == -1)
		m->out = open(out, O_WRONLY | O_TRUNC);
	else if (access(out, F_OK) != 0)
		m->out = open(out, O_WRONLY | O_CREAT, 0644);
	else
		m->out_rok = errno;
}

void	ft_dupcheck(int fd, int stdfd, t_struct *m)
{
	if (dup2(fd, stdfd) == -1)
		ft_free_process(m, errno);
}

int	ft_error(char *ft, char *error, int pid, t_struct *m)
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
			ft_printf("zsh: permission denied: %s\n", ft);
		else
			ft_printf("zsh: %s: %s\n", error, ft);
		return (0);
	}
}
