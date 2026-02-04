/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 20:55:20 by rchaumei          #+#    #+#             */
/*   Updated: 2026/02/05 00:20:56 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_infile(char *file)
{
	if (access(file, F_OK) == -1)
		perror("\033[31mError");
	if (access(file, F_OK) == 0)
		if (access(file, R_OK) == -1)
			perror("\033[31mError");
	return (open(file, O_RDONLY));
}

int	check_outfile(char *file, int i)
{
	if (access(file, F_OK) == 0)
		if (access(file, W_OK) == -1)
			perror("\033[31mError");
	if (i == 1)
		return (open(file, O_WRONLY | O_APPEND | O_CREAT, 0777));
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

char	*get_cmd_path(char **cmd, char **path)
{
	char	*command;
	char	*tmp;
	int		i;

	i = 0;
	if (access(cmd[0], X_OK) == 0)
		return (cmd[0]);
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
	return (NULL);
}

void	here_doc(char *lim, t_command *s)
{
	char	*line;

	close(s->fds[0]);
	ft_putstr_fd("pipe heredoc >", 1);
	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, lim, ft_strlen(lim)) == 0
			&& line[ft_strlen(lim)] == '\n')
		{
			get_next_line(-1);
			close(s->fds[1]);
			free(line);
			free(s->pid);
			exit(0);
		}
		write(s->fds[1], line, ft_strlen(line));
		free(line);
		ft_putstr_fd("pipe heredoc >", 1);
		line = get_next_line(0);
	}
}

int	is_slash(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	child(char **envp, char **av, int i, char **path, int fd_in, int fd_out,
		int *pid, int *fds, int in, int out)
{
	char	**cmd;
	char	*cmd_path;

	if (fd_in < 0)
	{
		free_path(path);
		free(pid);
		close(fds[0]);
		if (fd_out >= 0)
			close(fd_out);
		perror("\033[31mError");
		exit(1);
	}
	if (ft_strncmp(av[1], "here_doc", 8))
		cmd = ft_split(av[i + 2], ' ');
	else
		cmd = ft_split(av[i + 3], ' ');
	if (!cmd || !cmd[0] || !cmd[0][0])
	{
		ft_putstr_fd("Command not found: ", 2);
		if (cmd && cmd[0])
			ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("\n", 2);
		free_path(cmd);
		free_path(path);
		free(pid);
		close(fd_in);
		close(fd_out);
		close(fds[0]);
		exit(0);
	}
	if (is_slash(cmd[0]) && access(cmd[0], F_OK) == -1)
	{
		perror("\033[31mError");
		free_path(cmd);
		free_path(path);
		free(pid);
		close(fds[0]);
		close(fds[1]);
		close(in);
		close(out);
		exit(0);
	}
	if (access(cmd[0], F_OK) == 0 && access(cmd[0], X_OK) == -1)
	{
		perror("\033[31mError");
		free_path(cmd);
		free_path(path);
		free(pid);
		close(fds[0]);
		close(fds[1]);
		close(in);
		close(out);
		exit(0);
	}
	if ((!path || !path[0] || !path[0][0]) && access(cmd[0], X_OK) == -1)
	{
		perror("\033[31mError");
		free_path(cmd);
		free_path(path);
		free(pid);
		close(fds[0]);
		close(fds[1]);
		close(in);
		close(out);
		exit(0);
	}
	cmd_path = get_cmd_path(cmd, path);
	if (!cmd_path)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("\n", 2);
		free_path(cmd);
		free_path(path);
		free(pid);
		close(fd_in);
		close(fd_out);
		close(fds[0]);
		exit(0);
	}
	dup2(fd_out, 1);
	dup2(fd_in, 0);
	close(fd_in);
	close(fd_out);
	if (execve(cmd_path, cmd, envp) == -1)
		perror("\033[31mError");
	free_path(cmd);
}

int	main(int ac, char **av, char **envp)
{
	t_command	s;
	int			i;

	if (ac >= 5)
	{
		i = 0;
		s.exit_code = 0;
		s.pid = malloc(sizeof(int) * (ac - 3));
		if (!s.pid)
			return (0);
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
		{
			if (ac < 6)
			{
				free(s.pid);
				perror("\033[31mError");
				exit(1);
			}
			s.out = check_outfile(av[ac - 1], 1);
			pipe(s.fds);
			s.fd_in = s.fds[0];
			s.num_ac = ac - 4;
			s.num_cmd = ac - 4;
			s.pid[i] = fork();
			if (!s.pid[i])
			{
				if (s.out >= 0)
					close(s.out);
				here_doc(av[2], &s);
				close(s.fd_in);
				close(s.fds[1]);
			}
			close(s.fds[1]);
			waitpid(s.pid[i], NULL, 0);
			i++;
		}
		else
		{
			s.out = check_outfile(av[ac - 1], 0);
			s.num_ac = ac - 3;
			s.num_cmd = ac - 4;
			s.in = check_infile(av[1]);
			s.fd_in = s.in;
		}
		s.path = get_env(envp);
		while (i < s.num_cmd)
		{
			pipe(s.fds);
			s.pid[i] = fork();
			if (!s.pid[i])
			{
				close(s.fds[0]);
				if (s.out >= 0)
					close(s.out);
				child(envp, av, i, s.path, s.fd_in, s.fds[1], s.pid, s.fds,
					s.in, s.out);
				close(s.fd_in);
				close(s.fds[1]);
				free(s.pid);
			}
			if (s.fd_in >= 0)
				close(s.fd_in);
			close(s.fds[1]);
			s.fd_in = s.fds[0];
			i++;
		}
		s.pid[i] = fork();
		s.last_pid = s.pid[i];
		if (s.pid[i] == 0)
		{
			if (s.out == -1)
			{
				free_path(s.path);
				free(s.pid);
				close(s.fds[0]);
				close(s.fds[1]);
				close(s.in);
				perror("\033[31mError");
				exit(1);
			}
			dup2(s.fd_in, 0);
			dup2(s.out, 1);
			close(s.fd_in);
			if (s.out >= 0)
				close(s.out);
			s.cmd = ft_split(av[ac - 2], ' ');
			if (!s.cmd || !s.cmd[0] || !s.cmd[0][0])
			{
				ft_putstr_fd("Command not found: ", 2);
				if (s.cmd && s.cmd[0])
					ft_putstr_fd(s.cmd[0], 2);
				ft_putstr_fd("\n", 2);
				free_path(s.cmd);
				free_path(s.path);
				free(s.pid);
				close(s.fds[0]);
				close(s.fds[1]);
				close(s.in);
				close(s.out);
				exit(127);
			}
			if (is_slash(s.cmd[0]) && access(s.cmd[0], F_OK) == -1)
			{
				perror("\033[31mError");
				free_path(s.cmd);
				free_path(s.path);
				free(s.pid);
				close(s.fds[0]);
				close(s.fds[1]);
				close(s.in);
				close(s.out);
				exit(127);
			}
			if (access(s.cmd[0], F_OK) == 0 && access(s.cmd[0], X_OK) == -1)
			{
				perror("\033[31mError");
				free_path(s.cmd);
				free_path(s.path);
				free(s.pid);
				close(s.fds[0]);
				close(s.fds[1]);
				close(s.in);
				close(s.out);
				exit(126);
			}
			if ((!s.path || !s.path[0] || !s.path[0][0]) && access(s.cmd[0],
					X_OK) == -1)
			{
				perror("\033[31mError");
				free_path(s.cmd);
				free_path(s.path);
				free(s.pid);
				close(s.fds[0]);
				close(s.fds[1]);
				close(s.in);
				close(s.out);
				exit(127);
			}
			s.cmd_path = get_cmd_path(s.cmd, s.path);
			if (!s.cmd_path)
			{
				ft_putstr_fd("Command not found: ", 2);
				ft_putstr_fd(s.cmd[0], 2);
				ft_putstr_fd("\n", 2);
				free_path(s.cmd);
				free_path(s.path);
				free(s.pid);
				close(s.fds[0]);
				close(s.fds[1]);
				close(s.in);
				close(s.out);
				exit(127);
			}
			if (execve(s.cmd_path, s.cmd, envp) == -1)
				perror("\033[31mError");
			free_path(s.path);
			free_path(s.cmd);
			free(s.cmd_path);
		}
		if (s.fd_in >= 0)
			close(s.fd_in);
		if (s.out >= 0)
			close(s.out);
		free(s.pid);
		free_path(s.path);
		i = 0;
		while (i < s.num_ac)
		{
			s.wpid = wait(&s.status);
			if (s.wpid == s.last_pid)
				s.exit_code = s.status;
			i++;
		}
		if (s.exit_code >= 256)
			return (s.exit_code / 256);
		return (0);
	}
	return (0);
}
