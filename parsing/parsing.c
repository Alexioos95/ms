/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:53:38 by apayen            #+#    #+#             */
/*   Updated: 2023/06/15 13:27:00 by apayen           ###   ########.fr       */
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
	ms->split = ft_splitline(ms->line, ' ');
	if (ms->split[0] != NULL && ft_strncmp(ms->split[0], "echo", 5) == 0)
		ft_echo(ms->split);
	else if (ms->split[0] != NULL && ft_strncmp(ms->split[0], "pwd", 4) == 0)
		ft_pwd(ms);
	else if (ms->split[0] != NULL && ft_strncmp(ms->split[0], "cd", 3) == 0)
		ft_cd(ms, ms->split);
	else if (ms->split[0] != NULL && ft_strncmp(ms->split[0], "exit", 5) == 0)
		ft_exit(ms, ms->split);
	else if (ms->split[0] != NULL && ft_strncmp(ms->split[0], "env", 4) == 0)
		ft_env(ms, ms->split);
	else if (ms->split[0] != NULL && ft_strncmp(ms->split[0], "unset", 6) == 0)
		ft_unset(ms, ms->split);
	else if (ms->split[0] != NULL && ft_strncmp(ms->split[0], "export", 7) == 0)
		ft_export(ms, ms->split);
	return (0);
}
