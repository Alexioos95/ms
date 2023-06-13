/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:18:09 by apayen            #+#    #+#             */
/*   Updated: 2023/06/13 11:17:34 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*strmalloc;

	i = 0;
	j = 0;
	strmalloc = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (strmalloc == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		strmalloc[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		strmalloc[i + j] = s2[j];
		j++;
	}
	strmalloc[i + j] = '\0';
	return (strmalloc);
}

char	*ft_strdup(char *s)
{
	int		i;
	size_t	len;
	char	*s1;

	i = 0;
	len = ft_strlen(s);
	s1 = malloc(sizeof(char) * (len + 1));
	if (s1 == NULL)
	{
		return (NULL);
	}
	while (s[i] != '\0')
	{
		s1[i] = s[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

int	ft_atoi(char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == 32 || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * result);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s3;
	unsigned char	*s4;

	s3 = (unsigned char *)s1;
	s4 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (s3[i] != '\0' && s4[i] != '\0' && s3[i] == s4[i] && i < n - 1)
		i++;
	return (s3[i] - s4[i]);
}
