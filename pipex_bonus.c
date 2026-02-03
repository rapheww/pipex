/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 20:55:20 by rchaumei          #+#    #+#             */
/*   Updated: 2026/02/04 00:11:08 by rchaumei         ###   ########.fr       */
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
	
	if (!env)
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

void free_path(char **path)
{
	int i;

	i = -1;
	if(!path)
		return ;
	while(path[++i])
		free(path[i]);
	free(path);
}

char	*get_cmd_path(char **cmd, char **path, int *pid)
{
	char	*command;
	char	*tmp;
	int		i;

	i = 0;
	if (access(cmd[0], F_OK) == 0 && access(cmd[0], X_OK) == -1)
	{
		perror("\033[31mError");
		free_path(cmd);
		free_path(path);
		free(pid);
		exit(126);
	}
	if (access(cmd[0], X_OK) == 0)
		return (cmd[0]);
	if(!path || !path[0] || !path[0][0])
	{
		perror("\033[31mError");
		exit(127);
	}
	while (path[i])
	{
		command = ft_strjoin(path[i], "/");
		if (!command)
			return (NULL);
		tmp = ft_strjoin(command, cmd[0]);
		free(command);
		if (!tmp)
			return (NULL);
		if (access(tmp, X_OK) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (perror("\033[31mError"), NULL);
}

void here_doc(char *lim, int *fds, int *pid)
{
	char *line;
	
	close(fds[0]);
	ft_putstr_fd("pipe heredoc >", 1);
	line = get_next_line(0);
	while(line)
	{
		if (ft_strncmp(line, lim, ft_strlen(lim)) == 0
    		&& line[ft_strlen(lim)] == '\n')
		{
			get_next_line(-1);
			close(fds[1]);
			free(line);
			free(pid);
			exit(0);
		}
		write(fds[1], line, ft_strlen(line));
		free(line);
		ft_putstr_fd("pipe heredoc >", 1);
		line = get_next_line(0);
	}
	
}

void child(char **envp, char **av, int i,char **path, int fd_in, int fd_out, int *pid)
{
	char **cmd;
	char *cmd_path;
	
	if (fd_in < 0)
	{
		free_path(path);
		free(pid);
		perror("\033[31mError");
		exit(1);
	}
	if (ft_strncmp(av[1], "here_doc", 8))
		cmd = ft_split(av[i + 2], ' ');
	else
		cmd = ft_split(av[i + 3], ' ');
	if (!cmd || !cmd[0] || !cmd[0][0])
	{
		free_path(cmd);
		free_path(path);
		free(pid);
		ft_putstr_fd("Command not found \n", 2);	
		exit(127);
	}
	cmd_path = get_cmd_path(cmd, path, pid);
	if (!cmd_path)
	{	
		free_path(cmd);
		free_path(path);
		free(pid);
		ft_putstr_fd("Command not found \n", 2);
		exit(127);
	}
	dup2(fd_out, 1);
	dup2(fd_in, 0);
	close(fd_in);
	close(fd_out);
	if (execve(cmd_path, cmd, envp) == -1)
		perror("\033[31mError");
	free_path(cmd);
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
	int last_pid;
	int wpid;
	int exit_code;
	
    if (ac >= 5)
    {
		i = 0;
		pid = malloc(sizeof(int) * (ac - 3));
		
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
		{
			if (ac < 6)
			{
				perror("\033[31mError");
				exit(1);
			}
			out = check_outfile(av[ac - 1], 1);
			pipe(fds);
			fd_in = fds[0];
			num_ac = ac - 4;
			num_cmd = ac - 4;
			pid[i] = fork();
			if (!pid[i])
			{
				here_doc(av[2], fds, pid);
				free(pid);
			}
			close(fds[1]);
			waitpid(pid[i], NULL, 0);
			i++;
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
				child(envp, av, i, path, fd_in, fds[1], pid);
				free(pid);
			}
			close(fd_in);
			close(fds[1]);
			fd_in = dup(fds[0]);
			close(fds[0]);
			i++;
				
		}
		pid[i] = fork();
		last_pid = pid[i];
		if (pid[i] == 0)
		{
			if (out == -1)
			{	
				free_path(path);
				free(pid);
				perror("\033[31mError");
				exit(1);
			}
			dup2(fd_in, 0);
			dup2(out, 1);
			close(fd_in);
			close(out);
			cmd = ft_split(av[ac - 2], ' ');
			if (!cmd || !cmd[0] || !cmd[0][0])
			{
				free_path(cmd);
				free_path(path);
				free(pid);
				ft_putstr_fd("Command not found \n", 2);
				exit(127);
			}
			cmd_path = get_cmd_path(cmd, path, pid);
			if (!cmd_path)
			{
				free_path(cmd);
				free_path(path);
				free(pid);
				ft_putstr_fd("Command not found \n", 2);
				exit(127);
			}
			if (execve(cmd_path, cmd, envp) == -1)
				perror("\033[31mError");
			free_path(path);
			free_path(cmd);
			free(cmd_path);
		}
		close(fd_in);
		close(out);
		free(pid);
		free_path(path);
		i = 0;
		while(i < num_ac)
		{
			wpid = wait(&status);
			if (wpid == last_pid)
				exit_code = status;
			i++;
		}
		if (exit_code >= 256)
			return (exit_code / 256);
		return (0);
    }
    return (0);
}
