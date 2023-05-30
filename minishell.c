/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:24:52 by apayen            #+#    #+#             */
/*   Updated: 2023/05/30 14:35:53 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Boucle du shell.
// Lire une ligne > l'ajouter a l'historique > parser > executer.
static void	loop(struct s_shell *ms)
{
	while (1)
	{
		if (ms->line != NULL)
			free(ms->line);
		ms->line = readline(ms->prompt);
		if (ms->line != NULL && ms->line[0] != '\0')
			add_history(ms->line);
		(void)parser(ms);
	}
}

int	main(int argc, char **argv, char **envp)
{
	struct s_shell	ms;

	(void)argc;
	(void)argv;
	init(&ms, envp);
	loop(&ms);
	frees(&ms, 0);
	return (1);
}
