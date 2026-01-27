/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:56:14 by rchaumei          #+#    #+#             */
/*   Updated: 2026/01/26 21:51:41 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "libft/libft.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

// CMD PATH

char **create_cmd_path(int i, char **cmd1, char **cmd2, char **path);
int get_cmd_num(char **av);

#endif