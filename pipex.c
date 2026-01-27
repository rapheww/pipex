/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:45:39 by rchaumei          #+#    #+#             */
/*   Updated: 2026/01/27 23:51:09 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "stdlib.h"

int	main(int ac, char **av, char **envp)
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

	if (ac == 5)
	{
		if (check_file(av))
			return (0);
		in = open(av[1], O_RDONLY);
		out = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
		path = get_path(envp);
		if (!path)
			return (close_prog(NULL, NULL, in, out), 1);
		cmd1 = ft_split(av[2], ' ');
		if (!cmd1)
			return (close_prog(path, NULL, in, out), 1);
		cmd2 = ft_split(av[3], ' ');
		if (!cmd2)
			return (close_prog(path, cmd1, in, out), 1);
		pipe(pipefds);
		pid1 = fork();
		if (pid1 == 0)
		{
			if (in == -1)
			{
				free_cmd(cmd1);
				free_cmd(cmd2);
				free_cmd(path);
				close(pipefds[0]);
				close(pipefds[1]);
				close(out);
				close(in);
				exit(1);
			}
			if (!cmd1 || !cmd1[0] || !cmd1[0][0])
			{
				free_cmd(cmd1);
				free_cmd(cmd2);
				free_cmd(path);
				exit(127);
			}
			dup2(in, 0);
			dup2(pipefds[1], 1);
			close(in);
			close(pipefds[0]);
			close(pipefds[1]);
			close(out);
			cmd1_path = get_cmd_path(cmd1[0], path);
			if (!cmd1_path)
			{
				free_cmd(cmd1);
				free_cmd(cmd2);
				free_cmd(path);
				exit(127);
			}
			execve(cmd1_path, cmd1, envp);
			free_cmd(cmd1);
			free_cmd(cmd2);
			free(cmd1_path);
			exit(0);
		}
		pid2 = fork();
		if (pid2 == 0)
		{
			if (out == -1)
			{
				free_cmd(cmd1);
				free_cmd(cmd2);
				free_cmd(path);
				close(pipefds[0]);
				close(pipefds[1]);
				close(out);
				close(in);
				exit(1);
			}
			if (!cmd2 || !cmd2[0] || !cmd2[0][0])
			{
				free_cmd(cmd1);
				free_cmd(cmd2);
				free_cmd(path);
				exit(127);
			}
			dup2(pipefds[0], 0);
			dup2(out, 1);
			close(pipefds[0]);
			close(pipefds[1]);
			close(out);
			close(in);
			cmd2_path = get_cmd_path(cmd2[0], path);
			if (!cmd2_path)
			{
				free_cmd(cmd1);
				free_cmd(cmd2);
				free_cmd(path);
				exit(127);
			}
			execve(cmd2_path, cmd2, envp);
			free_cmd(cmd1);
			free_cmd(cmd2);
			free(cmd2_path);
			exit(0);
		}
		close(pipefds[0]);
		close(pipefds[1]);
        close(in);
        close(out);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, &status, 0);
		if (status >= 256)
			exit_code = status / 256;
		else if (status == 0)
			exit_code = 0;
		else
			exit_code = 128 + status;
		free_cmd(cmd1);
		free_cmd(cmd2);
		free_cmd(path);
		return (exit_code);
	}
	return (0);
}
