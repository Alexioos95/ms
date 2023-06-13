/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:53:38 by apayen            #+#    #+#             */
/*   Updated: 2023/06/13 11:17:34 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// Parser.
int	parser(struct s_shell *ms)
{
	if (ms->split != NULL)
	{
		freesplit(ms->split);
		ms->split = NULL;
	}
	if (ms->line == NULL)
		return (0);
	if (checkorphanbracket(ms->line) == 1 || checkorphanquote(ms->line) == 1)
		return (2);
	ms->split = ft_split(ms->line, ' ');			// Pour test, a delete.
	if (ft_strncmp(ms->line, "echo", 4) == 0)		// .
		ft_echo(ms->split[1], ms->split[2]);		// .
	else if (ft_strncmp(ms->line, "pwd", 3) == 0)	// .
		ft_pwd(ms);									// .
	else if (ft_strncmp(ms->line, "cd", 2) == 0)	// .
		ft_cd(ms, ms->split[1]);					// .
	else if (ft_strncmp(ms->line, "exit", 4) == 0)	// .
		ft_exit(ms, ms->split[1]);					// .
	else if (ft_strncmp(ms->line, "env", 3) == 0)	// .
		ft_env(ms, ms->split[1]);					// .
	else if (ft_strncmp(ms->line, "unset", 5) == 0)	// .
		ft_unset(ms, ms->split[1], ms->split[2]);	// .
	else if (ft_strncmp(ms->line, "export", 6) == 0)// .
		ft_export(ms, ms->split[1]);				// -----------------------
	return (0);
}
