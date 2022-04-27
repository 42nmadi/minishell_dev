/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 00:43:58 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/25 20:57:28 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Handles SIGINT signals by redisplaying the prompt.
*/
void	handle_signals(int signum)
{
	(void) signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	if (in_minishell_var(-1) == 1)
		rl_redisplay();
}

/*
** The static int is treated as a global variable.
** To retrieve its value, one must pass -1.
*/
int	in_minishell_var(int is_true)
{
	static int in_minishell;

	if (is_true != -1)
		in_minishell = is_true;
	return (in_minishell);
}