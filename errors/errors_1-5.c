/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_1-5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:25:41 by eewu              #+#    #+#             */
/*   Updated: 2023/06/26 12:08:54 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	ft_errors_1_5(int error, char *str)
{
	if (error == 0)
	{
		printf ("bash: syntax error near unexpected token `%s'\n", str);
		return (-2);
	}
	else if (error == 1)
	{
		printf ("%s\n", str);
		return (-2);
	}
	else if (error == 2)
	{
		printf ("%s\n", str);
		return (-2);
	}
	else if (error == 3)
	{
		printf ("%s\n", str);
		return (-2);
	}
	else
	{
		printf ("%s\n", str);
		return (-2);
	}
}
