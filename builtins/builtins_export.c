/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:03:43 by apayen            #+#    #+#             */
/*   Updated: 2023/06/15 13:59:59 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	oldnode(struct s_lst *node, char *str)
{
	if (node->flag == ALLOC)
		free(node->line);
	node->line = ft_substr(str, 0, ft_strlen(str));
	if (node->line == NULL)
	{
		printf("minishell: malloc: %s\n", strerror(errno));
		frees(node->ms, 1);
	}
	node->flag = ALLOC;
	node->print = 1;
	return (0);
}

int	newnode(struct s_shell *ms, char *str)
{
	struct s_lst	*new;

	new = ft_lstnew(ms, NULL);
	if (new == NULL)
	{
		printf("minishell: malloc: %s\n", strerror(errno));
		frees(ms, 1);
	}
	new->line = ft_strdup(str);
	if (new->line == NULL)
	{
		printf("minishell: malloc: %s\n", strerror(errno));
		free(new);
		frees(ms, 1);
	}
	ft_lstadd_back(&ms->env, new);
	return (0);
}

int	actualizeenv_export(struct s_shell *ms, char *str, int equal)
{
	char			*new;
	struct s_lst	*node;

	new = ft_substr(str, 0, equal);
	if (new == NULL)
	{
		printf("minishell: malloc: %s\n", strerror(errno));
		frees(ms, 1);
	}
	node = ft_getenv(ms, new);
	free(new);
	if (node == NULL)
		newnode(ms, str);
	else
		oldnode(node, str);
	return (0);
}

// Ajoute la str au env.
int	ft_export(struct s_shell *ms, char **tab)
{
	int				i;
	int				isvalid;

	i = 1;
	while (tab[i] != NULL)
	{
		i++;
		isvalid = parsingexport(tab[i - 1]);
		if (isvalid == 0)
		{
			if (tab[i] == NULL)
				return (1);
			continue ;
		}
		actualizeenv_export(ms, tab[i - 1], isvalid);
	}
	return (0);
}
