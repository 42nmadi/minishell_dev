/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:25:02 by imran             #+#    #+#             */
/*   Updated: 2022/04/21 02:17:47 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Using readline library to create shell command-line
** and executing the commands through user input
*/
int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("$> ");
		if (!line)
			break ;
		if (line[0])
		{
			add_history(line);
			if (is_valid_input(line))
			{
				if (ft_strchr(line, '|'))
					pipes(line);
				else
					execute(line);
			}
		}
		free(line);
	}
}
