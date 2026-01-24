/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:49 by rchaumei          #+#    #+#             */
/*   Updated: 2025/11/17 18:44:51 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	src_len;
	char	*dest;

	i = 0;
	src_len = ft_strlen(s);
	if (start >= src_len)
	{
		return (ft_strdup(""));
	}
	if (len > src_len - start)
		len = src_len - start;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (i < len && s[i + start])
	{
		dest[i] = s[i + start];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*#include<stdio.h>
int	main(void)
{
		char src[] = "idcbvwvhrviherihevhfiv";
		printf("%s\n", ft_substr(src, 4, 3));
		return (0);
}*/