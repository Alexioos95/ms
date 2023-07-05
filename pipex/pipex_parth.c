/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parth.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:14:53 by eewu              #+#    #+#             */
/*   Updated: 2023/06/22 11:47:25 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../header.h"


// int	check_path(char *tab_env)
// {
// 	char	*path;
// 	int		i;

// 	i = 0;
// 	path = "PATH=";
// 	if (!tab_env)
// 		return (0);
// 	while (tab_env[i])
// 	{
// 		if (tab_env[i] == path[i])
// 			i++;
// 		else
// 			break ;
// 	}
// 	if (i == 5)
// 		return (1);
// 	else
// 		return (0);
// }

// static int	ft_pathorexec(t_struct *m, int i, int path)
// {
// 	char	**cmd;

// 	cmd = ft_split(m->av[i], ' ');
// 	if (((int)ft_strlen(cmd[0]) >= 1) && \
// 		(cmd[0][0] == '/' || (cmd[0][0] == '.')))
// 	{
// 		if (!access(cmd[0], X_OK) && path == 0)
// 		{
// 			ft_free_tab(cmd);
// 			return (0);
// 		}
// 		ft_free_tab(cmd);
// 		return (m->eror = errno);
// 	}
// 	ft_free_tab(cmd);
// 	return (m->eror = 2);
// }

// void	ft_access(t_struct *m, int i, int j, int p)
// {
// 	char	**tab_cmd;
// 	char	*join;

// 	p = ft_pathorexec(m, i, p);
// 	tab_cmd = ft_split(m->av[i], ' ');
// 	if (p == 0)
// 		ft_lstadd_back(&m->cmd, ft_lstnew(tab_cmd, p), m);
// 	else
// 	{
// 		while (m->s_ev[j] && p != 0 && (int)ft_strlen(tab_cmd[0]) >= 1)
// 		{
// 			join = ft_join(m->s_ev[j++], tab_cmd[0]);
// 			if (access(join, X_OK) != 0)
// 				free(join);
// 			else
// 			{
// 				free(tab_cmd[0]);
// 				tab_cmd[0] = join;
// 				p = 0;
// 				ft_lstadd_back(&m->cmd, ft_lstnew(tab_cmd, p), m);
// 			}
// 		}
// 		if (p != 0)
// 			ft_lstadd_back(&m->cmd, ft_lstnew(tab_cmd, m->eror), m);
// 	}
// }

// void	ft_list_tab(t_struct *m)
// {
// 	int		i;
// 	int		j;
// 	int		p;

// 	if (m->hdoc)
// 		i = 3;
// 	else
// 		i = 2;
// 	while (m->av[i + 1])
// 	{
// 		j = 0;
// 		p = 0;
// 		ft_access(m, i, j, p);
// 		i++;
// 	}
// 	m->cmd_i = 0;
// }

// void	find_cmd(t_struct *m)
// {
// 	int		i;

// 	i = 0;
// 	while (m->ev[i])
// 	{
// 		if (check_path(m->ev[i]))
// 			break ;
// 		i++;
// 	}
// 	if (m->ev[i])
// 		m->s_ev = ft_split(&m->ev[i][5], ':');
// 	else
// 	{
// 		m->s_ev = ft_calloc(sizeof(char *), 2);
// 		if (!m->s_ev)
// 			ft_free_process(m, errno);
// 		m->s_ev[0] = ft_calloc(sizeof(char), 1);
// 		if (!m->s_ev[0])
// 			ft_free_process(m, errno);
// 	}
// 	ft_list_tab(m);
// 	ft_free_tab(m->s_ev);
// }
