/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imran.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imran <imran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:32:39 by imran             #+#    #+#             */
/*   Updated: 2022/04/08 17:11:29 by imran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMRAN_H
# define IMRAN_H

# include "../central.h"
# include <stdio.h>

size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*find_exec(char *prg, char	**paths);
char	*cmd_path(char	*cmd);
void	execute(char *line);

#endif