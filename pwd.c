/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <stribuzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 08:46:42 by stribuzi          #+#    #+#             */
/*   Updated: 2021/08/13 08:46:42 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*support;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		support = NULL;
		support = getcwd(support, 1);
		ft_putstr(support);
		ft_putstr("\n");
		if (support)
			free(support);
		exit(EXIT_SUCCESS);
	}
	else
		wait(&g_global_status);
}

t_list	*get_envp(char **envp)
{
	int		len;
	t_list	*to_ret;
	t_list	*support;

	to_ret = ft_lstnew((void *)ft_strdup(envp[0]));
	len = 1;
	while (envp[len])
	{
		support = ft_lstnew((void *)ft_strdup(envp[len]));
		ft_lstadd_back(&to_ret, support);
		len++;
	}
	return (to_ret);
}

void	free_prog(t_program *program)
{
	while (program->global_variables)
	{
		free(program->global_variables->content);
		free(program->global_variables);
		program->global_variables = program->global_variables->next;
	}
	while (program->local_variables)
	{
		free(program->local_variables->content);
		free(program->local_variables);
		program->local_variables = program->local_variables->next;
	}
	free_matrix(program->path);
}

int	take_input(char *str)
{
	char	*buf;

	buf = readline("\U0001F642 $> ");
	if (buf)
	{
		add_history(buf);
		ft_strcpy(str, buf);
		free(buf);
		return (0);
	}
	else
		return (1);
}
