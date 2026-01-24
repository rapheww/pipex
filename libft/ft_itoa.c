/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:14:43 by rchaumei          #+#    #+#             */
/*   Updated: 2025/11/13 14:22:26 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_count(long int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_change(char *result, long int nb, int len)
{
	if (nb == 0)
	{
		result[0] = '0';
		return (result);
	}
	if (nb < 0)
	{
		result[0] = '-';
		nb = -nb;
	}
	while (nb)
	{
		result[--len] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	char		*result;
	int			len;
	int long	nb;

	nb = n;
	len = ft_count(nb);
	result = malloc(sizeof(char) * (ft_count(nb) + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	ft_change(result, nb, len);
	return (result);
}

/*#include<stdio.h>

int	main(void)
{
	char *s = ft_itoa(110);
	printf("%s", s);
	return(0);
}*/