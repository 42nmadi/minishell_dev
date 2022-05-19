/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:43:09 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/11 18:01:39 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_cmd_child(char **args, t_data *data)
{
	if (!ft_strncmp(args[0], "echo", ft_strlen(args[0])))
	{
		b_echo(args, data);
		kill(getpid(), 9);
	}
	else if (!ft_strncmp(args[0], "pwd", ft_strlen(args[0])))
	{
		b_pwd();
		ft_free_arg(args);
		kill(getpid(), 9);
	}
	else if (!ft_strncmp(args[0], "env", 3))
	{
		b_env(data->envp, 0);
		kill(getpid(), 9);
	}
	else if (execve(cmd_path(args[0], data), args, data->envp) == -1)
		return (-1);
	//! Add an if-statement here that checks if the first command
	//! is the minishell exec so that I increment SHLVL then pass the envp to the execve
	return (0);
}