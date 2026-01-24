/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:45:39 by rchaumei          #+#    #+#             */
/*   Updated: 2026/01/24 19:11:56 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "stdlib.h"

int check_file(char **av)
{
    if (access(av[1], F_OK) == -1)
        return (ft_putstr_fd("invalid infile\n", 2), 1);
    if (access(av[4], F_OK) == -1)
        return (ft_putstr_fd("invalid outfile\n", 2), 1);
    if (access(av[1], R_OK) == -1)
        return (ft_putstr_fd("infile read permission denied\n", 2), 1);
    if (access(av[4], W_OK) == -1)
        return (ft_putstr_fd("outfile write permission denied\n", 2), 1);
    return (0);
}
#include <stdio.h>

char **get_path(char **env)
{
    char **path;
    
    while (env)
    {
        if (ft_strncmp(*env, "PATH", 4) == 0)
            break;
        env++;
    }
    path = ft_split(*env + 5, ':');
    return (path);
}



int main(int ac, char **av, char **envp)
{
    int in;
    int out;
    char *argv[] = {NULL};
    char **path;
    int i;
    char *cmd;
    char *tmp;
    
    if (ac == 5)
    {
        if (check_file(av))
            return (0);
        in = open(av[1], O_RDONLY);
        out = open(av[4], O_WRONLY);
        dup2(in, 0);
        dup2(out, 1);
        close(in);
        close(out);
        path = get_path(envp);
        if (!path)
            return (0);
        i = 0;
        if (execve(cmd , argv, envp) == 0)
            return (0);
        while (path[i])
        {
            tmp = ft_strjoin(path[i], "/");
            cmd = ft_strjoin(tmp, av[2]);
            if (execve(cmd , argv, envp) == 0)
                return (0);
            i++;
        }
        
    }
    return (0);
}