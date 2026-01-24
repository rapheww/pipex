/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:29:33 by rchaumei          #+#    #+#             */
/*   Updated: 2025/11/11 13:02:58 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (s)
	{
		ft_putstr_fd(s, fd);
		ft_putchar_fd('\n', fd);
	}
}

/*#include<fcntl.h>

int	main(void)
{
	int fd = open("test.txt", O_RDWR);
	ft_putendl_fd("salut c'est moi", fd);
	close(fd);
	return(0);
}*/