/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 00:29:31 by bsiche            #+#    #+#             */
/*   Updated: 2018/08/19 17:52:09 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envalue(t_lstcontainer *env)
{
	t_list		*tmp;
	t_envalue	*buf;

	tmp = env->firstelement;
	while (tmp)
	{
		buf = tmp->content;
		free(buf->name);
		buf->name = NULL;
		free(buf->value);
		buf->value = NULL;
		free(buf);
		buf = NULL;
		tmp = tmp->next;
	}
	ft_lstdel(env->firstelement);
	free(env);
}

void	cmdline_free(t_cmdline *cmdline)
{
	free_tab(cmdline->tab);
	cmdline->tab = NULL;
	free(cmdline->str);
	cmdline->str = NULL;
	free(cmdline->cmd);
	cmdline->cmd = NULL;
}
