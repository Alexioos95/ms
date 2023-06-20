/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:04:45 by apayen            #+#    #+#             */
/*   Updated: 2023/06/20 14:42:44 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// Init mes backups de PWD et OLDPWD en dehors du env.
void	ft_setpwd(struct s_shell *ms)
{
	struct s_lst	*tmp;

	tmp = ft_getenv(ms, "PWD");
	if (tmp != NULL)
	{
		ms->pwdpath = ft_strdup(tmp->line);
		if (ms->pwdpath == NULL)
			throwerror(ms, "malloc");
	}
	tmp = ft_getenv(ms, "OLDPWD");
	if (tmp != NULL)
	{
		ms->oldpwdpath = ft_strdup(tmp->line);
		if (ms->oldpwdpath == NULL)
		{
			printf("minishell: malloc: %s\n", strerror(errno));
			frees(ms, 1);
		}
	}
}

// Modifie le PWD du env, et le remplace avec le chemin actuel.
void	recreatepwd(struct s_shell *ms)
{
	char			*tmp;
	char			*tab[3];

	tmp = getcwd(NULL, 0);
	ms->tmp = ft_strjoin("PWD=", tmp);
	free(tmp);
	if (tmp == NULL || ms->tmp == NULL)
		throwerror(ms, "getcwd");
	tab[0] = "export";
	tab[1] = ms->tmp;
	tab[2] = NULL;
	ft_export(ms, tab);
	free(ms->tmp);
	ms->tmp = NULL;
}

// export PWD, OLDPWD pour creer un env en liste chainee.
void	createminienv(struct s_shell *ms)
{
	char			*tabcd[3];
	char			*tabexport[4];
	struct s_lst	*node;

	tabexport[0] = "export";
	tabexport[1] = "PWD=";
	tabexport[2] = "OLDPWD=";
	tabexport[3] = NULL;
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
		ft_lstadd_back(&ms->env, ft_lstnew(ms, envp[i]));
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
	ft_setpwd(ms);
}
