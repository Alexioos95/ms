/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:32:17 by apayen            #+#    #+#             */
/*   Updated: 2023/06/16 15:58:19 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// Actualise les char *path pwd et oldpwd.
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

// Actualise la ligne du env.
void	cdenv(struct s_shell *ms, char *tmp, char *str)
{
	char			*ret;
	struct s_lst	*node;

	node = ft_getenv(ms, str);
	if (node == NULL)
		return ;
	if (node->print == 2)
		node->print = 1;
	ret = ft_strjoinenv(str, '=', tmp);
	if (ret == NULL)
	{
		printf("minishell: malloc: %s\n", strerror(errno));
		free(tmp);
		frees(ms, 1);
	}
	if (node->flag == ALLOC)
		free(node->line);
	node->line = ret;
	node->flag = ALLOC;
	return ;
}

// Modifie le tmp pour avoir le symlink.
char	*actualizetmp(struct s_shell *ms, char *tmp, char *str)
{
	int				i;
	char			*new;
	struct s_lst	*node;

	node = ft_getenv(ms, str);
	if (node == NULL)
		return (tmp);
	i = 0;
	if (tmp[0] == '/')
		i++;
	while (tmp[i] != '\0' && tmp[i] != '/')
		i++;
	new = ft_substr(tmp, 0, i);
	free(tmp);
	if (new == NULL)
	{
		printf("minishell: malloc: %s\n", strerror(errno));
		frees(ms, 1);
	}
	tmp = ft_strjoin(&node->line[ft_strlen(str + 1)], new);
	if (tmp == NULL)
	{
		printf("minishell: malloc: %s\n", strerror(errno));
		frees(ms, 1);
	}
	free(new);
	return (tmp);
}

// Actualise le env de PWD et OLDPWD.
void	actualizeenv(struct s_shell *ms, char *tmp)
{
	cdenv(ms, tmp, "OLDPWD");
	free(tmp);
	tmp = getcwd(NULL, 0);
	if (ms->symlink == 1)
		tmp = actualizetmp(ms, tmp, "PWD=");
	if (tmp == NULL)
	{
		printf("minishell: getcwd: %s\n", strerror(errno));
		frees(ms, 1);
	}
	cdenv(ms, tmp, "PWD");
	free(tmp);
}
