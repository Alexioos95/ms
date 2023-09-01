/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:04:45 by apayen            #+#    #+#             */
/*   Updated: 2023/09/01 14:07:38 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// Modifie le PWD du env, et le remplace avec le chemin actuel.
void	recreatepwd(struct s_shell *ms)
{
	char			*tmp;
	char			*tab[3];

	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
	{
		if (errno == ENOMEM)
			throwerror(ms, "malloc");
		printf("shell-init: error retrieving current directory: getcwd: ");
		printf("cannot access parent directories: %s\n", strerror(errno));
	}
	else
	{
		ms->tmp = ft_strjoin("PWD=", tmp);
		free(tmp);
		if (ms->tmp == NULL)
			throwerror(ms, "malloc");
		tab[0] = "export";
		tab[1] = ms->tmp;
		tab[2] = NULL;
		ft_export(ms, tab);
	}
	free(ms->tmp);
	ms->tmp = NULL;
}

// export PWD, OLDPWD pour creer un env en liste chainee.
void	createminienv(struct s_shell *ms)
{
	char			*tabcd[3];
	char			*tabexport[5];
	struct s_lst	*node;

	tabexport[0] = "export";
	tabexport[1] = "PWD=";
	tabexport[2] = "OLDPWD=";
	tabexport[3] = "SHLVL=2";
	tabexport[4] = NULL;
	ft_export(ms, tabexport);
	tabcd[0] = "cd";
	tabcd[1] = "./";
	tabcd[2] = NULL;
	ft_cd(ms, tabcd);
	node = ft_getenv(ms, "OLDPWD");
	node->print = 2;
}

// Creer la liste chainee d'env a partir du envp,
// et en creer un mini s'il n'existe pas avant.
void	ft_setenv(struct s_shell *ms, char **envp)
{
	int				i;
	struct s_lst	*tmp;

	i = 0;
	while (envp != NULL && envp[i] != NULL)
	{
		ft_lstadd_back(ms, &ms->env, ft_lstnew(ms, envp[i]));
		i++;
	}
	tmp = ms->env;
	while (tmp != NULL)
	{
		tmp->line = ft_strdup(tmp->line);
		if (tmp->line == NULL)
		{
			printf("minishell: malloc: %s\n", strerror(errno));
			frees(ms, 1);
		}
		tmp = tmp->next;
	}
	if (envp == NULL || envp[0] == NULL)
		createminienv(ms);
	else
		recreatepwd(ms);
	increaseshlvl(ms);
}
