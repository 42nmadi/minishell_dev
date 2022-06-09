/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_struct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:59:12 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/09 17:48:01 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_struct_rd(t_redirs *rd)
{
	safe_free(rd->infile);
	safe_free(rd->outfile);
	safe_free(rd->heredoc);
	safe_free(rd->append);
	safe_free(rd);
}

void	free_struct_ps(t_pipe **p, int nchild)
{
	int	i;

	i = 0;
	while (i < nchild)
	{
		safe_free(p[i]->fcmd);
		safe_free(p[i]->rd.infile);
		safe_free(p[i]->rd.outfile);
		safe_free(p[i]->rd.heredoc);
		safe_free(p[i]->rd.append);
		safe_free(p[i]);
		i++;
	}
	free(p);
	p = NULL;
}

void	ps_free(char ***arg, int **pipes, int *pids, t_pipe **p)
{
	free_3d(arg, p[0]->nchild);
	free_2d_int(pipes, p[0]->nchild);
	safe_free(pids);
	free_struct_ps(p, p[0]->nchild);
}

void	rd_free(int *fd, char **arg, t_redirs *rd)
{
	close_fds(fd);
	safe_free(fd);
	free_2d(arg);
	free_struct_rd(rd);
}
