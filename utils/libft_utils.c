/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <stribuzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 08:47:22 by stribuzi          #+#    #+#             */
/*   Updated: 2021/08/13 08:47:22 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	unsigned int	count;

	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

int	only_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (is_space(s[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_lstiter_new(t_list *lst)
{
	if (!lst)
	{
		lst = (t_list *)malloc(sizeof(t_list *));
		lst->next = NULL;
		return ;
	}
	if (lst->next)
		lst = lst->next;
	while (lst)
	{
		write(1, (char *)lst->content, ft_strlen((char *)lst->content));
		write(1, "\n", 1);
		lst = lst->next;
	}
}
