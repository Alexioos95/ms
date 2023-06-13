/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:19:13 by apayen            #+#    #+#             */
/*   Updated: 2023/06/13 12:17:29 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	ft_countstrline(char *s, char c)
{
	int		i;
	char	d;
	int		count;

	i = 0;
	count = 0;
	while (s[i] != '\0' && s[i] == c)
		i++;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] != c)
		{
			if (s[i] == '\'' || s[i] == '"')
			{
				d = s[i++];
				while (s[i] != '\0' && s[i] != d)
					i++;
			}
			i++;
		}
		count++;
		while (s[i] != '\0' && s[i] == c)
			i++;
	}
	return (count);
}

static	int	movepointer(char *s, char c, int j)
{
	char	d;

	while (s[j] != '\0' && s[j] != c)
	{
		while (s[j] != '\0' && s[j] != c)
		{
			if (s[j] == '\'' || s[j] == '"')
			{
				d = s[j];
				j++;
				while (s[j] != '\0' && s[j] != d)
					j++;
			}
			j++;
		}
	}
	while (s[j] != '\0' && s[j] == c)
		j++;
	return (j);
}

static char	*ft_strdupsplitline(char *s, char c, int j)
{
	int		i;
	int		len;
	char	*s1;

	i = 0;
	len = j;
	len = movepointer(s, c, len);
	len = len - j;
	s1 = malloc(sizeof(char) * ((unsigned int)len + 1));
	if (s1 == NULL)
		return (NULL);
	while (i < len)
	{
		s1[i] = s[j];
		i++;
		j++;
	}
	s1[i] = '\0';
	return (s1);
}

static	char	*ft_loopline(char *s, char c, int i)
{
	char	*str;
	int		j;
	int		loop;

	j = 0;
	loop = 0;
	while (s[j] != '\0' && s[j] == c)
		j++;
	while (loop < i)
	{
		j = movepointer(s, c, j);
		loop++;
	}
	str = ft_strdupsplitline(s, c, j);
	if (str == NULL)
		return (NULL);
	return (str);
}

char	**ft_splitline(char *s, char c)
{
	int		i;
	int		len;
	char	**strmalloc;

	i = 0;
	if (s == NULL)
		return (NULL);
	len = ft_countstrline(s, c);
	strmalloc = malloc(sizeof(char *) * ((unsigned int)len + 1));
	if (strmalloc == NULL)
		return (NULL);
	while (i < len)
	{
		strmalloc[i] = ft_loopline(s, c, i);
		if (strmalloc[i] == NULL)
			return ((void)freesplit(strmalloc), NULL);
		i++;
	}
	strmalloc[i] = NULL;
	return (strmalloc);
}
