/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:25:02 by imustafa          #+#    #+#             */
/*   Updated: 2022/07/03 17:36:28 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_line(char *line, t_data *data)
{
	int	len;

	set_signalset(1);
	len = ft_strlen(line) - 1;
	if (line[len] == '|')
		line = ft_strjoin_and_free(line, line_update());
	if (pc_mode(line, 'p'))
		handle_pp(line, data);
	else if (pc_mode(line, 'r'))
		execute_rd(line, data);
	else
		master_execute(line, data);
}

void	minishell(t_data *data)
{
	char	*line;

	while (isatty(STDIN_FILENO))
	{
		set_signalset(0);
		line = readline("$> ");
		if (!line)
		{
			free_2d(data->envp);
			break ;
		}
		if (line[0])
		{
			add_history(line);
			if (pc_valid(line, data))
				execute_line(line, data);
		}
		safe_free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void) argc;
	(void) argv;
	data = malloc(sizeof(t_data));
	init_envp(envp, data);
	data->pwd = NULL;
	data->old_pwd = NULL;
	minishell(data);
}
