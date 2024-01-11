/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_last.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <stribuzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 08:45:55 by stribuzi          #+#    #+#             */
/*   Updated: 2021/08/13 09:09:38 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_last_char(char *s, char c)
{
	int	i;
	int	pos;

	pos = -1;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			pos = i;
		i++;
	}
	if (pos != -1)
	{
		return (&s[pos]);
	}
	else
		return (NULL);
}

int	find_last_pos_char(char *s, char c)
{
	int	i;
	int	pos;

	pos = -1;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			pos = i;
		i++;
	}
	return (pos);
}

char	*find_last_word(char *haystack, char *needle)
{
	int		found;
	size_t	i;
	int		index;

	i = 0;
	while (i <= ft_strlen(haystack) - ft_strlen(needle))
	{
		found = 1;
		if (ft_strncmp(&haystack[i], needle, ft_strlen(needle)) != 0)
			found = 0;
		if (found == 1)
			index = i;
		i++;
	}
	return (&haystack[index]);
}
