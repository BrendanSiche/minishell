/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 03:11:47 by bsiche            #+#    #+#             */
/*   Updated: 2018/08/06 04:00:27 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_convert2(t_lstcontainer *env,
t_cmdline *cmdline, int i, char *newstr)
{
	while (cmdline->tab[i])
	{
		if ((cmdline->tab[i][0] == '~') && ((cmdline->tab[i][1]) == '\0'
		|| cmdline->tab[i][1] == '/'))
		{
			if (cmdline->tab[i][1] == '\0')
			{
				free(cmdline->tab[i]);
				cmdline->tab[i] = ft_strdup(get_env_string(env, "HOME"));
			}
			if (cmdline->tab[i][i] == '/')
			{
				newstr = ft_strdup(get_env_string(env, "HOME"));
				cmdline->tab[i] = ft_strsub(cmdline->tab[i], 1,
				ft_strlen(cmdline->tab[i]), 1);
				cmdline->tab[i] = ft_strjoin(newstr, cmdline->tab[i], 3);
			}
		}
		i++;
	}
}

void	ft_convert1(t_lstcontainer *env,
t_cmdline *cmdline, char *newstr, int i)
{
	int		a;

	while (cmdline->tab[i])
	{
		a = 0;
		while (cmdline->tab[i][a])
		{
			if (cmdline->tab[i][a] == '$' && cmdline->tab[i][a + 1] != '$')
			{
				newstr = ft_strsub(cmdline->tab[i], a + 1,
				ft_strlen(cmdline->tab[i]), 0);
				cmdline->tab[i] = ft_strsub(cmdline->tab[i], 0, a, 1);
				free(newstr);
				newstr = ft_strdup(get_env_string(env, newstr));
				if (newstr == NULL)
					newstr = ft_strnew(0);
				cmdline->tab[i] = ft_strjoin(cmdline->tab[i], newstr, 3);
			}
			if (cmdline->tab[i][a + 1] != '\0')
				a++;
			else
				break ;
		}
		i++;
	}
}

void	ft_convert(t_lstcontainer *env, t_cmdline *cmdline)
{
	int		i;
	char	*newstr;

	i = 1;
	newstr = NULL;
	ft_convert1(env, cmdline, newstr, i);
	i = 0;
	ft_convert2(env, cmdline, i, newstr);
}
