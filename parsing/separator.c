/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:47:00 by eewu              #+#    #+#             */
/*   Updated: 2023/06/20 16:30:43 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_cmd	*split_pipe(char *str)
{
	t_cmd	*raw_cmd;
	char	**split_pipe;
	char	**split_cmd;
	int		nb_pipe;
	int		i;
	int		y;

	i = 0;
	split_pipe = ft_split(str, '|');
	y = 0;
	while (split_pipe[y])
		printf("Split_pipe: %s\n", split_pipe[y++]);
	nb_pipe = ft_tablen(split_pipe) - 1;
	printf("Nb_pipe: %d\n", nb_pipe);
	while (split_pipe[i])
	{
		split_cmd = ft_split(split_pipe[i++], ' ');
		y = 0;
		while (split_cmd[y])
			printf("cmd?: %s\n", split_cmd[y++]);
		raw_cmd = NULL;
		ft_lstadd_back_cmd(&raw_cmd, ft_lstnew_cmd(split_cmd, NULL, NULL));
	}
	return (raw_cmd);
}
