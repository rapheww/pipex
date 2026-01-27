/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:56:14 by rchaumei          #+#    #+#             */
/*   Updated: 2026/01/27 23:40:05 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "libft/libft.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>



//UTILS

char	*get_cmd_path(char *cmd, char **path);
char	**get_path(char **env);
int	check_file(char **av);
void	free_cmd(char **tmp);
void	close_prog(char **tab, char **tmp, int in, int out);

#endif