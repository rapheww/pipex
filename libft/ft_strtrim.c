/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 18:05:27 by rchaumei          #+#    #+#             */
/*   Updated: 2025/11/12 13:34:47 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_char(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	int	start;
	int	end;

	if (!s || !set)
		return (NULL);
	end = ft_strlen(s) - 1;
	start = 0;
	while (check_char(s[start], set) == 1)
		start++;
	while (check_char(s[end], set) == 1)
		end--;
	if (start > end)
		return (ft_strdup(""));
	return (ft_substr(s, start, (end - start + 1)));
}
