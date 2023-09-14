/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:41:32 by apayen            #+#    #+#             */
/*   Updated: 2023/09/14 10:37:54 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// Augmente la valeur de SHLVL de 1.
void	increaseshlvl(struct s_shell *ms)
{
	int				nb;
	char			*itoa;
	char			*result;
	struct s_lst	*node;
	char			*tab[3];

	tab[0] = "export";
	tab[1] = "SHLVL=2";
	tab[2] = NULL;
	node = ft_getenv(ms, "SHLVL");
	if (node == NULL)
		return ((void)ft_export(ms, tab));
	nb = ft_atoi(&node->line[6], &nb);
	if (nb < 1 || nb >= 2147483647)
		ft_export(ms, tab);
	itoa = ft_itoa(nb + 1);
	if (itoa == NULL)
		throwerror(ms, "malloc");
	result = ft_strjoinenv("SHLVL", '=', itoa);
	free(itoa);
	if (result == NULL)
		throwerror(ms, "malloc");
	free(node->line);
	node->line = result;
	ft_setpwd(ms);
}

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
