/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 19:33:30 by bsiche            #+#    #+#             */
/*   Updated: 2018/08/19 17:41:51 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_ispair(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (-1);
}

char	*pairparse(t_lstcontainer *newenv, t_cmdline *cmdline, int i, int a)
{
	char			*str;
	char			**split;

	i = 1;
	while (cmdline->tab[i] && ft_strcmp(cmdline->tab[i], "-i") == 0)
		i++;
	while (cmdline->tab[i] != NULL && ft_ispair(cmdline->tab[i]) != -1)
	{
		a = 1;
		split = ft_strsplit(cmdline->tab[i], '=');
		str = ft_strnew(0);
		while (split[a] != NULL)
		{
			if (a != 1)
				str = ft_strjoin(str, "=", 1);
			str = ft_strjoin(str, split[a], 3);
			if (replace_env_str(newenv, split[0], str) == -1)
				ft_add_env_string(newenv, split[0], str);
			a++;
		}
		free(split);
		i++;
	}
	str = getnewcmd(cmdline->tab, i);
	return (str);
}

void	newcmd(t_cmdline *cmdline, char *newstr)
{
	cmdline_free(cmdline);
	cmdline->cmd = NULL;
	cmdline->str = ft_strdup(newstr);
	cmdline->tab = ft_strsplit(cmdline->str, ' ');
	cmdline->cmd = ft_strdup(cmdline->tab[0]);
	ft_parseoption(cmdline);
	cmdline->flag = 18;
	free(newstr);
}

int		ft_env(t_cmdline *cmdline, t_lstcontainer *env, t_lstcontainer *list)
{
	t_lstcontainer		*newenv;
	char				*newstr;

	newenv = NULL;
	newstr = NULL;
	if (cmdline->tab[1] == NULL)
	{
		ft_printlist(env);
		return (0);
	}
	if (ft_strcmp(cmdline->tab[1], "-i") == 0)
		newenv = emptyenv(env);
	else
		newenv = copyenv(env);
	newstr = pairparse(newenv, cmdline, 1, 1);
	if (newstr != NULL)
		newcmd(cmdline, newstr);
	if (cmdline->flag == 18)
		ft_isbuiltin(cmdline, newenv, list);
	else
		ft_printlist(newenv);
	free_envalue(newenv);
	cmdline_free(cmdline);
	return (0);
}
