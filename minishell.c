/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:24:52 by apayen            #+#    #+#             */
/*   Updated: 2023/06/16 14:41:22 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	setsigaction(struct s_shell *ms, int b)
{
	if (b == 1)
	{
		if (sigaction(SIGINT, &ms->sigact[1], NULL) == -1 \
			|| sigaction(SIGQUIT, &ms->sigact[2], NULL) == -1
			|| sigaction(SIGTSTP, &ms->sigact[2], NULL) == -1)
		{
			printf("minishell: sigaction: %s\n", strerror(errno));
			frees(ms, 1);
		}
	}
	else
	{
		if (sigaction(SIGINT, &ms->sigact[0], NULL) == -1 \
			|| sigaction(SIGQUIT, &ms->sigact[0], NULL) == -1
			|| sigaction(SIGTSTP, &ms->sigact[0], NULL) == -1)
		{
			printf("minishell: sigaction: %s\n", strerror(errno));
			frees(ms, 1);
		}
	}
}

static void	nullonreadline(struct s_shell *ms)
{
	if (errno == ENOMEM)
	{
		printf("minishell: malloc: %s\n", strerror(errno));
		frees(ms, 1);
	}
	else
	{
		printf("exit\n");
		frees(ms, 0);
	}
}

// Boucle du shell.
// Lire une ligne > l'ajouter a l'historique > parser > executer.
_Noreturn static void	loop(struct s_shell *ms)
{
	while (1)
	{
		if (ms->line != NULL)
			free(ms->line);
		setsigaction(ms, 1);
		ms->line = readline("apayen&eewu@minishell$ ");
		if (ms->line == NULL)
			nullonreadline(ms);
		if (ms->line[0] != '\0')
			add_history(ms->line);
		setsigaction(ms, 0);
		parser(ms);
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
