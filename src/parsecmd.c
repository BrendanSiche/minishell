/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 18:46:26 by bsiche            #+#    #+#             */
/*   Updated: 2018/08/19 17:55:49 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_isbuiltin2(t_cmdline *cmdline, t_lstcontainer *env)
{
	if (ft_strcmp(cmdline->cmd, "cd") == 0)
	{
		ft_cd(cmdline, env);
		return (0);
	}
	if (ft_strcmp(cmdline->cmd, "pwd") == 0)
	{
		ft_pwd(env, cmdline);
		return (0);
	}
	if (ft_strcmp(cmdline->cmd, "setenv") == 0)
	{
		ft_setenv(cmdline, env);
		return (0);
	}
	if (ft_strcmp(cmdline->cmd, "unsetenv") == 0)
		ft_unsetenv(env, cmdline);
	else
		ft_exec(env, cmdline);
	return (0);
}

int		ft_isbuiltin(t_cmdline *cmdline, t_lstcontainer *env,
		t_lstcontainer *list)
{
	if (ft_strlen(cmdline->cmd) == 0)
		return (0);
	if (ft_strcmp(cmdline->cmd, "echo") == 0)
	{
		ft_echo(env, cmdline);
		return (0);
	}
	if (ft_strcmp(cmdline->cmd, "exit") == 0)
	{
		cmdline_free(cmdline);
		free(cmdline);
		if (list)
			ft_lstdel(list->firstelement);
		if (env != NULL)
			free_envalue(env);
		exit(0);
	}
	if (ft_strcmp(cmdline->cmd, "env") == 0)
	{
		ft_env(cmdline, env, list);
		return (0);
	}
	ft_isbuiltin2(cmdline, env);
	return (0);
}

void	ft_parseoption(t_cmdline *cmdline)
{
	int		i;

	i = 0;
	cmdline->flag = 0;
	cmdline->option = 'L';
	while (cmdline->tab[i])
	{
		if (cmdline->tab[i][0] != '-' || ft_strcmp(cmdline->tab[i], "--") == 0)
		{
			i++;
			break ;
		}
		if (cmdline->tab[i][1] == 'L')
			cmdline->option = 'L';
		if (cmdline->tab[i][1] != 'L' && cmdline->tab[i][1] != 'P')
			cmdline->flag = 1;
		i++;
	}
}

void	ft_getcmd(t_cmdline *cmdline)
{
	cmdline->tab = ft_split_white(cmdline->str);
	cmdline->cmd = ft_strdup(cmdline->tab[0]);
	ft_parseoption(cmdline);
}
