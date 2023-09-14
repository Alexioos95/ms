/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:24:40 by apayen            #+#    #+#             */
/*   Updated: 2023/09/14 15:36:07 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// Verifie que le tableau ne contient que des chiffres.
void	ft_exit_checktab(struct s_shell *ms, char *str, int i)
{
	int	b;

	b = 0;
	ft_atoi(str, &b);
	if (b == 1)
	{
		printf("minishell: exit: %s: numeric argument required\n", str);
		frees(ms, 2);
	}
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
		{
			printf("minishell: exit: %s: numeric argument required\n", str);
			frees(ms, 2);
		}
		i++;
	}
}

// Quitter proprement le programme.
int	ft_exit(struct s_shell *ms, char **tab)
{
	int	i;

	i = 0;
	printf("exit\n");
	if (tab[1] == NULL)
		frees(ms, ms->status);
	if (tab[1][0] == '-' || tab[1][0] == '+')
		i++;
	ft_exit_checktab(ms, tab[1], i);
	if (tab[2] != NULL)
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	frees(ms, (int)ft_atoi(tab[1], &i));
	return (0);
}

// Affiche le chemin actuel.
int	ft_pwd(struct s_shell *ms)
{
	if (ms->pwdpath != NULL)
		printf("%s\n", &ms->pwdpath[4]);
	else
	{
		printf("pwd: error retrieving current directory: getcwd: cannot ");
		printf("access parent directories: No such file or directory\n");
		return (1);
	}
	return (0);
}

// Supprimer une variable du env.
// Ne supprime pas la node de la liste chainee, mais met un flag dessus.
int	ft_unset(struct s_shell *ms, char **tab)
{
	int				i;
	struct s_lst	*tmp;

	i = 1;
	if (tab[1] == NULL || ms->env == NULL || ms->env->line == NULL)
		return (0);
	while (tab[i] != NULL)
	{
		i++;
		tmp = ft_getenv(ms, tab[i - 1]);
		if (tmp == NULL)
			continue ;
		if (ft_strncmp(tmp->line, "OLDPWD=", 7) == 0 && ms->oldpwdpath != NULL)
		{
			free(ms->oldpwdpath);
			ms->oldpwdpath = NULL;
		}
		tmp->print = 0;
	}
	return (0);
}

// Print l'env, en ignorant les nodes flagge par unset.
int	ft_env(struct s_shell *ms, char **tab)
{
	struct s_lst	*tmp;

	if (tab[1] != NULL)
	{
		printf("minishell: env: too many arguments\n");
		return (1);
	}
	tmp = ms->env;
	while (tmp != NULL)
	{
		if (tmp->print == 1 && tmp->line != NULL)
		{
			printf("%s\n", tmp->line);
			if (errno == ENOSPC)
			{
				write(2, "env: write error: No space left on device\n", 42);
				return (125);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
