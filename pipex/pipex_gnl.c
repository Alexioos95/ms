/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_gnl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 12:01:20 by eewu              #+#    #+#             */
/*   Updated: 2023/06/22 11:47:25 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../header.h"


// void	ft_clear_buf(char *buf, char *bsn_i, int after)
// {
// 	int	i;

// 	i = 0;
// 	if (after == -1)
// 	{
// 		while (bsn_i[i])
// 		{
// 			buf[i] = bsn_i[i];
// 			i++;
// 		}
// 		while (buf[i])
// 			buf[i++] = 0;
// 	}
// 	else
// 	{
// 		while (buf[after])
// 			buf[after++] = 0;
// 	}
// }

// int	ft_backsn(char *buf)
// {
// 	int	i;

// 	i = 0;
// 	while (buf[i])
// 	{
// 		if (buf[i] == '\n')
// 			return (i + 1);
// 		i++;
// 	}
// 	return (-1);
// }

// char	*ft_gnljoin(char *stash, char *buf, int backsn_index, int size)
// {
// 	int		i;
// 	int		j;
// 	size_t	len_stash;
// 	char	*join;

// 	i = 0;
// 	j = 0;
// 	len_stash = 0;
// 	if (stash)
// 		len_stash = ft_strlen(stash);
// 	if (backsn_index != -1)
// 		join = ft_calloc(sizeof(char), (len_stash + (size_t)backsn_index + 1));
// 	else
// 		join = ft_calloc(sizeof(char), (len_stash + ft_strlen(buf) + 1));
// 	if (!join)
// 		return (join);
// 	while (stash && stash[i])
// 	{
// 		join[i] = stash[i];
// 		i++;
// 	}
// 	while (j < size && buf[j] && (j < backsn_index || backsn_index == -1))
// 		join[i++] = buf[j++];
// 	free (stash);
// 	return (join);
// }

// char	*ft_read(int start, char *stash, int fd, char *buf)
// {
// 	int	r;

// 	r = 1;
// 	while (start == -1)
// 	{
// 		r = (int)read(fd, buf, BUFFER_SIZE);
// 		if (r == -1)
// 			return (0);
// 		if (r == 0)
// 			break ;
// 		if (r != BUFFER_SIZE)
// 			ft_clear_buf(buf, &buf[r], r);
// 		start = ft_backsn(buf);
// 		stash = ft_gnljoin(stash, buf, start, r);
// 	}
// 	if ((!stash) && r == 0)
// 		return (0);
// 	return (stash);
// }

// char	*get_next_line(int fd)
// {
// 	int			start;
// 	int			end;
// 	char		*stash;
// 	static char	buf[BUFFER_SIZE + 1];

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (0);
// 	start = ft_backsn(buf);
// 	stash = 0;
// 	if (start != -1)
// 	{
// 		if (buf[start])
// 		{
// 			end = ft_backsn(&buf[start]);
// 			stash = ft_gnljoin(0, &buf[start], end, (BUFFER_SIZE - start));
// 			ft_clear_buf(buf, &buf[start], -1);
// 			start = end;
// 		}
// 		else
// 			start = -1;
// 	}
// 	return (ft_read(start, stash, fd, buf));
// }
