/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:24:52 by apayen            #+#    #+#             */
/*   Updated: 2023/08/14 11:32:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// Realise des sigactions different selon le int donnee.
// Si b == 1, les signaux sont handled pour ne pas casser la boucle du shell.
// Si b == 2, Sigint est handled pour ne pas changer de ligne.
// Si b == 3, Sigint est handled pour fermer le stdin.
// Dans les autres cas, les signaux agissent par defaut.
void	setsigaction(struct s_shell *ms, int b)
{
	if (b == 1 && (sigaction(SIGINT, &ms->sigact[1], NULL) == -1 \
			|| sigaction(SIGQUIT, &ms->sigact[4], NULL) == -1 \
			|| sigaction(SIGTSTP, &ms->sigact[4], NULL) == -1))
			throwerror(ms, "sigaction");
	else if (b == 2 && sigaction(SIGINT, &ms->sigact[2], NULL) == -1)
			throwerror(ms, "sigaction");
	else if (b == 3 && sigaction(SIGINT, &ms->sigact[3], NULL) == -1)
			throwerror(ms, "sigaction");
	else if (b == 0 && (sigaction(SIGINT, &ms->sigact[0], NULL) == -1 \
			|| sigaction(SIGQUIT, &ms->sigact[0], NULL) == -1 \
			|| sigaction(SIGTSTP, &ms->sigact[0], NULL) == -1))
			throwerror(ms, "sigaction");
}

// Regarde pourquoi la line est a NULL, et agit en consequence.
void	nullonreadline(struct s_shell *ms)
{
	if (errno == ENOMEM)
		throwerror(ms, "readline");
	else
	{
		printf("exit\n");
		frees(ms, ms->status);
	}
}

// Boucle du shell.
// Lire une ligne > parser > executer.
void	loop(struct s_shell *ms)
{
	while (1)
	{
		setsigaction(ms, 1);
		if (ms->line != NULL)
			free(ms->line);
		ms->line = readline("apayen&eewu@minishell$ ");
		if (ms->line == NULL)
			nullonreadline(ms);
		if (ms->line[0] != '\0')
			add_history(ms->line);
		// setsigaction(ms, 2);
		ms->status = parser(ms);
	}
}

int	main(int argc, char **argv, char **envp)
{
	struct s_shell	ms;

	(void)argc;
	(void)argv;
	init(&ms, envp);
	loop(&ms);
}
