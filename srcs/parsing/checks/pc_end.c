/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:14:37 by nmadi             #+#    #+#             */
/*   Updated: 2022/07/03 17:36:56 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	error(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (1);
}

int	pc_end(char *line)
{
	int	len;

	len = ft_strlen(line) - 1;
	while (ft_isspace(line[len]))
		len--;
	if (line[0] == '|')
		return (error("Error: First character must not be a pipe symbol.\n"));
	else if (line[len] == '>' || line[len] == '<')
		return (error("Error: Last character must not be a redirection symbol.\n"));
	return (0);
}
