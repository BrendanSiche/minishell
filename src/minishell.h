/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 16:30:16 by bsiche            #+#    #+#             */
/*   Updated: 2018/08/19 20:14:51 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>

typedef	struct	s_cmdline
{
	char	*str;
	char	*cmd;
	char	**tab;
	char	option;
	int		flag;
}				t_cmdline;

typedef struct	s_truedir
{
	char	*type;
	char	*path;
	char	*logic;
	char	*name;
}				t_truedir;

typedef struct	s_envalue
{
	char	*name;
	char	*value;
}				t_envalue;

t_lstcontainer	*ft_env_to_lst(char **env);
t_lstcontainer	*emptyenv(t_lstcontainer *env);
t_lstcontainer	*copyenv(t_lstcontainer *env);
int				ft_env(t_cmdline *cmdline, t_lstcontainer *env,
				t_lstcontainer *list);
void			ft_getcmd(t_cmdline *cmdline);
void			ft_add_env_string(t_lstcontainer *env, char *s1, char *s2);
char			**ft_copytab(char **tab);
void			ft_parseoption(t_cmdline *cmdline);
int				ft_isbuiltin(t_cmdline *cmdline, t_lstcontainer *env,
				t_lstcontainer *list);
int				ft_echo(t_lstcontainer *env, t_cmdline *cmdline);
void			ft_pwd(t_lstcontainer *env, t_cmdline *cmdline);
char			*ft_true_pwd();
int				ft_cd(t_cmdline *cmdline, t_lstcontainer *env);
int				ft_setenv(t_cmdline *cmdline, t_lstcontainer *env);
int				ft_unsetenv(t_lstcontainer *env, t_cmdline *cmdline);
void			ft_printab(char **tab);
int				ft_exec(t_lstcontainer *env, t_cmdline *cmdline);
char			*get_env_string(t_lstcontainer *env, char *str);
int				replace_env_str(t_lstcontainer *env, char *s1, char *s2);
char			*remove_env_string(t_lstcontainer *env, char *str);
int				getright(char *str);
int				ft_isdir(char *path);
char			*ft_usrmode(mode_t mode);
char			*ft_cdpath(t_lstcontainer *env, char *path);
void			ft_printlist(t_lstcontainer *env);
int				ft_ispair(char *str);
char			*getnewcmd(char **tab, int i);
void			free_envalue(t_lstcontainer *env);
void			cmdline_free(t_cmdline *cmdline);
void			ft_convert(t_lstcontainer *env, t_cmdline *cmdline);
char			*ft_dotdot(t_lstcontainer *new);
char			*ft_dot(char *path);
char			**init_envp(t_lstcontainer *env);
int				check_rights(char *path);
void			ft_error(int i, t_cmdline *cmdline);
char			*ft_homepath(char *path, t_lstcontainer *env);
int				ft_handlestat(struct stat *tmp, char *permission, char *path);
int				ft_isdir(char *path);
#endif
