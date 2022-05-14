/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 19:46:57 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/14 18:17:12 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Count the number of pipe characters in the line
*/
int	count_pipes(char *line)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '|')
			p++;
		i++;
	}
	return (p);
}

char	*redir_cpy(char *input)
{
	int		i;
	char	*copy;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '<' || input[i] == '>')
			break ;
		i++;
	}
	copy = ft_substr(input, i, ft_strlen(input));
	return (copy);
}

char	*cmd_copy(char *input)
{
	int		i;
	int		j;
	int		size;
	char	*copy;

	i = 0;
	j = 0;
	size = 0;
	while (input[i] && input[i] != '<' && input[i] != '>')
	{
		size++;
		i++;
	}
	copy = (char *) malloc(sizeof(char) * (size + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (input[i] && input[i] != '<' && input[i] != '>')
		copy[j++] = input[i++];
	copy[j] = '\0';
	return (copy);
}

void	split_pipe(char *line, t_data *data)
{
	char	**cmd;
	t_pipe	**p;
	int		i;
	int		c;

	i = 0;
	c = count_pipes(line) + 1;
	p = malloc(sizeof(t_pipe *) * c);
	cmd = ft_split(line, '|');
	while (cmd[i])
	{
		cmd[i] = ft_strtrim(cmd[i], " ");
		p[i] = malloc(sizeof(t_pipe));
		process(cmd[i], &p[i]->rd);
		p[i]->fcmd = cmd_copy(cmd[i]);
		p[i]->data = data;
		// printf("cmd(%d): %s\n", i, cmd[i]);
		i++;
	}
	pipes(line, p);
}

void	split_rd(char *line, t_data *data)
{
	t_redirs	*rd;
	char		*cmd;
	char		*ln;

	rd = malloc(sizeof(t_redirs));
	if (line[0] == '<' || line[0] == '>')
		cmd = find_cmd(line);
	else
		cmd = cmd_copy(line);
	ln = redir_cpy(line);
	if (multi_cmd_redir(line))
		split_multi_cmd_redir(ft_split_rd(line), rd, data);
	else
	{
		process(ln, rd);
		create_file(cmd, rd, data);
	}
}
