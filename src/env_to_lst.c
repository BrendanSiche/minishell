/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 23:10:09 by bsiche            #+#    #+#             */
/*   Updated: 2018/08/06 05:03:58 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envalue			*ft_env2(t_lstcontainer *split)
{
	t_envalue		*buf;
	t_list			*tmp;

	tmp = split->firstelement;
	buf = malloc(sizeof(*buf));
	buf->name = ft_strdup(tmp->content);
	buf->value = ft_strnew(0);
	tmp = tmp->next;
	while (tmp)
	{
		buf->value = ft_strjoin(buf->value, tmp->content, 1);
		tmp = tmp->next;
	}
	return (buf);
}

void				add_missing_string(t_lstcontainer *env)
{
	char	*pwd;

	pwd = ft_true_pwd();
	if (get_env_string(env, "PWD") == NULL)
		replace_env_str(env, "PWD", pwd);
	ft_add_env_string(env, "TRUEPWD", pwd);
	ft_add_env_string(env, "TRUEOLDPWD", pwd);
	free(pwd);
}

t_lstcontainer		*ft_env_to_lst(char **tab)
{
	t_lstcontainer	*env;
	t_lstcontainer	*split;
	t_envalue		*buf;
	int				i;

	i = 0;
	env = NULL;
	env = lstcontainer_new();
	while (tab[i])
	{
		split = ft_strsplitlst(tab[i], '=');
		if (split != NULL)
		{
			buf = ft_env2(split);
			env->add(env, buf, 1);
		}
		ft_freesplitlist(split);
		i++;
	}
	add_missing_string(env);
	return (env);
}

t_lstcontainer		*copyenv(t_lstcontainer *env)
{
	t_lstcontainer	*envcpy;
	t_list			*tmp;
	t_envalue		*buf;

	envcpy = lstcontainer_new();
	tmp = env->firstelement;
	while (tmp)
	{
		buf = malloc(sizeof(*buf));
		buf->name = ft_strdup(((t_envalue*)tmp->content)->name);
		buf->value = ft_strdup(((t_envalue*)tmp->content)->value);
		envcpy->add(envcpy, buf, 1);
		tmp = tmp->next;
	}
	tmp = envcpy->firstelement;
	return (envcpy);
}

t_lstcontainer		*emptyenv(t_lstcontainer *env)
{
	t_lstcontainer	*empty;
	t_list			*tmp;
	t_envalue		*buf;

	empty = lstcontainer_new();
	tmp = env->firstelement;
	while (tmp)
	{
		buf = malloc(sizeof(*buf));
		buf->name = ft_strdup(((t_envalue*)tmp->content)->name);
		if (ft_strcmp(buf->name, "PATH") == 0)
			buf->value = ft_strdup(((t_envalue*)tmp->content)->value);
		else
			buf->value = ft_strnew(0);
		empty->add(empty, buf, 1);
		tmp = tmp->next;
	}
	return (empty);
}
