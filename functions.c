/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <stribuzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 08:46:06 by stribuzi          #+#    #+#             */
/*   Updated: 2021/08/13 08:46:07 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_pipe(t_check *check, t_program *program)
{
	if (find_last_char(check->after_echo, '\"') != NULL)
	{
		if (ft_strchr(find_last_char(check->after_echo, '\"'), '|') == NULL)
		{
			if (redir_func(check->after_echo, program) == -1)
				return (-1);
		}
		else
			pipe_support(check, program);
	}
	else
		if (pipe_support_2(check, program) == -1)
			return (-1);
	return (1);
}

int	check_echo_supp(t_check *check, t_program *program, char *split)
{
	check->j = 0;
	check->after_echo = find_last_word(split, "echo");
	check->last_pos = find_last_pos_char(check->after_echo, '\"');
	while (check->after_echo[check->i])
	{
		check->buffer[check->j] = check->after_echo[check->i];
		if (check->i > check->last_pos)
		{
			if (check->after_echo[check->i] == '|')
				break ;
		}
		check->j++;
		check->i++;
	}
	check->buffer[check->j] = '\0';
	if (if_pipe(check, program) == -1)
		return (-1);
	return (1);
}

void	check_echo_supp_2(char *split, t_check *check, t_program *program)
{
	check->split_command = ft_split(split, '|');
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

int	check_echo(char *split, t_check *check, t_program *program)
{
	if (ft_strnstr(split, "echo", ft_strlen(split)) != NULL)
	{
		if (check_echo_supp(check, program, split) == -1)
			return (-1);
	}
	else if (ft_strchr(split, (int) '|') != NULL)
		check_echo_supp_2(split, check, program);
	else if (ft_strchr(split, (int) '<') != NULL
		&& ft_strchr(split, (int) '<')[1] == '<')
		handle_double_in(split, program);
	else if (ft_strchr(split, (int) '<') != NULL)
		handle_redirection_in(split, program);
	else if (ft_strchr(split, (int) '>') != NULL)
		handle_redirection_out(split, program);
	else
	{
		if (redir_func(split, program) == -1)
			return (-1);
	}
	return (1);
}

int	check_function(char *split, t_program *program)
{
	t_check	check;

	check.i = 0;
	if (check_echo(split, &check, program) == -1)
		return (-1);
	return (1);
}
