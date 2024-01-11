/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <stribuzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 08:46:37 by stribuzi          #+#    #+#             */
/*   Updated: 2021/08/13 08:46:39 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	while_pipe(char **cmd, int i, t_pipe *p_struct, t_program *program)
{
	while (cmd[i] != NULL)
	{
		pipe(p_struct->pipefd);
		p_struct->pid = fork();
		if (p_struct->pid == -1)
			exit(EXIT_FAILURE);
		else if (p_struct->pid == 0)
		{
			dup2(p_struct->fd_in, 0);
			if ((cmd[i + 1]) != NULL)
				dup2(p_struct->pipefd[1], 1);
			close(p_struct->pipefd[0]);
			check_function(cmd[i], program);
			exit(EXIT_SUCCESS);
		}
		else
		{
			wait(&g_global_status);
			close(p_struct->pipefd[1]);
			p_struct->fd_in = p_struct->pipefd[0];
			i++;
		}
	}
}

void	loop_pipe(char **cmd, t_program *program)
{
	t_pipe	p_struct;
	int		i;

	p_struct.fd_in = 0;
	i = 0;
	while_pipe(cmd, i, &p_struct, program);
}
