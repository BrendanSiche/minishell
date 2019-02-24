/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 09:00:54 by bsiche            #+#    #+#             */
/*   Updated: 2018/08/06 05:11:40 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_printlist(t_lstcontainer *env)
{
	t_list			*tmp;
	t_envalue		*buf;

	tmp = env->firstelement;
	buf = NULL;
	while (tmp)
	{
		buf = tmp->content;
		ft_putstr(buf->name);
		ft_putchar('=');
		ft_putendl(buf->value);
		tmp = tmp->next;
	}
}

char	*getnewcmd(char **tab, int i)
{
	char	*newstr;

	newstr = NULL;
	if (tab[i])
		newstr = ft_strnew(0);
	while (ft_strcmp(tab[i], "-i") == 0)
		i++;
	while (tab[i])
	{
		newstr = ft_strjoin(newstr, tab[i], 1);
		newstr = ft_strjoin(newstr, " ", 1);
		i++;
	}
	return (newstr);
}

int		ft_removequote(t_cmdline *cmdline)
{
	int		i;

	i = ft_strlen(cmdline->tab[2]);
	if (cmdline->tab[2][0] != '"' || cmdline->tab[2][i - 1] != '"')
		return (1);
	else
		return (0);
}

int		ft_setenv(t_cmdline *cmdline, t_lstcontainer *env)
{
	int		i;

	if (cmdline->tab[1] == NULL || cmdline->tab[2] == NULL)
	{
		ft_putendl("Usage : setenv [name] [\"value\"]");
		return (0);
	}
	if (ft_removequote(cmdline) != 0)
	{
		ft_putendl("Usage : setenv [name] [\"value\"]");
		return (0);
	}
	i = ft_strlen(cmdline->tab[2]) - 2;
	cmdline->tab[2] = ft_strsub(cmdline->tab[2], 1, i, 1);
	replace_env_str(env, cmdline->tab[1], cmdline->tab[2]);
	return (0);
}

int		ft_unsetenv(t_lstcontainer *env, t_cmdline *cmdline)
{
	if (cmdline->tab[1] == NULL)
	{
		ft_putendl("Usage : unsetenv [name]");
		return (0);
	}
	remove_env_string(env, cmdline->tab[1]);
	return (0);
}
