/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:32:17 by apayen            #+#    #+#             */
/*   Updated: 2023/06/21 09:41:07 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// Actualise les char * pwd et oldpwd paths.
void	ft_echo_actualizepwd(struct s_shell *ms)
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
void	ft_echo_changeenv(struct s_shell *ms, char *tmp, char *str)
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

// Modifie le tmp pour avoir le symlink.
char	*ft_cd_symlink(struct s_shell *ms, char *tmp, char *str)
{
	int				i;
	char			*new;
	struct s_lst	*node;

	node = ft_getenv(ms, str);
	if (node == NULL || tmp == NULL)
		return (tmp);
	i = 0;
	if (tmp[0] == '/')
		i++;
	while (tmp[i] != '\0' && tmp[i] != '/')
		i++;
	new = ft_substr(tmp, 0, i);
	free(tmp);
	if (new == NULL)
		throwerror(ms, "malloc");
	tmp = ft_strjoin(&node->line[ft_strlen(str) + 1], new);
	if (tmp == NULL)
		throwerror(ms, "malloc");
	free(new);
	return (tmp);
}

// Actualise le env de PWD et OLDPWD.
void	ft_echo_actualizeenv(struct s_shell *ms, char *tmp)
{
	ft_echo_changeenv(ms, tmp, "OLDPWD");
	free(tmp);
	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
		throwerror(ms, "getcwd");
	if (ms->symlink == 1)
		tmp = ft_cd_symlink(ms, tmp, "PWD");
	ft_echo_changeenv(ms, tmp, "PWD");
	free(tmp);
}
