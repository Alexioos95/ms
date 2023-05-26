/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:05:22 by apayen            #+#    #+#             */
/*   Updated: 2023/05/26 13:11:46 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

struct s_lst	*ft_getenv(struct s_shell *ms, char *str)
{
	struct s_lst	*tmp;

	tmp = ms->env;
	while (tmp != NULL && tmp->line != NULL)
	{
		if (ft_strnstr(tmp->line, str, 0) != NULL && tmp->print == 1)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	char	*strmalloc;

	i = 0;
	if (start >= ft_strlen(s))
	{
		strmalloc = malloc(sizeof(char) * 1);
		strmalloc[0] = '\0';
		return (strmalloc);
	}
	if (len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	strmalloc = malloc(sizeof(char) * len + 1);
	if (strmalloc == NULL)
		return (NULL);
	while (s[i] != '\0' && i < len)
	{
		strmalloc[i] = s[start];
		i++;
		start++;
	}
	strmalloc[i] = '\0';
	return (strmalloc);
}

char	*ft_strjoinenv(char *s1, char c, char *s2)
{
	int		i;
	int		j;
	char	*strmalloc;

	i = 0;
	j = 0;
	strmalloc = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 2);
	if (strmalloc == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		strmalloc[i] = s1[i];
		i++;
	}
	if (c != '\0')
		strmalloc[i] = c;
	while (s2[j] != '\0')
	{
		strmalloc[i + j + 1] = s2[j];
		j++;
	}
	strmalloc[i + j + 1] = '\0';
	return (strmalloc);
}

char	*ft_strnstr(char *big, char *little, int equal)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (big == NULL || little == NULL)
		return (NULL);
	if (little[j] == '\0')
		return ((char *)big);
	while (big[i] != '\0')
	{
		j = 0;
		while (big[i + j] == little[j] && little[j] != '\0')
		{
			j++;
			if (little[j] == '\0' && i == 0 && big[i + j] == '=')
				return ((char *)&big[i + equal]);
		}
		i++;
	}
	return (NULL);
}
