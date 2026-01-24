/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:43:11 by rchaumei          #+#    #+#             */
/*   Updated: 2025/11/10 15:20:42 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

/*#include<fcntl.h>

int	main(void)
{
	int fd = open("test.txt", O_RDWR);
	ft_putstr_fd("salut c'est moi", fd);
	close(fd);
	return(0);
}*/