/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <stribuzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 08:45:43 by stribuzi          #+#    #+#             */
/*   Updated: 2021/08/13 09:25:13 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_var_support(t_list *support_list, char *support)
{
	while (support_list)
	{
		if (ft_strncmp(support_list->content, support, ft_strlen(support)) == 0)
		{
			ft_putstr(&ft_strchr(support_list->content, (int) '=')[1]);
			return (1);
		}
		support_list = support_list->next;
	}
	return (0);
}

void	search_var_support_2(t_list *support_list, char *support)
{
	while (support_list)
	{
		if (ft_strncmp(support_list->content, support, ft_strlen(support)) == 0)
		{
			ft_putstr(&ft_strchr(support_list->content, (int) '=')[1]);
			break ;
		}
		support_list = support_list->next;
	}
}

void	search_variable_right(char *str, t_program *program)
{
	char	support[500];
	int		i;
	t_list	*support_list;

	i = 0;
	while (str[i] != '\0' && str[i] != '"')
	{
		support[i] = str[i];
		i++;
	}
	support[i] = '\0';
	support_list = program->local_variables;
	if (search_var_support(support_list, support))
		return ;
	support_list = program->global_variables;
	search_var_support_2(support_list, support);
}
