/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <stribuzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 08:47:00 by stribuzi          #+#    #+#             */
/*   Updated: 2021/08/23 12:54:31 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_status_value(t_list *to_change, int value)
{
	t_list	*support_list;
	char	*itoa_res;
	char	*support;

	itoa_res = ft_itoa(value);
	support = ft_strjoin("?=", itoa_res);
	support_list = to_change;
	while (support_list)
	{
		if (ft_strncmp(support_list->content, "?", 1) == 0)
		{
			if (support_list->content)
				free(support_list->content);
			support_list->content = support;
		}
		support_list = support_list->next;
	}
	free(itoa_res);
}

void	change_path_value(t_program *program)
{
	t_list	*support;

	support = program->global_variables;
	while (support)
	{
		if (ft_strncmp(support->content, "PATH", 4) == 0)
		{
			free_matrix(program->path);
			program->path = ft_split(&support->content[4], ':');
			return ;
		}
		support = support->next;
	}
	free_matrix(program->path);
	program->path = ft_split("rubbish", ' ');
}

void	check_if_executable(t_func *function, char *split, t_program *program)
{
	if (ft_strncmp(&split[function->k], "./", 2) != 0)
	{
		if (execute_binaries(&split[function->k], program) == 0)
		{
			ft_putstr(&split[function->k]);
			ft_putstr(": Command not found\n");
			exit(127);
		}
		exit(EXIT_SUCCESS);
	}
}
