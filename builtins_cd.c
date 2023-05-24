/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:32:17 by apayen            #+#    #+#             */
/*   Updated: 2023/05/24 16:48:51 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Actualise le env de PWD et OLDPWD.
int	ft_cdenv(struct s_shell *ms, char *pwd, char *str)
{
	char *ret;

	if (pwd == NULL)
	{
		perror("minishell: cd: getcwd");
		return (1);
	}
	while (ms->env != NULL && ft_strnstr(ms->env->line, str, 0) == NULL)
		ms->env = ms->env->next;
	if (ms->env == NULL)
	{
		ms->env = ms->lsthead;
		return (1);
	}
	ret = ft_strjoin(str, pwd);
	if (ret == NULL)
	{
		printf("minishell: malloc: %s\n", strerror(errno));
		return (1);
	}
	ms->env->line = ret;
	ms->env->flag = NEW;
	ms->env = ms->lsthead;
	return (0);
}

// Va au home.
int	ft_cdhome(struct s_shell *ms, char *pwd)
{
	while (ms->env != NULL && ft_strnstr(ms->env->line, "HOME", 0) == NULL)
		ms->env = ms->env->next;
	if (ms->env == NULL)
	{
		ms->env = ms->lsthead;
		printf("minishell: cd: HOME not set\n");
		free(pwd);
		return (1);
	}
	if (chdir(&ms->env->line[5]) == -1)
	{
		free(pwd);
		printf("minishell: chdir: %s: %s\n", &ms->env->line[5], strerror(errno));
		return (1);
	}
	return (0);
}

// Change le chemin actuel, et actualise le env.
// Si on ne donne aucun chemin, il faut aller au home.
int ft_cd(struct s_shell *ms, char *str)
{
	char	*tmp;

	tmp = NULL;
	tmp = getcwd(tmp, 0);
	if (str == NULL)
	{
		if (ft_cdhome(ms, tmp) == 1)
			return (1);
	}
	else
	{
		if (chdir(str) == -1)
		{
			free(tmp);
			printf("minishell: cd: %s: %s\n", str, strerror(errno));
			return (0);
		}
	}
	if (ft_cdenv(ms, tmp, "OLDPWD") == 1)
		return (1);
	tmp = NULL;
	tmp = getcwd(tmp, 0);
	if (ft_cdenv(ms, tmp, "PWD") == 1)
		return (1);
	return (0);
}

// check chmod dir.
