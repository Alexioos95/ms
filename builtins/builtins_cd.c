/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:32:17 by apayen            #+#    #+#             */
/*   Updated: 2023/06/13 11:17:34 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	actualizepwd(struct s_shell *ms)
{
	struct s_lst	*tmp;

	tmp = ft_getenv(ms, "PWD");
	if (tmp != NULL && tmp->line != NULL)
	{
		free(ms->pwdpath);
		ms->pwdpath = ft_strdup(tmp->line);
		if (ms->pwdpath == NULL)
		{
			printf("minishell: malloc: %s\n", strerror(errno));
			frees(ms, 1);
		}
	}
	tmp = ft_getenv(ms, "OLDPWD");
	if (tmp != NULL && tmp->line != NULL)
	{
		free(ms->oldpwdpath);
		ms->oldpwdpath = ft_strdup(tmp->line);
		if (ms->oldpwdpath == NULL)
		{
			printf("minishell: malloc: %s\n", strerror(errno));
			frees(ms, 1);
		}
	}
}

// Actualise le env de PWD et OLDPWD.
void	cdenv(struct s_shell *ms, char *tmp, char *str)
{
	char			*ret;
	struct s_lst	*node;

	if (tmp == NULL)
	{
		printf("minishell: getcwd: %s\n", strerror(errno));
		frees(ms, 1);
	}
	node = ft_getenv(ms, str);
	if (node == NULL)
		return ;
	ret = ft_strjoinenv(str, '=', tmp);
	if (ret == NULL)
	{
		printf("minishell: malloc: %s\n", strerror(errno));
		frees(ms, 1);
	}
	if (node->flag == ALLOC)
		free(node->line);
	node->line = ret;
	node->flag = ALLOC;
	return ;
}

// Va au home.
int	cdhome(struct s_shell *ms)
{
	struct s_lst	*node;

	node = ft_getenv(ms, "HOME");
	if (node == NULL || node->print == 0 || node->line == NULL)
	{
		printf("minishell: cd: HOME not set\n");
		return (1);
	}
	if (chdir(&node->line[5]) == -1)
	{
		printf("minishell: chdir: %s: %s\n", &node->line[5], strerror(errno));
		if (errno == ENOMEM)
			frees(ms, 1);
		return (1);
	}
	return (0);
}

int	cdnothome(struct s_shell *ms, char *str)
{
	if (chdir(str) == -1)
	{
		printf("minishell: cd: %s: %s\n", str, strerror(errno));
		if (errno == ENOMEM)
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
		if (cdhome(ms) == 1)
			return ((void)free(tmp), 1);
	}
	else
	{
		if (cdnothome(ms, str) == 1)
			return ((void)free(tmp), 0);
	}
	cdenv(ms, tmp, "OLDPWD");
	free(tmp);
	tmp = getcwd(NULL, 0);
	cdenv(ms, tmp, "PWD");
	free(tmp);
	actualizepwd(ms);
	return (0);
}
