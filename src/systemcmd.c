/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   systemcmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 13:39:06 by bsiche            #+#    #+#             */
/*   Updated: 2018/08/29 23:22:07 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lstcontainer		*ft_pathlist(t_lstcontainer *env, t_cmdline *cmdline)
{
	t_lstcontainer	*new;
	t_list			*list;
	char			*tmp;

	new = NULL;
	list = NULL;
	tmp = ft_strdup(get_env_string(env, "PATH"));
	if (tmp != NULL)
	{
		tmp = ft_strjoin(tmp, ":.", 1);
		new = ft_strsplitlst(tmp, ':');
		list = new->firstelement;
		while (list)
		{
			list->content = ft_strjoin(list->content, "/", 1);
			list->content = ft_strjoin(list->content, cmdline->tab[0], 1);
			list = list->next;
		}
		free(tmp);
	}
	return (new);
}

int					ft_custompath(char *path, t_cmdline *cmdline, char **envp)
{
	if (check_rights(path) == 0)
	{
		if (execve(path, cmdline->tab, envp) == 1)
			return (1);
	}
	return (0);
}

void				execute(t_cmdline *cmdline, char **envp,
char *path, t_list *list)
{
	int		i;

	i = 0;
	if (list == NULL)
		i = ft_custompath(path, cmdline, envp);
	while (list)
	{
		path = list->content;
		if (check_rights(path) == 0)
		{
			if (execve(path, cmdline->tab, envp) == 1)
			{
				i = 1;
				break ;
			}
		}
		else
			i = 1;
		list = list->next;
	}
	ft_error(i, cmdline);
	free_tab(envp);
	envp = NULL;
	exit(0);
}

int					free_and_quit(pid_t father, t_lstcontainer *pathlist,
					char **envp)
{
	wait(&father);
	ft_freesplitlist(pathlist);
	pathlist = NULL;
	free_tab(envp);
	envp = NULL;
	return (0);
}

int					ft_exec(t_lstcontainer *env, t_cmdline *cmdline)
{
	pid_t			father;
	t_lstcontainer	*pathlist;
	t_list			*list;
	char			*path;
	char			**envp;

	list = NULL;
	pathlist = NULL;
	envp = init_envp(env);
	if (cmdline->str[0] != '/')
	{
		pathlist = ft_pathlist(env, cmdline);
		if (pathlist != NULL)
			list = pathlist->firstelement;
	}
	else
		path = cmdline->tab[0];
	father = fork();
	if (father > 0)
		return (free_and_quit(father, pathlist, envp));
	if (father == 0)
		execute(cmdline, envp, path, list);
	return (-1);
}
