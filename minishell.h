/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <stribuzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 08:46:16 by stribuzi          #+#    #+#             */
/*   Updated: 2021/08/23 13:14:33 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <termios.h>
# include <signal.h>
# include <stdio.h>
# include <sys/errno.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "utils/libft.h"

typedef struct s_program
{
	t_list		*local_variables;
	t_list		*global_variables;
	t_list		*history;
	t_list		*history_prec;
	char		**path;
	int			h_index;
	int			status;
}				t_program;

typedef struct s_echo
{
	pid_t	pid;
	int		i;
	int		k;
	int		newline_flag;
	char	**split;
	int		matrix_size;
}				t_echo;

typedef struct s_pipe
{
	int		pipefd[2];
	pid_t	pid;
	int		fd_in;
}				t_pipe;

typedef struct s_variable
{
	int			i;
	int			error;
	t_list		*support;
	t_list		*support_2;
	char		first[500];
	char		second[500];
	char		*new_content_1;
	char		*new_content_2;
	int			k;
}				t_variable;

typedef struct s_redir_out
{
	char	*found_out;
	pid_t	pid;
	int		out;
	int		fd;
	int		i;
	char	**split_ang;
	int		matrix_size;
	char	**split_name;

}				t_redir_out;

typedef struct s_redir_in
{
	int		ret;
	int		k;
	pid_t	pid;
	char	support[500];
	int		i;
	int		j;
	char	*found_in;
	int		l;
	int		fd_zero;
}				t_redir_in;

typedef struct s_double_in
{
	char	*line;
	int		i;
	int		k;
	char	to_check[500];
	char	to_execute[500];
	char	*final_command;
	char	**split_func;
	pid_t	pid;
	int		fd;

}				t_double_in;

typedef struct s_func
{
	int		k;
	int		len;
	int		ret;
	pid_t	pid;
}				t_func;

typedef struct s_check
{
	int		i;
	int		k;
	char	buffer[1024];
	int		ret;
	char	**split_command;
	int		j;
	char	*after_echo;
	int		last_pos;
}				t_check;

typedef struct s_unset
{
	int		i;
	t_list	*temp;
	t_list	*prev;
	char	**split;
}				t_unset;

int			g_global_status;
int			ft_strcmp(char *s1, char *s2);
int			execute_binaries(char *str, t_program *program);
int			terminal_init(void);
void		terminal_signal(int signum);
void		terminal_done(void);
void		ft_putstr(char *s);
int			is_space(char c);
void		echo_command(char *to_print, t_program *program);
int			clean_string(char *to_print);
void		handle_redirection_in(char *split, t_program *program);
void		handle_redirection_out(char *split, t_program *program);
void		check_add_variable(char *s, t_program *program);
int			redir_func(char *split, t_program *program);
void		export_variable(char *s, t_program *program);
int			only_spaces(char *s);
int			check_function(char *split, t_program *program);
void		free_matrix(char **to_free);
void		search_variable_right(char *str, t_program *program);
void		change_directory(char *dir, t_program *program);
void		loop_pipe(char **cmd, t_program *program);
size_t		ft_strlen(const char *s);
char		*ft_strchr(const char *s, int c);
void		ft_lstiter_new(t_list *lst);
int			redir_func(char *split, t_program *program);
int			check_function(char *split, t_program *program);
void		ft_pwd(void);
void		unset_variable(char *s, t_program *program);
char		*find_last_word(char *haystack, char *needle);
void		handle_double_in(char *split, t_program *program);
int			find_last_pos_char(char *s, char c);
char		*find_last_char(char *s, char c);
int			redir_func(char *split, t_program *program);
void		pipe_support(t_check *check, t_program *program);
int			pipe_support_2(t_check *check, t_program *program);
void		unset_variable(char *s, t_program *program);
int			execute_binaries(char *str, t_program *program);
char		*find_last_char(char *s, char c);
int			find_last_pos_char(char *s, char c);
char		*find_last_word(char *haystack, char *needle);
void		ft_pwd(void);
void		change_status_value(t_list *to_change, int value);
void		change_path_value(t_program *program);
t_list		*get_envp(char **envp);
void		free_prog(t_program *program);
int			take_input(char *str);
void		sig_handler(int status);
void		check_if_executable(t_func *function, char *split,
				t_program *program);

#endif