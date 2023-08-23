/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:06:19 by apayen            #+#    #+#             */
/*   Updated: 2023/08/15 11:48:01 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// Regarde si la boucle du heredoc doit être stoppé.
int	ft_heredoc_end(struct s_shell *ms, char *delim, struct s_heredoc *hd)
{
	if (hd->line == NULL)
	{
		rl_replace_line("", 0);
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

// Boucle du heredoc.
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
			hd->line = ft_heredoc_expand(hd, hd->line);
		write(hd->fd, hd->line, ft_strlen(hd->line));
		write(hd->fd, "\n", 1);
		free(hd->line);
		hd->i++;
	}
	return (0);
}

// Initialise les variables.
void	ft_heredoc_init(struct s_shell *ms, struct s_heredoc *hd)
{
	hd->i = 0;
	hd->fd = -1;
	hd->line = NULL;
	hd->name = malloc(sizeof(char) * 20);
	if (hd->name == NULL)
		throwerror(ms, "malloc");
	hd->ms = ms;
	ft_memset(hd->name, 0, 20);
	ft_heredoc_filename(ms, hd->name);
}

// Parcours la liste chaînée, et fais autant de heredoc que necessaire.
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
				printf("\n");
				ms->status = -1;
			}
			free(lexer->token.file);
			lexer->token.file = hd.name;
		}
		lexer = lexer->next;
	}
	close(backup);
}
