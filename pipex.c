/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapheww <rapheww@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:45:39 by rchaumei          #+#    #+#             */
/*   Updated: 2026/01/27 02:30:00 by rapheww          ###   ########.fr       */
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
    int pid1;
    int pid2;
    int pipefds[2];
    int status;
    int exit_code;
    
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
        pipe(pipefds);
        pid1 = fork();
        if (pid1 == 0)
        {
            if (in == -1)
                exit(1);
            dup2(in, 0);
            dup2(pipefds[1], 1);
            close(in);
            close(pipefds[0]);
            close(pipefds[1]);
            if (!cmd1 || !cmd1[0] || !cmd1[0][0])
                exit(127);
            cmd1_path = get_cmd_path(cmd1[0], path);
            if (!cmd1_path)
                exit(127);
            execve(cmd1_path, cmd1, envp);
            exit(0);
        }
        pid2 = fork();
        if (pid2 == 0)
        { 
            if (out == -1)
                exit(1);
            dup2(pipefds[0], 0);
            dup2(out, 1);
            close(pipefds[0]);
            close(pipefds[1]);
            close(out);
            if (!cmd2 || !cmd2[0] || !cmd2[0][0])
                exit(127);
            cmd2_path = get_cmd_path(cmd2[0], path);
            if (!cmd2_path)
                exit(127);
            execve(cmd2_path, cmd2, envp);
            exit(0);
        }
        close(pipefds[0]);
        close(pipefds[1]);
        waitpid(pid1, NULL, 0);
        waitpid(pid2, &status, 0);
        if (status >= 256)
            exit_code = status / 256;
        else if (status == 0)
            exit_code = 0;
        else 
            exit_code = 128 + status;
        return(exit_code);
    }
    return (0);
}
