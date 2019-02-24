/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 18:12:58 by bsiche            #+#    #+#             */
/*   Updated: 2018/08/29 23:26:52 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*promptlst(char *prompt)
{
	t_lstcontainer	*lst;
	t_list			*tmp;

	lst = ft_strsplitlst(prompt, '/');
	if (lst != NULL)
	{
		tmp = ft_lstgetlast(lst->firstelement);
		free(prompt);
		prompt = ft_strdup(tmp->content);
	}
	ft_freesplitlist(lst);
	prompt = ft_strjoin("\e[1;36m", prompt, 2);
	prompt = ft_strjoin(prompt, " > ", 1);
	prompt = ft_strjoin(prompt, "\e[0m", 1);
	return (prompt);
}

char		*getprompt(t_lstcontainer *env)
{
	char			*prompt;

	if (env == NULL)
		prompt = ft_true_pwd();
	if (env != NULL)
	{
		prompt = ft_strdup(get_env_string(env, "PWD"));
		if (ft_strcmp(prompt, get_env_string(env, "HOME")) == 0)
		{
			free(prompt);
			prompt = ft_strdup("~");
		}
	}
	prompt = promptlst(prompt);
	return (prompt);
}

t_cmdline	*init_cmdline(void)
{
	t_cmdline		*cmdline;

	cmdline = NULL;
	if ((cmdline = malloc(sizeof(*cmdline))) != NULL)
	{
		cmdline->str = NULL;
		cmdline->flag = 0;
		cmdline->tab = NULL;
		cmdline->cmd = NULL;
	}
	return (cmdline);
}

void		ft_mainloop(t_cmdline *cmdline, t_lstcontainer *env)
{
	t_lstcontainer	*list;
	t_list			*tmp;

	list = ft_strsplitlst(cmdline->str, ';');
	if (list != NULL)
	{
		tmp = list->firstelement;
		free(cmdline->str);
		while (tmp)
		{
			cmdline->str = tmp->content;
			if (ft_strlen(cmdline->str) != 0)
			{
				ft_getcmd(cmdline);
				ft_isbuiltin(cmdline, env, list);
			}
			cmdline_free(cmdline);
			tmp = tmp->next;
		}
		ft_lstdel(list->firstelement);
		free(list);
	}
	else
		cmdline_free(cmdline);
}

int			main(int argc, char **argv, char **environ)
{
	t_cmdline		*cmdline;
	t_lstcontainer	*env;
	char			*prompt;

	argc = 2;
	argv[1] = NULL;
	env = ft_env_to_lst(environ);
	prompt = getprompt(env);
	ft_putstr(prompt);
	free(prompt);
	cmdline = init_cmdline();
	while (1)
	{
		if ((get_next_line(0, &cmdline->str)) > 0)
			ft_mainloop(cmdline, env);
		else
			ft_putchar('\n');
		prompt = getprompt(env);
		ft_putstr(prompt);
		free(prompt);
	}
	return (0);
}
