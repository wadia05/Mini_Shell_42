/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 01:25:27 by med-dahr          #+#    #+#             */
/*   Updated: 2024/09/05 02:34:14 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft_42/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
// #include <limits.h> //use for macro of PATH_SIZE
# include <readline/history.h>
# include <readline/readline.h>

# define BUFFER_SIZE 4096

# define TMP_FD "/tmp/.file"
# define RED "\x1B[31m"
# define YAW "\x1B[33m"
# define RS "\x1B[0m"

extern int				g_exit_status;

typedef enum s_token_type{
	T_COMMEND,
	T_WORD,
	T_S_QUOTE,
	T_PIPE,
	T_DLESS,
	T_LESS,
	T_DGREAT,
	T_GREAT
}						t_TokenType;

typedef struct s_token
{
	t_TokenType			type;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_parse_vars
{
	int					i;
	char				*token_start;
	t_token				*tkn;
	int					in_quotes;
	char				quote_char;
}						t_parse_vars;

typedef struct s_env
{
	int					status;
	char				*full;
	char				*env_name;
	char				*env_data;
	struct s_env		*next;

}						t_env;

typedef struct s_vars
{
	char				*result;
	char				*temp;
	int					i;
	int					single;
	int					dble;
}						t_vars;

typedef struct s_cammand
{
	char				**args;
	t_TokenType			type;
	char				*input_file;

	struct s_cammand	*next;
}						t_cammand;

typedef struct s_command_context
{
	t_cammand			*current_cmd;
	t_cammand			*head_cmd;
	t_cammand			*final_cmd;
	int					idx;
}						t_command_context;
typedef struct s_globale
{
	t_env				*my_en;
	t_cammand			*commands;
	t_cammand			*parsed_commands;
	t_cammand			*cmd_iter;
	char				*line;
	char				*s_line;
	int					n_pipe;
	int					in_fd;
	int					out_fd;
	pid_t				pid;
}						t_globale;
// parsing

t_cammand				*process_pipe_tokens(t_token **tokens,
							t_command_context *ctx);
int						find_cote(char *value);
void					finalize_commands(t_cammand **current_cmd,
							t_cammand **final_cmd, t_cammand **head_cmd,
							int *idx);
void					process_operator_token(t_token **tokens,
							t_command_context *ctx);
void					process_argument_token(t_token **tokens,
							t_cammand **final_cmd, t_cammand **head_cmd,
							int *idx);
void					print_error(char *cmd, char *arg, char *msg);
void					free_commands(t_cammand *cmds);
void					advance_to_next_token(t_token **tokens);
t_cammand				*create_pipe_command(t_cammand **current_cmd,
							t_cammand **head_cmd);
void					handle_quotes(char *line, t_parse_vars *vars);
void					handle_token_creation(char *line, t_parse_vars *vars,
							t_env *my_en);
void					handle_operator(char *line, t_parse_vars *vars,
							t_env *my_en);
void					handle_final_token(char *line, t_parse_vars *vars,
							t_env *my_en);

t_token					*allocate_new_token(void);
char					*process_dollar_sign(char *line, t_env *env,
							t_vars *vars);
t_cammand				*finalize_current_command(t_cammand **current_cmd,
							t_cammand **head_cmd, t_cammand **final_cmd,
							int *idx);
void					init_var(t_globale *gbl, char **env);
void					free_tokens(t_parse_vars *vars);
char					*handle_dollar_sign(char *line, int *i, t_env *env,
							char *result);
char					*append_char(char *result, char c);
t_cammand				*validate_next_token(t_token **tokens);
t_cammand				*handle_heredocs(t_token **tokens,
							t_cammand **current_cmd, t_cammand **head_cmd);
t_cammand				*create_new_command(void);
t_cammand				*handle_pipes(t_token **tokens, t_command_context *ctx);
t_cammand				*convert_tokens_to_commands(t_token *tokens);
t_cammand				*handle_redirections(t_token **tokens,
							t_command_context *ctx);
t_cammand				*parsing(char *line, t_env *my_en);
t_token					*tokencreate(char *value, t_token *head, t_env *env);
char					*process_variable(char *line, int *i, t_env *env,
							char *result);
char					*var_in_line(char *line, t_env *env);

/*
	execution fonctionsF
*/
void					exit_shell(t_globale *gbl);
void					free_env(t_globale *gbl);
t_env					*init_env_node(char *name, char *value);
int						print_env_sorted(t_env *env);
void					add_or_update_env(t_env **env, char *name, char *value);
int						handle_child_status(int status);
void					handle_parent_process(int pid);
void					setup_heredoc_child_signals(void);
void					process_heredoc(char *end_str, t_env *env,
							char *name_file);
void					execute_relative_path_or_builtins(t_cammand *cmd,
							char **arry_env, t_env **my_en);
void					free_array(char ***arr);
void					process_all_heredocs(t_cammand *cmd, t_env *env);
int						execute_pipeline(t_globale *gbl);
void					apply_redirection(t_cammand *cmd, t_globale *gbl);
t_cammand				*move_to_next_command(t_globale *gbl, int i,
							int **pipes);
int						wait_for_parnt_babys(t_globale *gbl);
void					*init_pipe_check_build(t_globale *gbl, int **pipes);
void					i_am_the_baby(t_globale *gbl, int i, int **pipes);
void					execute_command(t_globale *gbl, int in_fd, int out_fd);
char					*find_executable(t_env *my_en, char *cmd);
char					**convert_env_to_array(t_env *env);
int						cont_pipe(t_cammand *cmd);
void					creat_pipe_line(t_globale *gbl, int ***pipes);
void					launch_cmd(t_globale *gbl, int **pipes);

// sig

void					setup_signals(void);
void					setup_child_signals(void);
void					restore_signal_handlers(void);
void					temporarily_ignore_signals(void);
int						empty(char **line);
char					*get_name(char *name);
char					*error_check(char *name, t_env *env,
							char *error_message);
void					update_env(t_env *env, char *new_value, char *name);
void					update_environment_variables(char *old_path,
							t_env *env);
// int						handle_too_many_arguments(char **name_dir);

int						builtins(char **command, t_env **my_en);
void					my_pwd(void);
void					my_echo(char **args);
t_env					*export(char **varible, t_env **env);
t_env					*creat_env(char *env, t_env *add_to_list);
void					my_cd(char **name_dir, t_env *env);
t_env					*my_env(char **env);
t_env					*my_unset(char **name, t_env **env);
char					*find_path(char *name, t_env *env);
char					*get_name_of_var(char *name);
char					*ft_strndup(const char *s1, char size);
char					*get_data_of_var(char *data);
void					envarment(t_env *env);
int						my_exit(char **args);

#endif