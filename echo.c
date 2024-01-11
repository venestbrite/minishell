/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <stribuzi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 08:45:47 by stribuzi          #+#    #+#             */
/*   Updated: 2021/08/17 18:32:03 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_support(char **split, t_program *program, int i, int k)
{
	if (split[k][1] == '$')
	{
		if (ft_strlen(split[k]) <= 3)
			ft_putstr("$");
		else
			search_variable_right(&split[k][2], program);
	}
	else
	{
		i = 1;
		while (split[k][i] != '\0' && split[k][i] != '"')
		{
			write(1, &split[k][i], 1);
			i++;
		}
	}
}

void	echo_support_2(char **split, int k)
{
	int	i;

	i = 0;
	while (split[k][i] != '"' && split[k][i] != '\0')
	{
		write(1, &split[k][i], 1);
		i++;
	}
}

void	echo_support_3(char **split, int k, int i, t_program *program)
{
	if (split[k][0] == '\'')
	{
		i = 1;
		while (split[k][i] != '\0' && split[k][i] != '\'')
		{
			write(1, &split[k][i], 1);
			i++;
		}
	}
	else if (split[k][0] == '"')
		echo_support(split, program, i, k);
	else if (split[k][0] == '$')
	{
		if (ft_strlen(split[k]) <= 1)
			ft_putstr("$");
		else
			search_variable_right(&split[k][1], program);
	}
	else
		echo_support_2(split, k);
}

void	echo_support_4(char *to_print, int *newline_flag, int *i)
{
	newline_flag[0] = 1;
	i[0] = 0;
	while (is_space(to_print[i[0]]) == 1)
		i[0]++;
	i[0] += 4;
	while (is_space(to_print[i[0]]) == 1)
		i[0]++;
	if (ft_strncmp(&to_print[i[0]], "-n", 2) == 0)
	{
		i[0] += 2;
		while (is_space(to_print[i[0]]) == 1)
			i[0]++;
		newline_flag[0] = 0;
	}
}

void	echo_command(char *to_print, t_program *program)
{
	t_echo	echo;

	echo.pid = fork();
	if (echo.pid == 0)
	{
		echo_support_4(to_print, &echo.newline_flag, &echo.i);
		echo.k = 0;
		echo.split = ft_split(&to_print[echo.i], ' ');
		echo.matrix_size = 0;
		while (echo.split[echo.matrix_size])
			echo.matrix_size++;
		while (echo.split[echo.k])
		{
			echo_support_3(echo.split, echo.k, echo.i, program);
			echo.k++;
			if (echo.k != echo.matrix_size)
				ft_putstr(" ");
		}
		if (echo.newline_flag)
			ft_putstr("\n");
		free_matrix(echo.split);
		exit(EXIT_SUCCESS);
	}
	else
		wait(&g_global_status);
}
