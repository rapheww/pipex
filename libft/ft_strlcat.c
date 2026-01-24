/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:39:07 by rchaumei          #+#    #+#             */
/*   Updated: 2025/11/12 14:50:11 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	len_dest;

	src_len = ft_strlen(src);
	len_dest = ft_strlen(dest);
	if (len_dest >= size)
		return (size + src_len);
	if (src_len < size - len_dest)
		ft_memcpy(dest + len_dest, src, src_len + 1);
	else
	{
		ft_memcpy(dest + len_dest, src, size - len_dest - 1);
		dest[size - 1] = '\0';
	}
	return (len_dest + src_len);
}
