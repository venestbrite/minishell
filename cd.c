/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <stribuzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 08:45:22 by stribuzi          #+#    #+#             */
/*   Updated: 2021/08/13 10:48:03 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_d_1(pid_t pid, char *dir, int ret, int i)
{
	pid = fork();
	if (pid == 0)
	{
		if (i == -1)
			ret = chdir(dir);
		else
			ret = chdir(&dir[i]);
		if (ret < 0)
		{
			ft_putstr(dir);
			ft_putstr(": ");
			ft_putstr(strerror(errno));
			ft_putstr("\n");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		wait(&g_global_status);
		if (i == -1)
			ret = chdir(dir);
		else
			ret = chdir(&dir[i]);
	}
}

void	ft_expand_variable(char *to_search, char *support, t_program *program)
{
	t_list	*sup;

	sup = program->local_variables;
	while (sup)
	{
		if (ft_strncmp(to_search, sup->content, ft_strlen(to_search)) == 0)
		{
			ft_strcpy(support, &ft_strchr(sup->content, (int) '=')[1]);
			return ;
		}
		sup = sup->next;
	}
	sup = program->global_variables;
	while (sup)
	{
		if (ft_strncmp(to_search, sup->content, ft_strlen(to_search)) == 0)
		{
			ft_strcpy(support, &ft_strchr(sup->content, (int) '=')[1]);
			return ;
		}
		sup = sup->next;
	}
}

void	change_directory(char *dir, t_program *program)
{
	int		i;
	int		ret;
	pid_t	pid;
	char	support[500];

	i = 0;
	pid = 0;
	ret = 0;
	while (is_space(dir[i]) == 1)
		i++;
	if (dir[i] == '$')
	{
		ft_expand_variable(&dir[i + 1], support, program);
		change_d_1(pid, support, ret, -1);
		return ;
	}
	change_d_1(pid, dir, ret, i);
}

void	sig_handler(int status)
{
	if (status < 0)
		return ;
	return ;
}
