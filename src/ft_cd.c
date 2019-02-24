/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 15:17:02 by bsiche            #+#    #+#             */
/*   Updated: 2018/08/29 23:05:27 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_parsecd(t_cmdline *cmdline)
{
	int i;

	i = 1;
	while (cmdline->tab[i])
	{
		if (ft_strcmp(cmdline->tab[i], "-") == 0)
			return (i);
		if (cmdline->tab[i][0] == '-')
		{
			if (cmdline->tab[i][1] == 'P' || cmdline->tab[i][1] == 'L')
				cmdline->option = cmdline->tab[i][1];
			if (cmdline->tab[i][1] == '-')
			{
				i++;
				return (i);
			}
			if (cmdline->tab[i][1] != 'P' && cmdline->tab[i][1] != 'L'
			&& cmdline->tab[i][1] != '-')
				return (i);
		}
		if (cmdline->tab[i][0] != '-')
			return (i);
		i++;
	}
	return (i);
}

void	ft_changedir(t_lstcontainer *env, t_cmdline *cmdline, char *path)
{
	char	*truepwd;
	char	*oldpwd;

	if (getright(path) == 0)
	{
		truepwd = ft_true_pwd();
		replace_env_str(env, "TRUEOLDPWD", truepwd);
		oldpwd = ft_strdup(get_env_string(env, "PWD"));
		chdir(path);
		if (cmdline->option != 'P')
			replace_env_str(env, "PWD", path);
		else
			replace_env_str(env, "PWD", truepwd);
		replace_env_str(env, "OLDPWD", oldpwd);
		free(truepwd);
		truepwd = NULL;
		free(oldpwd);
	}
}

char	*buildpath(t_lstcontainer *env, t_cmdline *cmdline, char *path)
{
	char	*pwd;
	int		i;

	pwd = NULL;
	if (cmdline->option == 'P')
		pwd = ft_true_pwd();
	else
		pwd = ft_strdup(get_env_string(env, "PWD"));
	if (pwd == NULL)
		pwd = ft_true_pwd();
	i = ft_strlen(pwd);
	if (pwd[i] != '/')
		pwd = ft_strjoin(pwd, "/", 1);
	if (path[0] != '/')
		path = ft_strjoin(pwd, path, 2);
	path = ft_dot(path);
	free(pwd);
	return (path);
}

int		ft_cd2(t_cmdline *cmdline, t_lstcontainer *env, int i, char *path)
{
	if (ft_strlen(path) == 0)
		ft_putendl("cd: HOME not set");
	if (ft_strlen(path) == 0)
		return (0);
	if (ft_strcmp(path, "/") == 0)
	{
		ft_changedir(env, cmdline, path);
		return (0);
	}
	path = ft_homepath(path, env);
	if (path[0] != '.' && path[0] != '/')
		path = ft_cdpath(env, path);
	if (cmdline->option != 'P')
		path = buildpath(env, cmdline, path);
	ft_changedir(env, cmdline, path);
	if (i == 875)
		ft_putendl(path);
	free(path);
	return (0);
}

int		ft_cd(t_cmdline *cmdline, t_lstcontainer *env)
{
	char			*path;
	int				i;

	i = ft_parsecd(cmdline);
	path = NULL;
	if (!cmdline->tab[i] || ft_strcmp(cmdline->tab[i], "~") == 0)
		path = ft_strdup(get_env_string(env, "HOME"));
	else
		path = ft_strdup((cmdline->tab[i]));
	if (ft_strcmp(cmdline->tab[i], "-") == 0)
	{
		i = 875;
		free(path);
		path = ft_strdup(get_env_string(env, "OLDPWD"));
		if (ft_strlen(path) == 0)
		{
			ft_putendl("OLDPWD not set");
			return (0);
		}
	}
	ft_cd2(cmdline, env, i, path);
	return (0);
}
