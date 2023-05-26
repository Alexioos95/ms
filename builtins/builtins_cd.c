/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:32:17 by apayen            #+#    #+#             */
/*   Updated: 2023/05/26 13:29:34 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Actualise le env de PWD et OLDPWD.
int	ft_cdenv(struct s_shell *ms, char *tmp, char *str)
{
	char			*ret;
	struct s_lst	*node;

	if (tmp == NULL)
	{
		perror("minishell: cd: getcwd");
		frees(ms, 1);
	}
	node = ft_getenv(ms, str);
	if (node == NULL)
	{
		free(tmp);
		return (1);
	}
	ret = ft_strjoinenv(str, '=', tmp);
	if (ret == NULL)
	{
		printf("minishell: malloc: %s\n", strerror(errno));
		frees(ms, 1);
	}
	if (node->flag == NEW)
		free(node->line);
	node->line = ret;
	node->flag = NEW;
	return (0);
}

// Va au home.
int	ft_cdhome(struct s_shell *ms)
{
	struct s_lst	*node;

	node = ft_getenv(ms, "HOME");
	if (node == NULL)
	{
		printf("minishell: cd: HOME not set\n");
		return (1);
	}
	if (node->line != NULL && chdir(&node->line[5]) == -1)
	{
		printf("minishell: chdir: %s: %s\n", &node->line[5], strerror(errno));
		frees(ms, 1);
		return (1);
	}
	return (0);
}

// Change le chemin actuel, et actualise le env.
int	ft_cd(struct s_shell *ms, char *str)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (str == NULL)
	{
		if (ft_cdhome(ms) == 1)
			return ((void)free(tmp), 1);
	}
	else
	{
		if (chdir(str) == -1)
		{
			free(tmp);
			printf("minishell: cd: %s: %s\n", str, strerror(errno));
			frees(ms, 1);
		}
	}
	if (ft_cdenv(ms, tmp, "OLDPWD") == 1)
		return (1);
	free(tmp);
	tmp = getcwd(NULL, 0);
	if (ft_cdenv(ms, tmp, "PWD") == 1)
		return (1);
	free(tmp);
	return (0);
}
