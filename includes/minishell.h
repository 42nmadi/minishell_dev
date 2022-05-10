/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 22:34:51 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/10 19:35:17 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../includes/all_includes.h"
# include "../libs/libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <unistd.h>

typedef struct s_data
{
	int		last_exit_status;
	char	**envp;
} t_data;

typedef struct s_redirs
{
	char	*infile;
	char	*outfile;
	char	*append;
	char	*heredoc;
} t_redirs;

typedef struct s_pipe
{
	char		*fcmd;
	t_redirs		rd;
	void		*prev;
	void		*next;
} t_pipe;

# define DQUOTE 34
# define SQUOTE 39

char	*find_exec(char *prg, char	**paths);
char	*cmd_path(char	*cmd);
void	ft_free_arg(char **arr);
void	pipes(char *line);
void	execute(char *line);
void	err_print(int error);
void	err_free_parent(int **pipes, int *pids);
void	err_free_pipex(int **pipes, char ***args);
void	ft_free(int **arr);
void	ft_free_arg(char **arr);
void	ft_free_args(char ***arr);
char	**chars_split(char *str, char *charset);
void	here_ops(char *line);
void	file(char *line);
void	append(char *line);
char	**ft_split_path(char *s, char c);
char	*expand_env(char *str);
int		exec_cmd(char **args, char **envp);

//* Parsing
int		preliminary_check(char *str);
int		p_contains_unclosed_quotes(char *str);
int		p_is_empty_input(char *str);
int		p_contains_illegal_special_chars(char *str);
int		p_contains_invalid_redirs(char *str);

//* Signals
void	handle_signals(int signum);
int		in_minishell_var(int is_true);

//* Builtins
int		b_env(t_data *data);
int		b_pwd(void);
int		b_cd(char *new_path);
int		b_echo(char **args);

//* EV functions
char	*get_env_value(char *str, char **envp);
int		env_exists(char *var_name, char **envp);

#endif