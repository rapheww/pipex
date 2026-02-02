/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 20:55:20 by rchaumei          #+#    #+#             */
/*   Updated: 2026/02/02 23:59:14 by rchaumei         ###   ########.fr       */
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

int check_outfile(char *file, int i)
{
    if (access(file, F_OK) == 0)
		if (access(file, W_OK) == -1)
			perror("\033[31mError");
	if (i == 1)
		return(open(file, O_WRONLY | O_APPEND | O_CREAT, 0777));
    return (open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777));
}

char	**get_env(char **env)
{
	char	**path;
	
	if (!env || !env[0] || !env[0][0])
		return (NULL);
	while (*env)
	{
		if (ft_strncmp(*env, "PATH", 4) == 0)
			break ;
		env++;
	}
	if (*env)
		path = ft_split(*env + 5, ':');
	else
		path = NULL;
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
	if(!path || !path[0] || !path[0][0])
		exit(127);
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

void here_doc(char *lim, int ac, int *fds)
{
	char *line;
	
	if (ac < 6)
	{
		ft_putstr_fd("Invalid LIMITER\n", 2);
		exit(1);
	}
	close(fds[0]);
	ft_putstr_fd("pipe heredoc >", 1);
	line = get_next_line(0);
	while(line)
	{
		if (ft_strncmp(lim, line, ft_strlen(lim)) == 0)
		{
			close(fds[1]);
			free(line);
			exit(0);
		}
		write(fds[1], line, ft_strlen(line));
		free(line);
		ft_putstr_fd("pipe heredoc >", 1);
		line = get_next_line(0);
	}
	
}

void child(char **envp, char **av, int i,char **path, int fd_in, int fd_out)
{
	char **cmd;
	char *cmd_path;
	
	if (fd_in < 0)
		exit(1);
	if (ft_strncmp(av[1], "here_doc", 8))
		cmd = ft_split(av[i + 2], ' ');
	else
		cmd = ft_split(av[i + 3], ' ');
	if (!cmd || !cmd[0] || !cmd[0][0])
		exit(127);
	cmd_path = get_cmd_path(cmd[0], path);
	if (!cmd_path)
		exit(127);
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
	int num_ac;
	int num_cmd;
	char *cmd_path;
	
    if (ac >= 5)
    {
		i = 0;
		pid = malloc(sizeof(int) * (ac - 3));
		
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
		{
			out = check_outfile(av[ac - 1], 1);
			pipe(fds);
			fd_in = fds[0];
			num_ac = ac - 4;
			num_cmd = ac - 3;
			pid[i] = fork();
			if (!pid[i])
				here_doc(av[2], ac, fds);
			i++;
			close(fds[1]);
		}
		else
		{
			out = check_outfile(av[ac - 1], 0);
			num_ac = ac - 3;
			num_cmd = ac - 4;
        	in = check_infile(av[1]);
			fd_in = in;
		}
        path = get_env(envp);
		while (i  < num_cmd)
		{
			pipe(fds);
			pid[i] = fork();
			if (!pid[i])
			{
				close(fds[0]);
				child(envp, av, i, path, fd_in, fds[1]);
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
			if (out == -1)
				exit(1);
			dup2(fd_in, 0);
			dup2(out, 1);
			close(fd_in);
			close(out);
			cmd = ft_split(av[ac - 2], ' ');
			if (!cmd || !cmd[0] || !cmd[0][0])
				exit(127);
			cmd_path = get_cmd_path(cmd[0], path);
			if (!cmd_path)
				exit(127);
			if (execve(cmd_path, cmd, envp) == -1)
				ft_putstr_fd("Invalid command", 2);
			free(cmd);
			free(cmd_path);
		}
		close(fd_in);
		close(out);
		i = 0;
		while(i < num_ac)
		{
			waitpid(pid[i], &status, 0);
			i++;
		}
		if (status >= 256)
			return (status / 256);
		return (0);
    }
    return (0);
}
