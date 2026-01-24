/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:20:49 by rchaumei          #+#    #+#             */
/*   Updated: 2025/11/10 15:19:36 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t size)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < size)
	{
		*ptr = (unsigned char)c;
		i++;
		ptr++;
	}
	return (s);
}

/*#include<stdio.h>

int	main(void)
{
	char str[5] = "Salut";
	printf("before memset : %s\n", str);
	ft_memset(str, 'C', 6);
	printf("after memset : %s\n", str);
	return (0);
}*/