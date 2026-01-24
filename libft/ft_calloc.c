/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:59:53 by rchaumei          #+#    #+#             */
/*   Updated: 2025/11/12 12:49:39 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*str;

	if (nmemb != 0 && size > SIZE_MAX / nmemb)
		return (NULL);
	str = malloc(nmemb * size);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, nmemb * size);
	return (str);
}

/*#include <stdio.h>

int	main(void)
{
	int *tab;
	int i;

	tab = (int *)ft_calloc(5, 8);
	if (!tab)
	{
		printf("Échec de l allocation\n");
		return (1);
	}

	for (i = 0; i < 5; i++)
		printf("tab[%d] = %d\n", i, tab[i]);

	free(tab);
	return (0);
}*/