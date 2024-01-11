/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <stribuzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 08:46:53 by stribuzi          #+#    #+#             */
/*   Updated: 2021/08/23 13:14:02 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_in_1(char *split, t_redir_in *redir_in, t_program *program)
{
	redir_in->found_in = ft_strchr(split, (int) '<');
	if (redir_in->found_in != NULL)
	{
		redir_in->l = 1;
		while (is_space(redir_in->found_in[redir_in->l]) == 1)
			redir_in->l++;
		redir_in->fd_zero = open(&redir_in->found_in[redir_in->l], O_RDONLY);
		if (redir_in->fd_zero < 0)
		{
			perror(&redir_in->found_in[redir_in->l]);
			exit(errno);
		}
		dup2(redir_in->fd_zero, STDIN_FILENO);
		close(redir_in->fd_zero);
	}
	if (!only_spaces(redir_in->support))
		redir_func(redir_in->support, program);
	exit(EXIT_SUCCESS);
}

void	handle_redirection_in(char *split, t_program *program)
{
	t_redir_in	redir_in;

	redir_in.k = 0;
	while (is_space(split[redir_in.k]) == 1)
		redir_in.k++;
	redir_in.j = 0;
	redir_in.i = 0;
	while (split[redir_in.k + redir_in.i] != '<')
	{
		redir_in.support[redir_in.k] = split[redir_in.k + redir_in.i];
		redir_in.k++;
	}
	redir_in.support[redir_in.k] = '\0';
	redir_in.pid = fork();
	if (redir_in.pid == 0)
		redir_in_1(split, &redir_in, program);
	else
		wait(&g_global_status);
}

void	redir_out_sup_1(t_redir_out *redir)
{
	while (redir->i < redir->matrix_size - 1)
	{
		redir->split_name = ft_split(redir->split_ang[redir->i], ' ');
		ft_putstr(redir->split_name[0]);
		redir->fd = open(redir->split_name[0], O_CREAT | O_RDWR, 0644);
		free_matrix(redir->split_name);
		redir->i++;
	}
}

void	redir_out_1(char *split, t_redir_out *redir, t_program *program)
{
	redir->found_out = ft_strchr(split, (int) '>');
	if (redir->found_out[1] == '>')
		redir->out = 2;
	redir->split_name = ft_split(redir->split_ang[redir->matrix_size - 1], ' ');
	if (redir->out == 2)
	{
		redir->fd = open(redir->split_name[0], O_CREAT | O_RDWR | O_APPEND,
				0644);
		if (redir->fd < 0)
			exit(EXIT_FAILURE);
	}
	else
		redir->fd = open(redir->split_name[0], O_CREAT | O_RDWR | O_TRUNC,
				0644);
	dup2(redir->fd, STDOUT_FILENO);
	close(redir->fd);
	check_function(redir->split_ang[0], program);
	free_matrix(redir->split_name);
	redir->i = 1;
	redir_out_sup_1(redir);
	exit(EXIT_SUCCESS);
}

void	handle_redirection_out(char *split, t_program *program)
{
	t_redir_out	redir;

	redir.split_ang = ft_split(split, '>');
	redir.matrix_size = 0;
	while (redir.split_ang[redir.matrix_size])
		redir.matrix_size++;
	redir.out = 1;
	redir.pid = fork();
	if (redir.pid == 0)
		redir_out_1(split, &redir, program);
	else
		wait(&g_global_status);
	free_matrix(redir.split_ang);
}
