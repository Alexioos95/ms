/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:06:46 by apayen            #+#    #+#             */
/*   Updated: 2023/08/15 10:08:48 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	ft_heredoc_end(struct s_shell *ms, char *delim, struct s_heredoc *hd)
{
	if (hd->line == NULL)
	{
		if (errno == ENOMEM)
		{
			close(hd->fd);
			throwerror(ms, "readline");
		}
		if (errno == EBADF)
			return (2);
		printf("-minishell: warning: here-document at line ");
		printf("%d delimited by end-of-file (wanted `%s')\n", hd->i, delim);
		return (1);
	}
	if (ft_strncmp(hd->line, delim, ft_strlen(delim)) == 0)
	{
		free(hd->line);
		close(hd->fd);
		return (1);
	}
	return (0);
}

void	ft_heredoc_filename(struct s_shell *ms, char *str)
{
	int		i;
	int		fd;

	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
	{
		free(str);
		throwerror(ms, "open");
	}
	read(fd, str, 14);
	i = 1;
	str[0] = '.';
	while (i < 15)
	{
		str[i] = (str[i] % 26) + 'a';
		i++;
	}
	str[i] = '.';
	str[16] = 't';
	str[17] = 'm';
	str[18] = 'p';
	str[19] = '\0';
	close(fd);
}

int	ft_heredoc_quotes(char *str, int i, int len)
{
	int		j;
	int		ret;
	char	c;

	c = str[i];
	while (str[i] != '\0' && str[i + 1] != c)
	{
		str[i] = str[i + 1];
		i++;
	}
	ret = i;
	j = i + 1;
	while (str[j] != '\0')
	{
		str[i] = str[j + 1];
		i++;
		j++;
	}
	while (j < len)
	{
		str[j] = '\0';
		j++;
	}
	return (ret - 1);
}

int	ft_heredoc_delim(char *str)
{
	int		i;
	int		len;
	int		state;

	i = 0;
	state = 0;
	len = ft_strlen(str);
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			state = 1;
			i = ft_heredoc_quotes(str, i, len);
		}
		i++;
	}
	return (state);
}
