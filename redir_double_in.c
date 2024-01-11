/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_double_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <stribuzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 08:46:49 by stribuzi          #+#    #+#             */
/*   Updated: 2021/08/13 09:09:07 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_double_1(char *split, t_double_in *double_struct)
{
	double_struct->k = 0;
	double_struct->i = 0;
	while (is_space(split[double_struct->i]) == 1)
		double_struct->i++;
	while (split[double_struct->i] != '<')
	{
		double_struct->to_execute[double_struct->k] = split[double_struct->i];
		double_struct->i++;
		double_struct->k++;
	}
	double_struct->to_execute[double_struct->k] = '\0';
	double_struct->i += 2;
	while (is_space(split[double_struct->i]) == 1)
		double_struct->i++;
	double_struct->k = 0;
	while (is_space(split[double_struct->i]) == 0
		&& split[double_struct->i] != '\0')
	{
		double_struct->to_check[double_struct->k] = split[double_struct->i];
		double_struct->i++;
		double_struct->k++;
	}
	double_struct->to_check[double_struct->k] = '\0';
	double_struct->fd = open(".h", O_CREAT | O_RDWR, 0666);
}

void	handle_double_2(t_double_in *d_s, t_program *program)
{
	d_s->line = readline("> ");
	write(d_s->fd, d_s->line,
		ft_strlen(d_s->line));
	write(d_s->fd, "\n", 1);
	while (ft_strcmp(d_s->line, d_s->to_check) != 0)
	{
		if (d_s->line)
			free(d_s->line);
		d_s->line = readline("> ");
		if (ft_strcmp(d_s->line, d_s->to_check) == 0)
			break ;
		write(d_s->fd, d_s->line, ft_strlen(d_s->line));
		write(d_s->fd, "\n", 1);
	}
	if (d_s->line)
		free(d_s->line);
	if (ft_strncmp(d_s->to_execute, "wc", 2) == 0)
		d_s->final_command = ft_strdup("wc < .h");
	else
		d_s->final_command = ft_strjoin(d_s->to_execute, " .h");
	check_function(d_s->final_command, program);
	write(d_s->fd, " ", 1);
	free(d_s->final_command);
	redir_func("rm .h", program);
	exit(EXIT_SUCCESS);
}

void	handle_double_in(char *split, t_program *program)
{
	t_double_in	double_struct;

	handle_double_1(split, &double_struct);
	if (double_struct.fd < 0)
	{
		ft_putstr("Error opening file!\n");
		return ;
	}
	double_struct.pid = fork();
	if (double_struct.pid == 0)
		handle_double_2(&double_struct, program);
	else
		wait(&g_global_status);
	close(double_struct.fd);
}
