/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:45:39 by rchaumei          #+#    #+#             */
/*   Updated: 2026/01/28 20:26:59 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "stdlib.h"

void	close_all(t_command *s, int i, int j)
{
	if (i == 1)
	{
		free_cmd(s->cmd1);
		free_cmd(s->cmd2);
		free_cmd(s->path);
	}
	if (j == 1)
	{
		close(s->pipefds[0]);
		close(s->pipefds[1]);
		close(s->out);
		close(s->in);
	}
}

int	init(t_command *s, char **envp, char **av)
{
	s->in = open(av[1], O_RDONLY);
	s->out = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	s->path = get_path(envp);
	if (!s->path)
		return (close_prog(NULL, NULL, s->in, s->out), 1);
	s->cmd1 = ft_split(av[2], ' ');
	if (!s->cmd1)
		return (close_prog(s->path, NULL, s->in, s->out), 1);
	s->cmd2 = ft_split(av[3], ' ');
	if (!s->cmd2)
		return (close_prog(s->path, s->cmd1, s->in, s->out), 1);
	pipe(s->pipefds);
	return (0);
}

void	child1(t_command *s, char **envp)
{
	if (s->in == -1)
	{
		close_all(s, 1, 1);
		exit(1);
	}
	if (!s->cmd1 || !s->cmd1[0] || !s->cmd1[0][0])
	{
		close_all(s, 1, 0);
		exit(127);
	}
	dup2(s->in, 0);
	dup2(s->pipefds[1], 1);
	close_all(s, 0, 1);
	s->cmd1_path = get_cmd_path(s->cmd1[0], s->path);
	if (!s->cmd1_path)
	{
		close_all(s, 1, 0);
		exit(127);
	}
	execve(s->cmd1_path, s->cmd1, envp);
	close_all(s, 1, 0);
	exit(0);
}

void	child2(t_command *s, char **envp)
{
	if (s->out == -1)
	{
		close_all(s, 1, 1);
		exit(1);
	}
	if (!s->cmd2 || !s->cmd2[0] || !s->cmd2[0][0])
	{
		close_all(s, 1, 0);
		exit(127);
	}
	dup2(s->pipefds[0], 0);
	dup2(s->out, 1);
	close_all(s, 0, 1);
	s->cmd2_path = get_cmd_path(s->cmd2[0], s->path);
	if (!s->cmd2_path)
	{
		close_all(s, 1, 0);
		exit(127);
	}
	execve(s->cmd2_path, s->cmd2, envp);
	close_all(s, 1, 0);
	exit(0);
}

int	main(int ac, char **av, char **envp)
{
	t_command	s;

	if (ac == 5)
	{
		if (check_file(av))
			return (1);
		if (init(&s, envp, av))
			return (1);
		s.pid1 = fork();
		if (s.pid1 == 0)
			child1(&s, envp);
		s.pid2 = fork();
		if (s.pid2 == 0)
			child2(&s, envp);
		close_all(&s, 0, 1);
		waitpid(s.pid1, NULL, 0);
		waitpid(s.pid2, &s.status, 0);
		if (s.status >= 256)
			s.exit_code = s.status / 256;
		else
			s.exit_code = 0;
		return (close_all(&s, 1, 0), s.exit_code);
	}
	return (0);
}
