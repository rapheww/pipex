/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:45:20 by rchaumei          #+#    #+#             */
/*   Updated: 2025/11/11 16:18:23 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *p1, const void *p2, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	i = 0;
	s1 = (unsigned char *)p1;
	s2 = (unsigned char *)p2;
	while (i < n)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		i++;
		s1++;
		s2++;
	}
	return (0);
}

/*#include<stdio.h>

int	main(void)
{
	char p1[] = "saLut";
	char p2[] = "salut";
	printf("%d", ft_memcmp(p1, p2, 4));
	return (0);
}*/