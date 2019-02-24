/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 04:40:44 by bsiche            #+#    #+#             */
/*   Updated: 2018/08/29 22:53:31 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**init_envp(t_lstcontainer *env)
{
	int			i;
	char		**envp;
	t_list		*tmp;
	t_envalue	*buf;

	envp = NULL;
	if (env != NULL)
	{
		i = env->size(env) + 1;
		envp = malloc(sizeof(char *) * i + 1);
		i = 0;
		tmp = env->firstelement;
		while (tmp)
		{
			buf = tmp->content;
			envp[i] = ft_strnew(0);
			envp[i] = ft_strjoin(envp[i], buf->name, 1);
			envp[i] = ft_strjoin(envp[i], "=", 1);
			envp[i] = ft_strjoin(envp[i], buf->value, 1);
			tmp = tmp->next;
			i++;
		}
		envp[i] = NULL;
	}
	return (envp);
}
