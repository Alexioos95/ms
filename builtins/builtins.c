/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:24:40 by apayen            #+#    #+#             */
/*   Updated: 2023/05/26 13:03:37 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Afficher le chemin actuel.
int	ft_pwd(struct s_shell *ms)
{
	struct s_lst	*tmp;

	tmp = ms->env;
	while (tmp != NULL && tmp->line != NULL \
		&& ft_strnstr(tmp->line, "PWD", 0) == NULL)
		tmp = tmp->next;
	if (tmp == NULL)
		return (1);
	if (tmp->line != NULL)
		printf("%s\n", &tmp->line[4]);
	return (0);
}

// Supprimer une variable du env, sans argument.
int	ft_unset(struct s_shell *ms, char *str, char *opt)
{
	int				i;
	struct s_lst	*tmp;

	i = 0;
	if (str == NULL || opt != NULL || ms->env == NULL || ms->env->line == NULL)
		return (1);
	tmp = ft_getenv(ms, str);
	if (tmp == NULL)
		return (1);
	tmp->print = 0;
	return (0);
}

// Afficher l'env, sans prendre d'argument.
int	ft_env(struct s_shell *ms, char *opt)
{
	struct s_lst	*tmp;

	if (opt != NULL)
		return (1);
	tmp = ms->env;
	while (tmp != NULL)
	{
		if (tmp->print == 1 && tmp->line != NULL)
			printf("%s\n", tmp->line);
		tmp = tmp->next;
	}
	return (0);
}

// Print la str.
// Si l'argument est "-n", ne pas print le \n a la fin.
int	ft_echo(char *opt, char *str)
{
	char	*option;

	option = "-n";
	if (opt != NULL && ft_strncmp(opt, option, 4) == 0)
	{
		if (str != NULL)
			printf("%s", str);
	}
	else
	{
		if (str != NULL)
			printf("%s\n", str);
		else
			printf("\n");
	}
	return (0);
}

// Quitter proprement le shell.
// Exit avec le status code de la derniere commande si l'argument n'est pas entre 0 et 255 !
void	ft_exit(struct s_shell *ms, char *opt)
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
			frees(ms, 1);
		}
		i++;
	}
	if (opt != NULL)
		code = ft_atoi(opt);
	frees(ms, code);
}
