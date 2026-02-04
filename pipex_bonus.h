/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 20:54:15 by rchaumei          #+#    #+#             */
/*   Updated: 2026/02/05 00:12:40 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_command
{
	int		in;
	int		out;
	char	**path;
	int		status;
	int		*pid;
	char	**cmd;
	int		fds[2];
	int		fd_in;
	int		num_ac;
	int		num_cmd;
	char	*cmd_path;
	int		last_pid;
	int		wpid;
	int		exit_code;
	int		fd_out;
}			t_command;

#endif