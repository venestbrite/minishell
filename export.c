/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbasso <fbasso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 08:45:52 by stribuzi          #+#    #+#             */
/*   Updated: 2021/08/13 14:48:17 by fbasso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_till_uguale(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '=' && s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
	i++;
	ft_putstr("=\"");
	ft_putstr(&s[i]);
	ft_putstr("\"");
}

void	export_variable_support(t_program *program)
{
	t_list	*iter_support;

	iter_support = program->global_variables;
	if (!program->global_variables)
	{
		program->global_variables = (t_list *)malloc(sizeof(t_list *));
		program->global_variables->next = NULL;
	}
	while (iter_support)
	{
		ft_putstr("declare --x ");
		ft_putstr_till_uguale((char *)iter_support->content);
		write(1, "\n", 1);
		iter_support = iter_support->next;
	}
}

int	check_in_global(char *support, char *to_insert, int len, t_program *program)
{
	t_list	*sup;

	sup = program->global_variables;
	while (sup)
	{
		if (ft_strncmp(sup->content, support, len) == 0)
		{
			free(sup->content);
			sup->content = ft_strdup(to_insert);
			return (1);
		}
		sup = sup->next;
	}
	return (0);
}

void	export_support_2(char *support, int len, t_program *program)
{
	t_list	*temp;
	t_list	*new_list;

	temp = program->local_variables;
	while (temp)
	{
		if (ft_strncmp(temp->content, support, len) == 0)
		{
			if (check_in_global(support, temp->content, len, program))
				break ;
			new_list = ft_lstnew(ft_strdup(temp->content));
			ft_lstadd_back(&program->global_variables, new_list);
			break ;
		}
		temp = temp->next;
	}
	if (support != NULL)
		free(support);
}

void	export_variable(char *s, t_program *program)
{
	int		i;
	int		len;
	char	*support;

	i = 0;
	len = 0;
	while (is_space(s[i]) == 0 && s[i] != '\0')
		i++;
	while (is_space(s[i]) == 1 && s[i] != '\0')
		i++;
	if (only_spaces(&s[i]) == 1)
		return (export_variable_support(program));
	while (is_space(s[i + len]) == 0 && s[i + len] != '\0')
		len++;
	support = malloc(len + 1);
	len = 0;
	while (is_space(s[i + len]) == 0 && s[i + len] != '\0')
	{
		support[len] = s[i + len];
		len++;
	}
	support[len] = '\0';
	export_support_2(support, len, program);
}
