/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:15:21 by rchaumei          #+#    #+#             */
/*   Updated: 2026/02/01 17:11:14 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*ft_strdup(const char *src);
int		ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *src);
char	*get_next_line(int fd);
char	*ft_fill_line(char *tmp);

#endif