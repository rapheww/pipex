/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 20:54:15 by rchaumei          #+#    #+#             */
/*   Updated: 2026/02/05 23:26:00 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_command
{
	int		in;
	int		out;
	char	**path;
	char	**envp;
	char	**av;
	int		status;
	int		*pid;
	char	**cmd;
	int		fds[2];
	int		fd_in;
	int		num_ac;
	int		num_cmd;
	char	*cmd_path;
	int		last_pid;
	int		wpid;
	int		exit_code;
	int		fd_out;
}			t_command;

// INIT

int			check_outfile(char *file, int i);
int			check_infile(char *file);
char		**get_env(char **env);
char		*get_cmd_path(char **cmd, char **path);
int			is_slash(char *s);

// CLOSE

void		free_path(char **path);
void		close_perror(int *fds, int *pid, t_command s, char **cmd);
void		close_perror2(int *fds, int *pid, t_command s, char **cmd);
void		close_invalid(int *fds, int *pid, t_command s);
void		close_putstr(int *fds, int *pid, t_command s, char **cmd);

// CHILD

void		child(int i, int *pid, int *fds, t_command s);
void		child2(int ac, int *pid, int *fds, t_command s);
void		call_child(t_command *s, int *i);

// HEREDOC

void		here_doc(char *lim, t_command *s);
void		create_heredoc(t_command *s, int *i, int ac);

#endif