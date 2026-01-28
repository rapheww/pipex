/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 23:33:47 by rchaumei          #+#    #+#             */
/*   Updated: 2026/01/28 22:38:51 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_file(char **av)
{
	if (access(av[1], F_OK) == -1)
		perror("\033[31mError");
	if (access(av[1], F_OK) == 0)
		if (access(av[1], R_OK) == -1)
			perror("\033[31mError");
	if (access(av[4], F_OK) == 0)
		if (access(av[4], W_OK) == -1)
			perror("\033[31mError");
	return (0);
}

char	**get_path(char **env)
{
	char	**path;

	while (env)
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

void	close_prog(char **tab, char **tmp, int in, int out)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
	free_cmd(tmp);
	close(in);
	close(out);
}

void	free_cmd(char **tmp)
{
	int	i;

	i = 0;
	if (tmp)
	{
		while (tmp[i])
		{
			free(tmp[i]);
			i++;
		}
		free(tmp);
	}
}
