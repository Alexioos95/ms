/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:24:40 by apayen            #+#    #+#             */
/*   Updated: 2023/05/24 16:27:48 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Print la str.
// Si l'argument est "-n", ne pas print le \n a la fin.
// (A mettre en dur dans le parseur...)
int	ft_echo(char *str, char *opt)
{
	char	*option;

	option = "-n";
	if (opt != NULL && ft_strncmp(opt, option, 4) == 0)
		printf("%s", str);
	else
		printf("%s\n", str);
	return (0);
}

// Afficher l'env, sans prendre d'argument.
int	ft_env(struct s_shell *ms, char *opt)
{
	if (opt != NULL || ms->env->line == NULL)
		return (1);
	while (ms->env != NULL)
	{
		if (ms->env->flag != UNSET && ms->env->line != NULL)
			printf("%s\n", ms->env->line);
		ms->env = ms->env->next;
	}
	ms->env = ms->lsthead;
	return (0);
}

// Quitter proprement le shell.
// Exit avec le status code de la derniere commande si l'argument n'est pas entre 0 et 255 !
int	ft_exit(struct s_shell *ms, char *opt)
{
	int	i;
	int	code;

	i = 0;
	code = 0;
	printf("exit\n");
	while (opt != NULL && opt[i] != '\0')
	{
		if (opt[i] < '0' || opt[i] > '9')
		{
			printf("minishell: exit: %s: numeric argument required\n", opt);
			break ;
		}
		i++;
	}
	if (opt != NULL)
		code = ft_atoi(opt);
	frees(ms);
	exit(code);
}

// Supprimer une variable du env, sans argument.
int	ft_unset(struct s_shell *ms, char *str, char *opt)
{
	int	i;

	i = 0;
	if (str == NULL || opt != NULL || ms->env == NULL || ms->env->line == NULL)
		return (1);
	while (ms->env != NULL && ft_strnstr(ms->env->line, str, 0) == NULL \
		&& ms->env->flag != UNSET)
		ms->env = ms->env->next;
	if (ms->env == NULL)
	{
		ms->env = ms->lsthead;
		return (1);
	}
	ft_lstdelone(ms->env);
	ms->env = ms->lsthead;
	return (0);
}

// Afficher le chemin actuel.
int	ft_pwd(void)
{
	char	*pwd;

	pwd = getenv("PWD");
	printf("%s\n", pwd);
	return (0);
}
