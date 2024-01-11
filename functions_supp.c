/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_supp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <stribuzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 08:46:03 by stribuzi          #+#    #+#             */
/*   Updated: 2021/08/23 13:44:04 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	binaries_func(t_func *function, t_program *program, char *split)
{
	function->pid = fork();
	signal(SIGINT, sig_handler);
	if (function->pid == 0)
	{
		check_if_executable(function, split, program);
		function->ret = execute_binaries(&split[function->k], program);
		if (function->ret == 0)
		{
			perror(&split[function->k]);
			exit(127);
		}
		else if (function->ret == 2)
		{
			ft_putstr("Permission denied\n");
			exit(126);
		}
	}
	else
		wait(&g_global_status);
	return (0);
}

int	if_func(char *split, t_program *program, t_func *f)
{
	if (ft_strncmp(&split[f->k], "exit", f->len) == 0 && f->len == 4)
		return (-1);
	else if (ft_strncmp("echo", &split[f->k], f->len) == 0 && f->len == 4)
		echo_command(&split[f->k], program);
	else if (ft_strncmp(&split[f->k], "cd", f->len) == 0)
	{
		change_directory(&split[f->k + 2], program);
		return (1);
	}
	else if (ft_strncmp(&split[f->k], "env", f->len) == 0)
		ft_lstiter_new(program->global_variables);
	else if (ft_strncmp(&split[f->k], "echo", f->len) != 0
		&& ft_strchr(&split[f->k], (int) '=') != NULL)
		check_add_variable(&split[f->k], program);
	else if (ft_strncmp(&split[f->k], "unset", f->len) == 0 && f->len == 5)
		unset_variable(&split[f->k], program);
	else if (ft_strncmp(&split[f->k], "export", f->len) == 0 && f->len == 6)
		export_variable(&split[f->k], program);
	else if (ft_strncmp(&split[f->k], "clear", f->len) == 0 && f->len == 5)
		ft_putstr("\033[H\033[J");
	else if (ft_strncmp(&split[f->k], "pwd", f->len) == 0 && f->len == 3)
		ft_pwd();
	else
		binaries_func(f, program, split);
	return (1);
}

int	redir_func(char *split, t_program *program)
{
	t_func	function;

	function.len = 0;
	function.k = 0;
	while (is_space(split[function.k]) == 1)
		function.k++;
	while (is_space(split[function.k + function.len]) == 0
		&& split[function.k + function.len] != '\0')
		function.len++;
	if (if_func(split, program, &function) == -1)
		return (-1);
	return (0);
}

void	pipe_support(t_check *check, t_program *program)
{
	check->split_command = ft_split(find_last_char(check->after_echo, '\"'),
			'|');
	free(check->split_command[0]);
	check->split_command[0] = ft_strdup(check->buffer);
	loop_pipe(check->split_command, program);
	free_matrix(check->split_command);
}

int	pipe_support_2(t_check *check, t_program *program)
{
	if (ft_strchr(check->after_echo, (int) '|') != NULL)
	{
		check->split_command = ft_split(check->after_echo, '|');
		loop_pipe(check->split_command, program);
		check->j = 0;
		while (check->split_command[check->j])
		{
			free(check->split_command[check->j]);
			check->j++;
		}
		if (check->split_command)
			free(check->split_command);
	}
	else if (ft_strchr(check->after_echo, (int) '|') != NULL)
	{
		handle_redirection_out(check->after_echo, program);
	}
	else if (redir_func(check->after_echo, program) == -1)
		return (-1);
	return (1);
}
