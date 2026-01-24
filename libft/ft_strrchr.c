/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:35:00 by rchaumei          #+#    #+#             */
/*   Updated: 2025/11/13 14:54:33 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;

	ptr = NULL;
	while (*s)
	{
		if ((unsigned char)*s == (unsigned char)c)
			ptr = (char *)s;
		s++;
	}
	if ((unsigned char)*s == (unsigned char)c)
		return ((char *)s);
	if (c == '\0')
		return ((char *)s);
	return (ptr);
}

/*#include<stdio.h>

int	main(void)
{
	char *str = "Salut c moi";
	printf("%s", ft_strrchr(str, 'S'));
	return (0);
}*/