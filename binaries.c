/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <stribuzi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 08:45:10 by stribuzi          #+#    #+#             */
/*   Updated: 2021/08/17 18:20:23 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_bin_general(int *error, char **argv, t_program *program)
{
	int		i;
	char	*join_support;
	char	*joined;

	error[0] = 1;
	i = 0;
	while (program->path[i])
	{
		join_support = ft_strjoin(program->path[i], "/");
		joined = ft_strjoin(join_support, argv[0]);
		if (execve(joined, argv, NULL) > 0)
		{
			error[0] = 0;
			free(joined);
			free(join_support);
			free_matrix(argv);
			return ;
		}
		free(joined);
		free(join_support);
		i++;
	}
	free_matrix(argv);
}

int	execute_binaries(char *str, t_program *program)
{
	int		i;
	char	**argv;
	int		error;

	error = 0;
	i = 0;
	argv = ft_split(str, ' ');
	if (execve(argv[0], argv, NULL) < 0)
	{
		if (errno != 13)
			exec_bin_general(&error, argv, program);
		else
			error = 2;
	}
	else
	{
		free_matrix(argv);
		return (1);
	}
	if (error == 1)
		return (0);
	else if (error == 2)
		return (2);
	return (1);
}
