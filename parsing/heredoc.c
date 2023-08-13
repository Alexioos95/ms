
#include "../header.h"

void	ft_heredoc_loop(struct s_shell *ms, char *delim, char *name, int state)
{
	int 	fd;
	char	*line;

	fd = open(name, O_WRONLY | O_CREAT);
	if (fd == -1)
	{
		free(name);
		throwerror(ms, "open");
	}
	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strncmp(line, delim, ft_strlen(delim)) == 0)
		{
			free(line);
			close(fd);
			return ;
		}
		if (state == 0)
			dprintf(2, "NO EXPAND\n");
		write(fd, line, ft_strlen(line));
		free(line);
	}
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

void	ft_heredoc(struct s_lexer *lexer, struct s_shell *ms)
{
	int		state;
	char	*name;

	while (lexer != NULL)
	{
		if (lexer->token.token != NULL && ft_strncmp(lexer->token.token, "<<", 2) == 0)
		{
			state = ft_heredoc_delim(lexer->token.file);
			name = malloc(sizeof(char) * 20);
			if (name == NULL)
				throwerror(ms, "malloc");
			ft_memset(name, 0, 20);
			ft_heredoc_filename(ms, name);
			ft_heredoc_loop(ms, lexer->token.file, name, state);
			free(lexer->token.file);
			lexer->token.file = name;
		}
		lexer = lexer->next;
	}
}
