/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:23:31 by rchaumei          #+#    #+#             */
/*   Updated: 2026/02/05 23:23:56 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	create_heredoc(t_command *s, int *i, int ac)
{
	if (ac < 6)
	{
		free(s->pid);
		perror("\033[31mError");
		exit(1);
	}
	s->out = check_outfile(s->av[ac - 1], 1);
	pipe(s->fds);
	s->fd_in = s->fds[0];
	s->num_ac = ac - 4;
	s->num_cmd = ac - 4;
	s->pid[*i] = fork();
	if (!s->pid[*i])
	{
		if (s->out >= 0)
			close(s->out);
		here_doc(s->av[2], s);
		close(s->fd_in);
		close(s->fds[1]);
	}
	close(s->fds[1]);
	waitpid(s->pid[*i], NULL, 0);
	(*i)++;
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
