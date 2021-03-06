/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:32:09 by nmadi             #+#    #+#             */
/*   Updated: 2022/07/29 08:54:31 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_env_access(t_data *data)
{
	ft_putstr_fd("Error: cannot access parent directories. ", 2);
	ft_putstr_fd("Redirecting to root regardless of input.\n", 1);
	chdir("/");
	safe_free(data->old_pwd);
	if (data->pwd)
		data->old_pwd = ft_strdup(data->pwd);
	modify_env(ft_strdup("OLDPWD"), data->old_pwd, data);
	safe_free(data->pwd);
	data->pwd = ft_strdup("/");
	modify_env(ft_strdup("PWD"), ft_strdup("/"), data);
	data->last_exit_status = 0;
}

static int	handle_del_dir(t_data *data)
{
	char	*pwd;
	char	*old_pwd;

	pwd = NULL;
	old_pwd = NULL;
	if (data->old_pwd != NULL && chdir(data->old_pwd) != -1)
	{
		pwd = ft_strdup(data->pwd);
		old_pwd = ft_strdup(data->old_pwd);
		safe_free(data->pwd);
		safe_free(data->old_pwd);
		data->pwd = ft_strdup(old_pwd);
		data->old_pwd = ft_strdup(pwd);
	}
	else
		update_env_access(data);
	return (0);
}

static int	redirect_to_home(t_data *data)
{
	char	*cwd;
	char	*pwd;
	char	*destination;

	cwd = NULL;
	pwd = getcwd(cwd, sizeof(cwd));
	destination = get_env_value("HOME", data);
	if (chdir(destination) == -1)
	{
		ft_putstr_fd("Error: HOME not set\n", 2);
		safe_free(pwd);
		safe_free(cwd);
		safe_free(destination);
		return (1);
	}
	safe_free(pwd);
	safe_free(cwd);
	safe_free(destination);
	return (0);
}

static int	handle_input_types(char **args, char *pwd, t_data *data)
{
	if (!args[1])
		return (redirect_to_home(data));
	else if (args[1][0] == '/' && pwd[0] == '/' && !pwd[1])
		return (root_relative_chdir(args[1]));
	else if (args[1][0] == '/')
		return (full_chdir(args[1]));
	else
		return (relative_chdir(pwd, args[1]));
}

int	b_cd(char **args, t_data *data)
{
	char	*cwd;
	char	*pwd;
	int		rv;

	cwd = NULL;
	rv = 0;
	if (invalid_args_count(args, data))
	{
		free_2d(args);
		return (1);
	}
	pwd = getcwd(cwd, sizeof(cwd));
	if (!pwd)
		return (handle_del_dir(data));
	rv = handle_input_types(args, pwd, data);
	data->last_exit_status = rv;
	update_pwd_oldpwd(pwd, rv, data);
	safe_free(pwd);
	safe_free(cwd);
	return (rv);
}
