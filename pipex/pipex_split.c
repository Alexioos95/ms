/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:16:12 by eewu              #+#    #+#             */
/*   Updated: 2023/08/02 11:10:11 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../header.h"

// static int	ft_nbword(char *s, char c)
// {
// 	int	i;
// 	int	nb;

// 	nb = 0;
// 	i = 0;
// 	while (s[i] && s[i] == c)
// 		i++;
// 	while (s[i])
// 	{
// 		while (s[i] && !(s[i] == c))
// 			i++;
// 		nb += 1;
// 		while (s[i] && s[i] == c)
// 			i++;
// 	}
// 	return (nb);
// }

// static int	ft_sizeword(char *s, char c, int index)
// {
// 	int	size_word;

// 	size_word = 0;
// 	while (s[index] && s[index] == c)
// 		index++;
// 	while (s[index + size_word] && (s[index + size_word] != c))
// 		size_word++;
// 	return (size_word);
// }

// static char	**ft_freeture(char **split)
// {
// 	int	i;

// 	i = 0;
// 	while (split && split[i])
// 	{
// 		free(split[i]);
// 		i++;
// 	}
// 	free(split);
// 	return (0);
// }

// static char	**ft_tab(int i, char *s, char c, char **split)
// {
// 	int		j;
// 	int		k;

// 	k = 0;
// 	while (s[i] && k < ft_nbword(s, c))
// 	{
// 		while (s[i] && s[i] == c)
// 			i++;
// 		j = 0;
// 		split[k] = ft_calloc(sizeof(char), (size_t)(ft_sizeword(s, c, i) + 1));
// 		if (!split[k])
// 			return (ft_freeture(split));
// 		while (s[i] && s[i] != c)
// 			split[k][j++] = s[i++];
// 		split[k][j] = 0;
// 		k++;
// 	}
// 	return (split);
// }

// char	**ft_split(char *s, char c)
// {
// 	int		i;
// 	int		nb_word;
// 	char	**split;

// 	i = 0;
// 	if (s == NULL)
// 		return (0);
// 	nb_word = ft_nbword((char *)s, c);
// 	split = ft_calloc(sizeof(char *), (size_t)(nb_word + 1));
// 	if (!split)
// 		return (0);
// 	split[nb_word] = 0;
// 	if (ft_tab(i, (char *)s, c, split))
// 		return (split);
// 	return (0);
// }
