/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:25:02 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/11 16:03:59 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Using readline library to create shell command-line
** and executing the commands through user input
*/

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	data;

	(void) argc;
	(void) argv;
	data.envp = envp;
	in_minishell_var(1);
	while (isatty(STDIN_FILENO))
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &handle_signals);
		line = readline("$> ");
		if (!line)
			break ;
		if (line[0])
		{
			add_history(line);
			// line = ft_strtrim(line, "\n ");
			if (preliminary_check(line))
			{
				if (ft_strchr(line, '|'))
					split_pipe(line, &data);
				else if (ft_strchr(line, '<') || ft_strchr(line, '>'))
					split_rd(line, &data);
				else
					master_execute(line, &data);
			}
		}
		in_minishell_var(1);
		free(line);
	}
}
