/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 18:14:29 by bsiche            #+#    #+#             */
/*   Updated: 2018/08/06 03:19:09 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(t_lstcontainer *env, t_cmdline *cmdline)
{
	int i;

	i = 1;
	ft_convert(env, cmdline);
	if (cmdline == NULL)
		ft_putstr("\n");
	else
	{
		while (ft_strlen(cmdline->tab[i]) != 0)
		{
			ft_putstr(cmdline->tab[i]);
			i++;
			if (cmdline->tab != NULL)
				ft_putchar(' ');
		}
		ft_putchar('\n');
	}
	return (0);
}

void	ft_pwd(t_lstcontainer *env, t_cmdline *cmdline)
{
	char *pwd;

	if (cmdline->option != 'P')
		pwd = get_env_string(env, "PWD");
	else
		pwd = ft_true_pwd();
	ft_putendl(pwd);
}

char	*ft_true_pwd(void)
{
	char	*buf;
	char	*str;

	buf = ft_strnew(1024);
	getcwd(buf, 1024);
	str = ft_strdup(buf);
	free(buf);
	return (str);
}
