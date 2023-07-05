/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_minilib.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:07:57 by eewu              #+#    #+#             */
/*   Updated: 2023/06/22 11:47:25 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../header.h"


// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	if (!s)
// 		return (0);
// 	while (s[i])
// 		i++;
// 	return (i);
// }

// void	*ft_calloc(size_t nmemb, size_t size)
// {
// 	void	*tab;

// 	if (size != 0 && nmemb > SIZE_MAX / size)
// 		return (NULL);
// 	tab = malloc(size * nmemb);
// 	ft_bzero(tab, size * nmemb);
// 	return (tab);
// }

// char	*ft_strlcpy(char *dest, const char *src)
// {
// 	int	i;

// 	i = 0;
// 	while (src[i])
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	return (dest);
// }

// char	*ft_strlcat(char *dest, const char *src, int size)
// {
// 	int	i;

// 	i = 0;
// 	while (src[i])
// 	{
// 		dest[size + i] = src[i];
// 		i++;
// 	}
// 	return (dest);
// }

// char	*ft_join(char *path, char const *cmd)
// {
// 	size_t	len_path;
// 	size_t	len_buf;
// 	char	*join;

// 	len_path = 0;
// 	len_buf = 0;
// 	if (path)
// 		len_path = ft_strlen(path) + 1;
// 	if (cmd)
// 		len_buf = ft_strlen(cmd);
// 	join = ft_calloc(sizeof(char), (len_path + len_buf + 1));
// 	if (!join)
// 		return (join);
// 	if (path)
// 		ft_strlcpy(join, path);
// 	ft_strlcat(join, "/", (int)(len_path - 1));
// 	if (cmd)
// 		ft_strlcat(join, cmd, (int)len_path);
// 	return (join);
// }
