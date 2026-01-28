/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 20:55:20 by rchaumei          #+#    #+#             */
/*   Updated: 2026/01/28 23:31:58 by rchaumei         ###   ########.fr       */
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

	while (env)
	{
		if (ft_strncmp(*env, "PATH", 4) == 0)
			break ;
		env++;
	}
	path = ft_split(*env + 5, ':');
	return (path);
}

int main(int ac, char **av, char **envp)
{
    int in;
    int out;
    char **env;
    if (ac >= 5)
    {
        in = check_infile(av[1]);
        out = check_outfile(av[ac - 1]);
        env = get_env(char **env);
    }
    return (0);
}