/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:19:57 by rchaumei          #+#    #+#             */
/*   Updated: 2026/02/05 23:27:06 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_path(char **path)
{
	int	i;

	i = -1;
	if (!path)
		return ;
	while (path[++i])
		free(path[i]);
	free(path);
}

void	close_perror(int *fds, int *pid, t_command s, char **cmd)
{
	perror("\033[31mError");
	free_path(cmd);
	free_path(s.path);
	free(pid);
	close(fds[0]);
	close(fds[1]);
	close(s.in);
	close(s.out);
	exit(127);
}

void	close_perror2(int *fds, int *pid, t_command s, char **cmd)
{
	perror("\033[31mError");
	free_path(cmd);
	free_path(s.path);
	free(pid);
	close(fds[0]);
	close(fds[1]);
	close(s.in);
	close(s.out);
	exit(126);
}

void	close_invalid(int *fds, int *pid, t_command s)
{
	free_path(s.path);
	free(pid);
	close(fds[0]);
	close(fds[1]);
	close(s.in);
	perror("\033[31mError");
	exit(1);
}

void	close_putstr(int *fds, int *pid, t_command s, char **cmd)
{
	ft_putstr_fd("command not found: ", 2);
	if (cmd && cmd[0])
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("\n", 2);
	}
	else
		ft_putstr_fd("\n", 2);
	free_path(cmd);
	free_path(s.path);
	free(pid);
	close(fds[0]);
	close(fds[1]);
	close(s.in);
	close(s.out);
	exit(127);
}
