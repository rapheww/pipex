/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:21:58 by rchaumei          #+#    #+#             */
/*   Updated: 2026/02/05 23:22:31 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child(int i, int *pid, int *fds, t_command s)
{
	if (s.fd_in < 0)
		close_invalid(fds, pid, s);
	if (ft_strncmp(s.av[1], "here_doc", 8))
		s.cmd = ft_split(s.av[i + 2], ' ');
	else
		s.cmd = ft_split(s.av[i + 3], ' ');
	if (!s.cmd || !s.cmd[0] || !s.cmd[0][0])
		close_putstr(fds, pid, s, s.cmd);
	if (is_slash(s.cmd[0]) && access(s.cmd[0], F_OK) == -1)
		close_perror(fds, pid, s, s.cmd);
	if (access(s.cmd[0], F_OK) == 0 && access(s.cmd[0], X_OK) == -1)
		close_perror2(fds, pid, s, s.cmd);
	if ((!s.path || !s.path[0] || !s.path[0][0]) && access(s.cmd[0], X_OK) ==
		-1)
		close_perror(fds, pid, s, s.cmd);
	s.cmd_path = get_cmd_path(s.cmd, s.path);
	if (!s.cmd_path)
		close_putstr(fds, pid, s, s.cmd);
	dup2(s.fd_out, 1);
	dup2(s.fd_in, 0);
	close(s.fd_in);
	close(s.fd_out);
	if (execve(s.cmd_path, s.cmd, s.envp) == -1)
		perror("\033[31mError");
	free_path(s.cmd);
}

void	child2(int ac, int *pid, int *fds, t_command s)
{
	if (s.out == -1)
		close_invalid(fds, pid, s);
	dup2(s.fd_in, 0);
	dup2(s.out, 1);
	close(s.fd_in);
	if (s.out >= 0)
		close(s.out);
	s.cmd = ft_split(s.av[ac - 2], ' ');
	if (!s.cmd || !s.cmd[0] || !s.cmd[0][0])
		close_putstr(fds, pid, s, s.cmd);
	if (is_slash(s.cmd[0]) && access(s.cmd[0], F_OK) == -1)
		close_perror(fds, pid, s, s.cmd);
	if (access(s.cmd[0], F_OK) == 0 && access(s.cmd[0], X_OK) == -1)
		close_perror2(fds, pid, s, s.cmd);
	if ((!s.path || !s.path[0] || !s.path[0][0]) && access(s.cmd[0], X_OK) ==
		-1)
		close_perror(fds, pid, s, s.cmd);
	s.cmd_path = get_cmd_path(s.cmd, s.path);
	if (!s.cmd_path)
		close_putstr(fds, pid, s, s.cmd);
	if (execve(s.cmd_path, s.cmd, s.envp) == -1)
		perror("\033[31mError");
	free_path(s.path);
	free_path(s.cmd);
	free(s.cmd_path);
}

void	call_child(t_command *s, int *i)
{
	while (*i < s->num_cmd)
	{
		pipe(s->fds);
		s->fd_out = s->fds[1];
		s->pid[*i] = fork();
		if (!s->pid[*i])
		{
			close(s->fds[0]);
			if (s->out >= 0)
				close(s->out);
			child(*i, s->pid, s->fds, *s);
			close(s->fd_in);
			close(s->fds[1]);
			free(s->pid);
		}
		if (s->fd_in >= 0)
			close(s->fd_in);
		close(s->fds[1]);
		s->fd_in = s->fds[0];
		(*i)++;
	}
}
