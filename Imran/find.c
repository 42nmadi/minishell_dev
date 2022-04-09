/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imran <imran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:06:27 by imran             #+#    #+#             */
/*   Updated: 2022/04/09 19:38:47 by imran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "imran.h"

/*
** returns the PATH variable from the environment
*/
char	*get_path(void)
{
	extern char			**environ;
	int					i;
	unsigned long		j;
	char				*find;

	i = 0;
	j = 0;
	find = "PATH";
	while (environ[i] != NULL)
	{
		j = 0;
		while (environ[i][j] == find[j])
		{
			if (j == ft_strlen(find) - 1)
				return (environ[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
/*
** Splits the PATH variable by delimiter and returns paths 
*/
char	**split_path(char *path)
{
	char	**strs;
	char	*newpath;
	int		fwd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	fwd = 5;
	newpath = &path[fwd];
	strs = ft_split(newpath, ':');
	while (strs[i])
	{
		j = ft_strlen(strs[i]);
		strs[i][j] = '/';
		strs[i][j + 1] = '\0';
		i++;
	}
	return (strs);
}

/*
** checks if the command exists by going through different paths
** specified in the environment
*/
char	*find_exec(char *prg, char	**paths)
{
	int		i;
	char	*find;

	i = 0;
	while (paths[i])
	{
		find = ft_strjoin(paths[i], prg);
		if (access(find, X_OK) == 0)
		{
			ft_free_arg(paths);
			return (find);
		}
		i++;
	}
	return (NULL);
}
/*
** culmination of previous functions to return command path
*/
char	*cmd_path(char	*cmd)
{
	char	*path;
	char	**paths;
	char	*output;

	path = get_path();
	paths = split_path(path);
	output = find_exec(cmd, paths);
	if (!output)
	{
		perror("command not found");
		exit(127);
	}
	return (output);
}