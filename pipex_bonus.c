/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 20:55:20 by rchaumei          #+#    #+#             */
/*   Updated: 2026/01/31 00:12:31 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int check_infile(char *file)
{
    if (access(file, F_OK) == -1)
		perror("\033[31mError");
	if (access(file, F_OK) == 0)
		if (access(file, R_OK) == -1)
			perror("\033[31mError");
	return (open(file, O_RDONLY));
}

int check_outfile(char *file)
{
    if (access(file, F_OK) == 0)
		if (access(file, W_OK) == -1)
			perror("\033[31mError");
    return (open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777));
}

char	**get_env(char **env)
{
	char	**path;

	while (*env)
	{
		if (ft_strncmp(*env, "PATH", 4) == 0)
			break ;
		env++;
	}
	path = ft_split(*env + 5, ':');
	return (path);
}

char	*get_cmd_path(char *cmd, char **path)
{
	char	*command;
	char	*tmp;
	int		i;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (path[i])
	{
		command = ft_strjoin(path[i], "/");
		if (!command)
			return (NULL);
		tmp = ft_strjoin(command, cmd);
		free(command);
		if (!tmp)
			return (NULL);
		if (access(tmp, X_OK) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (ft_putstr_fd("Invalid command\n", 2), NULL);
}

void child(char **envp, char **av, int i, int pid, char **path, int fd_in, int fd_out)
{
	char **cmd;
	char *cmd_path;
	
	cmd = ft_split(av[i + 2], ' ');
	cmd_path = get_cmd_path(cmd[0], path);
	dup2(fd_out, 1);
	dup2(fd_in, 0);
	close(fd_in);
	close(fd_out);
	execve(cmd_path, cmd, envp);
}

int main(int ac, char **av, char **envp)
{
    int in;
    int out;
    char **path;
	int i;
	int status;
	int *pid;
	char **cmd;
	int fds[2];
	int fd_in;

    if (ac >= 5)
    {
        in = check_infile(av[1]);
        out = check_outfile(av[ac - 1]);
        path = get_env(envp);
		i = 0;
		pid = malloc(sizeof(int) * (ac - 3));
		fd_in = in;
		while (i  < ac - 4)
		{
			pipe(fds);
			pid[i] = fork();
			if (!pid[i])
			{
				close(fds[0]);
				child(envp, av, i, pid[i], path, fd_in, fds[1]);
			}
			close(fd_in);
			close(fds[1]);
			fd_in = dup(fds[0]);
			close(fds[0]);
			i++;
				
		}
		pid[i] = fork();
		if (pid[i] == 0)
		{
			dup2(fd_in, 0);
			dup2(out, 1);
			close(fd_in);
			close(out);
			cmd = ft_split(av[ac - 2], ' ');
			execve(get_cmd_path(cmd[0], path), cmd, envp);
		}
		close(fd_in);
		close(out);
		i = 0;
		while(i < ac - 3)
		{
			waitpid(pid[i], &status, 0);
			i++;
		}
    }
    return (0);
}