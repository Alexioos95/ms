/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:24:40 by apayen            #+#    #+#             */
/*   Updated: 2023/06/02 10:14:41 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Afficher le chemin actuel.
int	ft_pwd(struct s_shell *ms)
{
	if (ms->pwdpath != NULL)
		printf("%s\n", &ms->pwdpath[4]);
	return (0);
}

// Supprimer une variable du env.
int	ft_unset(struct s_shell *ms, char *str, char *opt)
{
	struct s_lst	*tmp;

	if (str == NULL || opt != NULL || ms->env == NULL || ms->env->line == NULL)
		return (1);
	tmp = ft_getenv(ms, str);
	if (tmp == NULL)
		return (0);
	tmp->print = 0;
	return (0);
}

// Afficher l'env.
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
int	ft_echo(char *str, char *opt)
{
	char	*option;

	option = "-n";
	if (opt != NULL && ft_strncmp(opt, option, 3) == 0)
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
// Exit avec le status code de la derniere commande si l'argument n'est pas entre 0 et 255.
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
