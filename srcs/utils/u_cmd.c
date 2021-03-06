/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:59:33 by nmadi             #+#    #+#             */
/*   Updated: 2022/07/28 12:49:24 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**split_path(char *path)
{
	int		i;
	int		j;
	char	**paths;

	i = 0;
	j = 0;
	paths = pe_split_path(&path[5], ':');
	while (paths[i])
	{
		j = ft_strlen(paths[i]);
		paths[i][j] = '/';
		paths[i][j + 1] = '\0';
		i++;
	}
	return (paths);
}

char	*find_exec(char *cmd, char **paths)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], cmd);
		if (!access(full_path, F_OK))
		{
			free_2d(paths);
			return (full_path);
		}
		safe_free(full_path);
		i++;
	}
	free_2d(paths);
	return (NULL);
}

char	*validate_cmd(char *cmd, char **args, t_data *data)
{
	if (access(cmd, F_OK) == -1)
	{
		ft_putstr_fd("Error: command not found\n", 2);
		data->last_exit_status = 127;
		free_2d(args);
		exit (127);
	}
	else if (access(cmd, X_OK) == -1)
	{
		ft_putstr_fd("Error: no permission to execute this command\n", 2);
		data->last_exit_status = 126;
		free_2d(args);
		safe_free(cmd);
		exit (126);
	}
	return (cmd);
}

//! Change this to accept only one string containing the cmd
char	*get_cmd_path(char **args, t_data *data)
{
	char	*path_env_val;
	char	**paths;
	char	*cmd;

	if (ft_strchr(args[0], '/'))
		return (args[0]);
	path_env_val = get_env_value("PATH", data);
	if (!path_env_val)
		return (NULL);
	paths = split_path(path_env_val);
	if (!paths)
		return (NULL);
	cmd = find_exec(args[0], paths);
	return (validate_cmd(cmd, args, data));
}
