/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:32:17 by apayen            #+#    #+#             */
/*   Updated: 2023/08/09 13:30:55 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// Actualise les char * pwd et oldpwd paths.
void	ft_cd_actualizepwd(struct s_shell *ms)
{
	struct s_lst	*tmp;

	tmp = ft_getenv(ms, "PWD");
	if (tmp != NULL && tmp->line != NULL)
	{
		free(ms->pwdpath);
		ms->pwdpath = ft_strdup(tmp->line);
		if (ms->pwdpath == NULL)
			throwerror(ms, "malloc");
	}
	tmp = ft_getenv(ms, "OLDPWD");
	if (tmp != NULL && tmp->line != NULL)
	{
		free(ms->oldpwdpath);
		ms->oldpwdpath = ft_strdup(tmp->line);
		if (ms->oldpwdpath == NULL)
			throwerror(ms, "malloc");
	}
}

// Actualise la ligne du env.
void	ft_cd_changeenv(struct s_shell *ms, char *tmp, char *str)
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
		free(tmp);
		throwerror(ms, "malloc");
	}
	free(node->line);
	node->line = ret;
}

// Actualise le env de PWD et OLDPWD.
void	ft_cd_actualizeenv(struct s_shell *ms, char *tmp)
{
	ft_cd_changeenv(ms, tmp, "OLDPWD");
	free(tmp);
	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
		throwerror(ms, "getcwd");
	ft_cd_changeenv(ms, tmp, "PWD");
	free(tmp);
}

// Protecte getcwd en cas de fail.
char	*ft_cd_proteccwd(struct s_shell *ms, char **tab, char *tmp)
{
	if (errno == ENOMEM)
		throwerror(ms, "cd");
	if (tab[1] != NULL && ft_strncmp(tab[1], "-", 2) != 0)
	{
		printf("minishell: cd: %s: %s\n", tab[1], strerror(errno));
		return (NULL);
	}
	tmp = malloc(sizeof(char) * 1);
	if (errno == ENOMEM)
		throwerror(ms, "malloc");
	tmp[0] = '\0';
	return (tmp);
}
