/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 17:29:29 by rchaumei          #+#    #+#             */
/*   Updated: 2025/11/17 17:53:08 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t size)
{
	char	*tmp;
	char	*dest;

	tmp = (char *)source;
	dest = (char *)destination;
	if (tmp < dest)
	{
		while (size--)
			dest[size] = tmp[size];
	}
	else
		ft_memcpy(destination, source, size);
	return (destination);
}
