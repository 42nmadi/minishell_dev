/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:43:09 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/07 17:16:52 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *str)
{
	if (!ft_strncmp(str, "exit", ft_strlen(str)))
		return (1); //? 1 is exit
	else if (!ft_strncmp(str, "echo", ft_strlen(str)))
		return (2); //? 2 is echo
	else if (!ft_strncmp(str, "cd", ft_strlen(str)))
		return (3); //? 3 is cd
	else if (!ft_strncmp(str, "pwd", ft_strlen(str)))
		return (4); //? 4 is pwd
	else if (!ft_strncmp(str, "export", ft_strlen(str)))
		return (5); //? 5 is export
	else if (!ft_strncmp(str, "unset", ft_strlen(str)))
		return (6); //? 6 is unset
	else if (!ft_strncmp(str, "env", ft_strlen(str)))
		return (7); //? 7 is env
	return (0);
}

int	exec_cmd(char **args, char **envp)
{
	if (is_builtin(args[0]) == 1)
		exit(0); //! I want it to exit the parent process. Help!
	else if (is_builtin(args[0]) == 2)
		b_echo(args);
	else if (is_builtin(args[0]) == 3)
		b_cd(args[1]);
	else if (is_builtin(args[0]) == 4)
		b_pwd();
	else if (is_builtin(args[0]) == 5)
		; //? export
	else if (is_builtin(args[0]) == 6)
		; //? unset
	else if (is_builtin(args[0]) == 7)
		; //? env
	else if (execve(cmd_path(args[0]), args, envp) == -1)
		err_print(127);
	return (0);
}