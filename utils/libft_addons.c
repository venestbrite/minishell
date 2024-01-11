/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_addons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <stribuzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 08:47:18 by stribuzi          #+#    #+#             */
/*   Updated: 2021/08/13 08:47:18 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			x;
	unsigned char	*y;

	x = 0;
	y = s;
	while (n > 0)
	{
		y[x] = '\0';
		x++;
		n--;
	}
}

void	ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}

void	free_matrix(char **to_free)
{
	int	j;

	j = 0;
	if (!to_free)
		return ;
	while (to_free[j])
	{
		if (to_free[j])
			free(to_free[j]);
		j++;
	}
	if (to_free)
		free(to_free);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

char	*ft_strcpy(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
