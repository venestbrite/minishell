/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_add_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <stribuzi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 08:45:32 by stribuzi          #+#    #+#             */
/*   Updated: 2021/08/17 18:24:55 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_add_variable_support_1(t_variable *var)
{
	while (var->support)
	{
		if (ft_strncmp((char *)var->support->content, var->first,
				ft_strlen(var->first)) == 0)
		{
			free(var->support->content);
			var->support->content = var->new_content_2;
			return (1);
		}
		var->support = var->support->next;
	}
	return (0);
}

int	check_add_variable_support(char *s, t_variable *var, t_program *program)
{
	var->i = 0;
	while (s[var->i] != '=')
	{
		var->first[var->i] = s[var->i];
		var->i++;
	}
	var->first[var->i] = '\0';
	var->i++;
	var->k = 0;
	if (s[var->i] == '"')
		var->i++;
	while (s[var->i] != '\0')
	{
		if (var->i == ((int)ft_strlen(s) - 1) && s[var->i] == '"')
			break ;
		var->second[var->k] = s[var->i];
		var->k++;
		var->i++;
	}
	var->second[var->k] = '\0';
	var->new_content_1 = ft_strjoin(var->first, "=");
	var->support = program->local_variables;
	var->new_content_2 = ft_strjoin(var->new_content_1, var->second);
	return (check_add_variable_support_1(var));
}

void	check_add_variable(char *s, t_program *program)
{
	t_variable	var;

	var.error = 0;
	var.i = 0;
	while (s[var.i])
	{
		if (is_space(s[var.i]) == 1)
		{
			var.error = 1;
			break ;
		}
		var.i++;
	}
	s[var.i] = '\0';
	if (var.error == 1)
		ft_putstr(strerror(EXIT_FAILURE));
	else
	{
		if (check_add_variable_support(s, &var, program))
			return (free(var.new_content_1));
		var.support_2 = ft_lstnew(var.new_content_2);
		free(var.new_content_1);
		ft_lstadd_back(&program->local_variables, var.support_2);
	}
}
