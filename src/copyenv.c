/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copyenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 18:55:40 by bsiche            #+#    #+#             */
/*   Updated: 2018/08/06 04:57:09 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_printab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		ft_putendl(tab[i]);
		i++;
	}
}

char	*get_env_string(t_lstcontainer *env, char *str)
{
	t_list		*tmp;
	t_envalue	*buf;

	if (env == NULL)
		return (NULL);
	tmp = env->firstelement;
	while (tmp)
	{
		buf = tmp->content;
		if (ft_strcmp(str, buf->name) == 0)
			return (buf->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int		replace_env_str(t_lstcontainer *env, char *s1, char *s2)
{
	t_list		*tmp;
	t_envalue	*buf;

	if (env == NULL)
	{
		ft_add_env_string(env, s1, s2);
		return (0);
	}
	tmp = env->firstelement;
	while (tmp)
	{
		buf = tmp->content;
		if (ft_strcmp(s1, buf->name) == 0)
		{
			free(buf->value);
			buf->value = ft_strdup(s2);
			return (0);
		}
		tmp = tmp->next;
	}
	ft_add_env_string(env, s1, s2);
	return (0);
}

void	ft_add_env_string(t_lstcontainer *env, char *s1, char *s2)
{
	t_envalue	*buf;

	if (env == NULL)
		env = lstcontainer_new();
	buf = malloc(sizeof(*buf));
	buf->value = NULL;
	buf->name = NULL;
	buf->name = ft_strdup(s1);
	buf->value = ft_strdup(s2);
	env->add(env, buf, 1);
}

char	*remove_env_string(t_lstcontainer *env, char *str)
{
	t_list		*tmp;
	t_envalue	*buf;

	if (env == NULL)
		return (NULL);
	tmp = env->firstelement;
	while (tmp)
	{
		buf = tmp->content;
		if (ft_strcmp(str, buf->name) == 0)
		{
			env->remove(env, tmp);
			return (NULL);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
