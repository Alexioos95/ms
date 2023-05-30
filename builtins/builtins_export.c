/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:03:43 by apayen            #+#    #+#             */
/*   Updated: 2023/05/30 15:18:21 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	oldnode(struct s_lst *node, char *str)
{
	if (node->flag == ALLOC)
		free(node->line);
	node->line = ft_substr(str, 0, ft_strlen(str));
	if (node->line == NULL)
	{
		printf("minishell: malloc: %s\n", strerror(errno));
		return (1);
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
		return (1);
	}
	new->line = ft_strdup(str);
	if (new->line == NULL)
	{
		printf("minishell: malloc: %s\n", strerror(errno));
		free(new);
		return (1);
	}
	ft_lstadd_back(&ms->env, new);
	return (0);
}

int	searchequal(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (1);
	while (str[i] != '\0' && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (-1);
	return (i);
}

// Ajoute la str au env.
int	ft_export(struct s_shell *ms, char *str)
{
	int				equal;
	char			*new;
	struct s_lst	*node;

	equal = searchequal(str);
	if (equal < 1)
		return (1);
	new = ft_substr(str, 0, equal);
	if (new == NULL)
	{
		printf("minishell: malloc: %s\n", strerror(errno));
		frees(ms, 1);
	}
	node = ft_getenv(ms, new);
	if (node == NULL)
	{
		if (newnode(ms, str) == 1)
			return ((void)free(new), frees(ms, 1), 1);
	}
	else
	{
		if (oldnode(node, str) == 1)
			return ((void)free(new), 1);
	}
	return ((void)free(new), 0);
}
