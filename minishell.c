/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:24:52 by apayen            #+#    #+#             */
/*   Updated: 2023/06/01 11:36:38 by apayen           ###   ########.fr       */
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
		if (sigaction(SIGINT, &ms->sigact[0], NULL) == -1 \
			|| sigaction(SIGQUIT, &ms->sigact[1], NULL) == -1)
		{
			printf("minishell: sigaction: %s\n", strerror(errno));
			frees(ms, 1);
		}
		ms->line = readline(ms->prompt);
		if (ms->line == NULL)
		{
			printf("exit\n");
			frees(ms, 0);
		}
		if (ms->line[0] != '\0')
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
