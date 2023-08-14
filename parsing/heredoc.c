
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

int	ft_heredoc_loop(struct s_shell *ms, char *delim, struct s_heredoc *hd)
{
	int	isend;

	hd->i = 0;
	hd->fd = open(hd->name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (hd->fd == -1)
	{
		free(hd->name);
		throwerror(ms, "open");
	}
	while (1)
	{
		hd->line = readline("> ");
		isend = ft_heredoc_end(ms, delim, hd);
		if (isend == 1)
			return (0);
		else if (isend == 2)
			return (1);
		if (hd->state == 0)
			dprintf(2, "EXPAND\n");
		write(hd->fd, hd->line, ft_strlen(hd->line));
		free(hd->line);
		hd->i++;
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

void	ft_heredoc_init(struct s_shell *ms, struct s_heredoc *hd)
{
	hd->i = 0;
	hd->fd = -1;
	hd->line = NULL;
	hd->name = malloc(sizeof(char) * 20);
	if (hd->name == NULL)
		throwerror(ms, "malloc");
	ft_memset(hd->name, 0, 20);
	ft_heredoc_filename(ms, hd->name);
}

void	ft_heredoc(struct s_lexer *lexer, struct s_shell *ms)
{
	int					backup;
	struct s_heredoc	hd;

	backup = dup(0);
	setsigaction(ms, 3);
	while (lexer != NULL && ms->status != -1)
	{
		if (lexer->token.token != NULL \
			&& ft_strncmp(lexer->token.token, "<<", 2) == 0)
		{
			ft_heredoc_init(ms, &hd);
			hd.state = ft_heredoc_delim(lexer->token.file);
			if (ft_heredoc_loop(ms, lexer->token.file, &hd) == 1)
			{
				dup2(backup, 0);
				ms->status = -1;
			}
			free(lexer->token.file);
			lexer->token.file = hd.name;
		}
		lexer = lexer->next;
	}
	close(backup);
}
