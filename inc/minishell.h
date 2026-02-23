/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:21:02 by htharrau          #+#    #+#             */
/*   Updated: 2024/10/16 12:45:30 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> 	// printf, perror
# include <stdlib.h> 	// malloc, free, exit, getenv
# include <string.h> 	// strerror
# include <unistd.h> 	// access, read, write, close, fork, exec, pipe, getcwd,
# include <readline/readline.h> // For readline
# include <readline/history.h>  // For add_history
# include <fcntl.h>		// open, O_RDONLY, O_WRONLY
# include <signal.h>	// signal, sigaction
# include <stdbool.h>	// for bool
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <errno.h>
# include "../libft/libft.h"

# define NO_ERROR 0
# define GENERAL_ERROR 1
# define SHELL_BUILTIN_ERROR 2
# define MEMORY_ALLOCATION_ERROR 3
# define NO_TOKEN 4
# define CANNOT_EXECUTE_CMD 126
# define COMMAND_NOT_FOUND_ 127

typedef enum e_redir_type
{
	NO_REDIR = 0,
	REDIR_IN = 1,
	REDIR_OUT = 2,
	REDIR_APPEND = 3,
	REDIR_HEREDOC = 4
}		t_redir_type;

typedef enum e_tok_type
{
	TOKEN_INVALID,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_SINGLE_Q,
	TOKEN_DOUBLE_Q,
	FILE_REDIR_IN,
	FILE_REDIR_OUT,
	FILE_APPEND,
	HEREDOC_DLM
}		t_tok_type;

typedef struct s_redir
{
	t_redir_type	redir_type;
	char			*file;
	char			*heredoc_dlm;
}		t_redir;

typedef struct s_xnode
{
	char			**argv;
	t_redir			**redir;
	struct s_xnode	*prev;
	struct s_xnode	*next;
}		t_xnode;

typedef struct s_token
{
	t_tok_type	type;
	char		*value;
	int			length;
	int			start;
	int			end;
	bool		expandable;
	bool		comb_prev;
	bool		retoken;
}		t_token;

typedef struct s_state
{
	char	*input_string;
	t_token	**tokens;
	int		token_count;
}		t_state;

typedef struct s_shell
{
	unsigned int	last_exit_code;
	char			**env;
	t_state			*state;
	t_xnode			*cmd_tree;
}		t_shell;

/****************************/
/*			MAIN			*/
/****************************/
/* SIGNALS LOOP */
int		init_shell(t_shell *shell, char **envp);
int		setup_signals_interactive(void);
void	disable_ctrl_backslash_echo(void);
void	enable_ctrl_backslash_echo(void);

/* CLEAN UP */
void	cleanup_shell(t_shell *shell);
void	cleanup_cmd_tree(t_xnode **node);
void	cleanup_node(t_xnode *node);
void	free_redir(t_redir *redir);
void	cleanup_env(char **env);
void	cleanup_state(t_state *state);
void	cleanup_tokens(t_state *state);

/****************************/
/*			PARSING			*/
/****************************/

typedef struct s_helpr {
	t_tok_type	type;
	int			step;
}		t_helpr;

typedef struct s_expand
{
	int		start;
	int		end;
	char	*envar_name;
	char	*env_val;
}	t_expand;

typedef struct s_retoken
{
	t_token	**new_tok;
	int		*j;
	t_token	*old_tok;
	char	**split;
}		t_retoken;

int		parse(char *input, t_shell *shell);
void	reset_shell_state(t_shell *shell);

/* TOKENISATIION */
int		tokenize(t_shell *shell, int max_token);
t_helpr	identify_operator(char *current);
t_token	*putval_q(char *start, char *end, t_state *state, t_tok_type t_type);
t_token	*putval_nq(char *start, char *end, t_state *state, t_tok_type t_type);
int		increase_tok_capacity(t_shell *shell, int *max_tok);

/* EXPANSION */
int		expand(t_shell *shell);
char	*expand_string(char *value, t_shell *shell);
char	*get_env_name(char *value, int dollar_int);
char	*get_env_value(char *env_val, t_shell *shell);
char	*alloc_newvalue(char *value, t_expand *expansion, int n_exp);
void	free_expansion(t_expand **expansion, int n_exp);
int		inc_exp_capacity(t_expand **exp, int *max_exp);

/* DELETE EMPTY TOKENS (excepts quoted)*/
int		delete_empty(t_shell *sell);

/* RETOKEN (SPLITTING) */
int		retoken(t_shell *shell);
int		count_elts(char *s);
void	free_split(char **split, int i);
int		assign_values(t_retoken *tok_d, int k);

/* COMBINATION */
int		combine(t_shell *shell);

/* GRAMMAR */
int		grammar(t_shell *shell);

/* COMMANDS */
int		command(t_shell *shell);
int		put_arg_redir(t_state *state, t_xnode *node, int start, int *i);

/* HEREDOCS */
void	heredoc(t_shell *shell);
int		setup_signals_heredoc(void);
int		expand_heredoc(t_redir *redir, t_shell *s);
bool	is_heredoc(t_xnode *nodes);
int		inc_hd_capacity(char ***lines, int max_lines, int count);

/* FT_IS */
bool	ft_isspace(char c);
bool	ft_isops(char c);
bool	ft_isquotes(char c);
bool	ft_is_comb(t_token *token);
bool	ft_is_valid_exp(char *value, int i, bool start);

/****************************/
/*			EXECUTE			*/
/****************************/

void	execute(t_shell *ms);

int		exec_builtin(t_xnode *node, t_shell *ms);
int		execute_child(t_xnode *node, t_shell *ms, int last_fd_r, int fd[2]);
int		set_redirections(t_xnode *node);
int		is_builtin(t_xnode *node);
char	*get_cmd_path(t_xnode *node);
void	free_array(char **array);
int		get_array_size(char **arr);
void	set_signals_to_default(void);
void	set_signals_to_ignore(void);
int		get_exit_code(int status);

int		ft_cd(char **arg, char ***env);
int		ft_exit(t_shell *ms, t_xnode *node);
int		ft_echo(char **argv);
int		ft_env(char **env);
int		ft_export(char **arg, char ***env);
int		ft_pwd(void);
int		ft_unset(char **argv, char ***env);

void	memory_failure(void);
int		does_variable_exist(char *arg, char **env);
char	*get_var_name(char *arg);

#endif