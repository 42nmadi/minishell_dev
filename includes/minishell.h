/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 22:34:51 by nmadi             #+#    #+#             */
/*   Updated: 2022/07/03 17:37:21 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include "../libs/readline/include/readline/readline.h"
# include "../libs/readline/include/readline/history.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>

typedef struct s_data
{
	int		last_exit_status;
	int		shlvl;
	char	*pwd;
	char	*old_pwd;
	char	**envp;
}	t_data;

typedef struct s_redirs
{
	char	*infile;
	char	*heredoc;
	char	*outfile;
	char	*append;
	char	lastin;
	char	lastout;
}	t_redirs;

typedef struct s_pipe
{
	char		*fcmd;
	int			nchild;
	t_redirs	rd;
	t_data		*data;
}	t_pipe;

# define DQUOTE 34
# define SQUOTE 39

//* Redirection
void	append(char *line);
void	close_fds(int *fd);
void	here_ops(char *line);
void	init_rd(t_redirs *rd);
void	empty_file(char *file);
void	process(char *line, t_redirs *rd);
void	file_parent(int *pid, t_data *data);
void	execute_rd(char *line, t_data *data);
void	create_file(char *line, t_redirs *rd, t_data *data);

//* General Execution
char	*read_line(char *lim);
int		is_parent_function(char **args);
char	*find_exec(char *prg, char	**paths);
char	*get_cmd_path(char **args, t_data *data);
void	master_execute(char *line, t_data *data);
int		exec_cmd_child(char **args, t_data *data);
void	exec_cmd_parent(char **args, t_data *data);

//* Pipes
void	pipes(t_pipe **p);
void	here_pipe(t_pipe *p);
int		count_pipes(char *line);
int		redir_in(t_pipe **p, int i);
int		redir_out(t_pipe **p, int i);
void	handle_pp(char *line, t_data *data);
void	last_child(char **arg, int **pipes, t_pipe **p);
void	first_child(char **arg, int **pipes, t_pipe **p);
void	create_process(char ***arg, int **pipes, t_pipe **p);
void	mid_child(int *i, char **arg, int **pipes, t_pipe **p);
void	parent(char ***arg, int **pipes, int *pids, t_pipe **p);

//* Error and free
void	err_print(int error, t_data *data);
void	err_free_parent(int **pipes, int *pids, int nchild);
void	no_err_free_parent(int **pipes, int *pids);
void	err_kill_process(t_pipe **p);
void	err_free_process(int **pipes, char ***args, int nchild);
void	safe_free(void *ptr);
void	free_2d_int(int **arr, int nchild);
void	free_2d(char **arr);
void	free_3d(char ***arr, int nchild);
void	free_struct_rd(t_redirs *rd);
void	free_struct_pp(t_pipe **p, int nchild);
void	ps_free(char ***arg, int **pipes, int *pids, t_pipe **p);
void	rd_free(int *fd, char **arg, t_redirs *rd);

//* Parsing Checkers
int		pc_end(char *line);
int		pc_chars(char *str);
int		pc_pipe(char *line);
int		pc_quotes(char *str);
int		pc_redirs(char *str);
int		pc_redir(char *line);
int		pc_export(char **args);
int		pc_mode(char *str, char mode);
int		pc_valid(char *str, t_data *data);

//* Parsing Extractors
char	**split_rd(char *str);
char	*find_cmd(char *input);
char	*rem_words(char *input);
char	*first_word(char *input);
char	**smart_split(char *str);
char	*set_cmd(char *s1, char *s2);
char	**pe_split_path(char *s, char c);
char	**split_pp(char const *s, char c);
char	**strip_quotes(char **elements, int element_count);

//* Builtins
int		b_pwd(t_data *data);
int		b_cd(char **args, t_data *data);
void	b_exit(char **args, t_data *data);
int		b_echo(char **args, t_data *data);
void	b_unset(char **args, t_data *data);
void	b_export(char **args, t_data *data);
int		b_env(char **envp, int export_mode);

//* Environment Variables
void	init_envp(char **envp, t_data *data);
char	*get_env_value(char *str, t_data *data);
int		env_exists(char *var_name, t_data *data);
void	delete_env(char *var_name, t_data *data);
char	**clone_env(char **envp, int extra_slot);
char	*get_export_value_side(char *str, int lhs);
void	modify_env(char *var_name, char *value, t_data *data);
void	append_env(char *var_name, char *value, t_data *data);

//* cd utils
int		full_chdir(char *new_path);
char	*join_paths(char *cwd, char *np);
int		root_relative_chdir(char *new_path);
int		relative_chdir(char *new_path, char *pwd);
int		invalid_args_count(char **args, t_data *data);

//* Signals
void	set_signalset(int sigmode);
void	handle_signals_main(int signum);
void	handle_signals_else(int signum);

//* Misc (Organize)
char	*cmd_copy(char *input);
int		check_space(char *str);
char	*ft_strjoin_and_free(char *s1, char const *s2);
int		word_count(char *input);
char	*line_update(void);

#endif