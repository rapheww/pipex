/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:56:14 by rchaumei          #+#    #+#             */
/*   Updated: 2026/02/01 15:14:00 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_command
{
	int		in;
	int		out;
	char	**path;
	char	**cmd1;
	char	*cmd1_path;
	char	**cmd2;
	char	*cmd2_path;
	int		pid1;
	int		pid2;
	int		pipefds[2];
	int		status;
	int		exit_code;

}			t_command;

// UTILS

char		*get_cmd_path(char *cmd, char **path);
char		**get_path(char **env);
int			check_file(char **av);
void		free_cmd(char **tmp);
void		close_prog(char **tab, char **tmp, int in, int out);

#endif