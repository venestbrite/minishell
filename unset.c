/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <stribuzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 08:46:56 by stribuzi          #+#    #+#             */
/*   Updated: 2021/08/13 08:46:57 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_support(t_program *program, t_unset *unset)
{
	while (unset->split [unset->i])
	{
		unset->temp = program->global_variables;
		while (unset->temp != NULL && ft_strncmp(unset->split[unset->i],
				unset->temp->content, ft_strlen(unset->split[unset->i])) != 0)
		{
			unset->prev = unset->temp;
			unset->temp = unset->temp->next;
		}
		if (unset->temp == NULL)
			break ;
		free(unset->temp->content);
		free(unset->temp);
		unset->prev->next = unset->temp->next;
		unset->i++;
	}
}

void	unset_support_2(t_program *program, t_unset *unset)
{
	while (unset->split [unset->i])
	{
		unset->temp = program->local_variables;
		while (unset->temp != NULL && ft_strncmp(unset->split[unset->i],
				unset->temp->content, ft_strlen(unset->split[unset->i])) != 0)
		{
			unset->prev = unset->temp;
			unset->temp = unset->temp->next;
		}
		if (unset->temp == NULL)
			break ;
		free(unset->temp->content);
		free(unset->temp);
		unset->prev->next = unset->temp->next;
		unset->i++;
	}
}

void	unset_variable(char *s, t_program *program)
{
	int		matrix_size;
	t_unset	unset;

	unset.i = 1;
	matrix_size = 0;
	unset.split = ft_split(s, ' ');
	while (unset.split[matrix_size])
		matrix_size++;
	if (matrix_size > 1)
	{
		unset_support(program, &unset);
		unset.i = 1;
		unset_support_2(program, &unset);
	}
	free_matrix(unset.split);
}
