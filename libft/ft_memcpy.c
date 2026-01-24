/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:11:50 by rchaumei          #+#    #+#             */
/*   Updated: 2025/11/17 17:52:58 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t size)
{
	size_t	i;
	char	*dst;
	char	*src;

	i = 0;
	dst = (char *)destination;
	src = (char *)source;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}
