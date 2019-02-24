/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 19:07:24 by bsiche            #+#    #+#             */
/*   Updated: 2018/07/31 18:48:09 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*conc_and_free(char *path, char **tab)
{
	int i;

	i = 0;
	if (tab != NULL)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
	}
	free(tab);
	return (path);
}

char	*cd_line(char **tab, char *cdline, char *path)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	free(path);
	return (cdline);
}

char	*ft_cdpath(t_lstcontainer *env, char *path)
{
	char	**tab;
	char	*cdline;
	int		i;
	int		a;

	i = 0;
	tab = NULL;
	cdline = get_env_string(env, "CDPATH");
	if (cdline)
		tab = ft_strsplit(cdline, ':');
	if (cdline)
		while (tab[i])
		{
			a = ft_strlen(tab[i]);
			if (tab[i][a] != '/')
				tab[i] = ft_strjoin(tab[i], "/", 1);
			cdline = ft_strjoin(tab[i], path, 0);
			if (ft_isdir(cdline) == 1)
				return (cd_line(tab, cdline, path));
			i++;
		}
	return (conc_and_free(path, tab));
}
