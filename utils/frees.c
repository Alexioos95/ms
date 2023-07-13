/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:36:20 by apayen            #+#    #+#             */
/*   Updated: 2023/07/13 14:22:57 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_lstclear(struct s_lst *lst)
{
	struct s_lst	*tmp;

	if (lst == NULL)
		return ;
	while (lst != NULL)
	{
		tmp = lst->next;
		free(lst->line);
		free(lst);
		lst = tmp;
	}
}

void	ft_lexerclear(t_lexer *lexer)
{
	t_lexer		*tmp;
	int			i;
	int			len;

	i = 0;
	if (lexer == NULL)
		return ;
	len = lexer->len;
	while (i < len)
	{
		tmp = lexer->next;
		if (lexer->str)
			free(lexer->str);
		if (lexer->token.token)
			free(lexer->token.token);
		if (lexer->token.arg)
			free(lexer->token.arg);
		if (lexer->token.pipe)
			free(lexer->token.pipe);
		free(lexer);
		lexer = tmp;
		i++;
	}
}

// Free un tableau de split.
void	freesplit(char **strmalloc)
{
	int	i;

	i = 0;
	if (strmalloc == NULL)
		return ;
	while (strmalloc[i] != NULL)
	{
		free(strmalloc[i]);
		i++;
	}
	free(strmalloc);
}

// Free toutes les variables.
_Noreturn void	frees(struct s_shell *ms, int code)
{
	if (ms->line != NULL)
		free(ms->line);
	if (ms->split != NULL)
		freesplit(ms->split);
	if (ms->env != NULL)
		ft_lstclear(ms->env);
	if (ms->tmp != NULL)
		free(ms->tmp);
	if (ms->pwdpath != NULL)
		free(ms->pwdpath);
	if (ms->oldpwdpath != NULL)
		free(ms->oldpwdpath);
	rl_clear_history();
	exit(code);
}

_Noreturn void	throwerror(struct s_shell *ms, char *str)
{
	printf("minishell: %s: %s\n", strerror(errno), str);
	frees(ms, 1);
}
