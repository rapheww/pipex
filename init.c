/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:24:38 by rchaumei          #+#    #+#             */
/*   Updated: 2026/02/05 23:26:02 by rchaumei         ###   ########.fr       */
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
