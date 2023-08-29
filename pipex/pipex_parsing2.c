/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsing2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:50:02 by eewu              #+#    #+#             */
/*   Updated: 2023/08/28 15:26:31 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_redir	*ft_redir_lstnew(t_tokens token)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	new->token = token;
	new->next = NULL;
	return (new);
}

t_redir	*ft_redir_lstlast(t_redir *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_redir_lstadd_back(t_redir **lst, t_redir *new, t_pipex *m)
{
	t_redir	*last;

	if (*lst == NULL)
	{
		*lst = new;
		m->tokenhead = *lst;
		return ;
	}
	last = ft_redir_lstlast(*lst);
	last->next = new;
}

void	ft_redir_in_cmd(t_pipex *m, t_lexer **lexer, t_cmd_lst *cmd)
{
	t_redir		*redir;

	redir = NULL;
	while ((*lexer) && !((*lexer)->token.pipe))
	{
		if ((*lexer)->token.token)
			ft_redir_lstadd_back(&redir, ft_redir_lstnew((*lexer)->token), m);
		(*lexer) = (*lexer)->next;
	}
	cmd->redirlst = redir;
}

void	ft_redir_list(t_pipex *m, t_shell *ms)
{
	t_lexer		*lexer;
	t_cmd_lst	*cmd;

	lexer = ms->lexer;
	cmd = m->cmd;
	while (lexer && cmd)
	{
		ft_redir_in_cmd(m, &lexer, cmd);
		while (lexer && (lexer->token.pipe))
			lexer = lexer->next;
		cmd = cmd->next;
	}
}
