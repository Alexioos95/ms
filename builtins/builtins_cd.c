/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:32:17 by apayen            #+#    #+#             */
/*   Updated: 2023/06/14 15:55:45 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// Va au home.
int	cdhome(struct s_shell *ms, char *tmp)
{
	struct s_lst	*node;

	node = ft_getenv(ms, "HOME");
	if (node == NULL || node->print == 0 || node->line == NULL)
	{
		free(tmp);
		printf("minishell: cd: HOME not set\n");
		return (1);
	}
	if (chdir(&node->line[5]) == -1)
	{
		free(tmp);
		if (errno == ENOMEM)
		{
			printf("minishell: chdir: %s: %s\n", &node->line[5], strerror(errno));
			frees(ms, 1);
		}
		printf("minishell: chdir: %s: %s\n", &node->line[5], strerror(errno));
		return (1);
	}
	return (0);
}

// Va au OLDPWD.
int	cdoldpwd(struct s_shell *ms, char *tmp)
{
	if (ms->oldpwdpath == NULL)
	{
		free(tmp);
		printf("minishell: cd: OLDPWD not set\n");
		return (1);
	}
	if (chdir(&ms->oldpwdpath[7]) == -1)
	{
		free(tmp);
		if (errno == ENOMEM)
		{
			printf("minishell: cd: %s: %s\n", &ms->oldpwdpath[7], strerror(errno));
			frees(ms, 1);
		}
		printf("minishell: cd: %s: %s\n", &ms->oldpwdpath[7], strerror(errno));
		return (1);
	}
	printf("%s\n", &ms->oldpwdpath[7]);
	return (0);
}

int	cdnothome(struct s_shell *ms, char *str, char *tmp)
{
	if (chdir(str) == -1)
	{
		free(tmp);
		if (errno == ENOMEM)
		{
			printf("minishell: cd: %s: %s\n", str, strerror(errno));
			frees(ms, 1);
		}
		printf("minishell: cd: %s: %s\n", str, strerror(errno));
		return (1);
	}
	return (0);
}

// Change le chemin actuel, et actualise le env.
int	ft_cd(struct s_shell *ms, char **tab)
{
	char	*tmp;

	if (tab[1] != NULL && tab[2] != NULL)
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
	{
		printf("minishell: getcwd: %s\n", strerror(errno));
		frees(ms, 1);
	}
	if (tab[1] == NULL && cdhome(ms, tmp) == 1)
		return (1);
	else if (tab[1] != NULL && ft_strncmp(tab[1], "-", 2) == 0 \
		&& cdoldpwd(ms, tmp) == 1)
		return (1);
	else if (tab[1] != NULL && ft_strncmp(tab[1], "-", 2) != 0 \
		&& cdnothome(ms, tab[1], tmp) == 1)
		return (1);
	actualizeenv(ms, tmp);
	actualizepwd(ms);
	return (0);
}
