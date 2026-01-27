/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:45:39 by rchaumei          #+#    #+#             */
/*   Updated: 2026/01/27 01:01:03 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "stdlib.h"

int check_file(char **av)
{
    if (access(av[1], F_OK) == -1)
        perror("\033[31mError");
    if (access(av[1], F_OK) == 1)
        if (access(av[1], R_OK) == -1)
            perror("\033[31mError");
    if (access(av[4], F_OK) == 1)
        if (access(av[4], W_OK) == -1)
            perror("\033[31mError");
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

char *get_cmd_path(char *cmd, char **path)
{
    char *command;
    int i;

    i = 0;
    if (access(cmd, X_OK) == 0)
        return (cmd);
    while(path[i])
    {
        command = ft_strjoin(path[i], "/");
        if (!command)
            return(NULL);
        command = ft_strjoin(command, cmd);
        if (!command)
            return(NULL);
        if (access(command, X_OK) == 0)
            return (command);
        i++;
    }
    return(ft_putstr_fd("Invalid command\n", 2), NULL);
}

int main(int ac, char **av, char **envp)
{
    int in;
    int out;
    char **path;
    char **cmd1;
    char *cmd1_path;
    char **cmd2;
    char *cmd2_path;
    int pid;
    int pipefds[2];
    int status;
    
    if (ac == 5)
    {
        if (check_file(av))
            return (0);
        in = open(av[1], O_RDONLY);
        out = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
        path = get_path(envp);
        if (!path)
            return (0);
        cmd1 = ft_split(av[2], ' ');
        if (!cmd1)
            return (0);
        cmd2 = ft_split(av[3], ' ');
        cmd1_path = get_cmd_path(cmd1[0], path);
        cmd2_path = get_cmd_path(cmd2[0], path);
        if (!cmd1_path)
            return (0);
        if (!cmd2_path)
            return (127);
        pipe(pipefds);
        pid = fork();
        if (pid == 0)
        {
            if (in == -1)
                exit(1);
            dup2(in, 0);
            dup2(pipefds[1], 1);
            close(in);
            close(pipefds[0]);
            if (!cmd1 || !cmd1[0] || !cmd1[0][0])
                exit(127);
            execve(cmd1_path, cmd1, envp);
        }
        if (out == -1)
            return (1);
        dup2(pipefds[0], 0);
        dup2(out, 1);
        close(pipefds[1]);
        close(out);
        if (!cmd2 || !cmd2[0] || !cmd2[0][0])
            return (127);
        execve(cmd2_path, cmd2, envp);
        waitpid(pid, &status, 0);
    }
    return (0);
}
