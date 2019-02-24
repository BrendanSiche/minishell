/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 16:23:05 by bsiche            #+#    #+#             */
/*   Updated: 2018/08/29 23:15:29 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_rights(char *path)
{
	if ((access(path, F_OK) == 0))
	{
		if (access(path, X_OK) != 0)
		{
			ft_putendl("permission denied");
			return (1);
		}
	}
	return (0);
}

void	ft_error(int i, t_cmdline *cmdline)
{
	if (i == 0)
	{
		ft_putstr("b_sh: command not found: ");
		ft_putendl(cmdline->tab[0]);
	}
}
