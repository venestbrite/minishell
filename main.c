/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbasso <fbasso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 08:46:10 by stribuzi          #+#    #+#             */
/*   Updated: 2021/08/13 13:00:31 by fbasso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	backslash_handler(int status)
{
	if (status > 0)
		ft_putstr("quit\n");
	exit(EXIT_SUCCESS);
}

void	handle_sigint(int c)
{
	char	input_string[500];

	if (c < 0)
		return ;
	ft_putstr("\n");
	take_input(input_string);
	return ;
}

static void	int_handler(int status)
{
	if (status < 0)
		return ;
	rl_on_new_line();
	ft_putstr("\n");
	//rl_replace_line("", 0);
	rl_redisplay();
}

int	while_main(char input_string[500], t_program *program)
{
	while (1)
	{
		signal(SIGINT, int_handler);
		signal(SIGQUIT, SIG_IGN);
		if (take_input(input_string) == 1)
		{	
			free_prog(program);
			exit(0);
		}
		if (only_spaces(input_string) == 0)
		{
			if (check_function(input_string, program) == -1)
			{
				free_prog(program);
				return (0);
			}
		}
		ft_bzero(input_string, ft_strlen(input_string));
		change_status_value(program->local_variables,
			WEXITSTATUS(g_global_status));
		change_path_value(program);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int			i;
	t_program	program;
	char		input_string[500];

	if (argc > 1)
		return (0);
	ft_strcpy(input_string, argv[0]);
	ft_bzero(input_string, ft_strlen(input_string));
	program.local_variables = ft_lstnew(ft_strdup("?=0"));
	program.global_variables = get_envp(envp);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			program.path = ft_split(&envp[i][4], ':');
			break ;
		}
		i++;
	}
	while_main(input_string, &program);
	return (0);
}
