/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 20:55:20 by rchaumei          #+#    #+#             */
/*   Updated: 2026/02/05 23:26:44 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pipex(t_command s, int i, int ac)
{
	s.path = get_env(s.envp);
	call_child(&s, &i);
	s.pid[i] = fork();
	s.last_pid = s.pid[i];
	if (s.pid[i] == 0)
		child2(ac, s.pid, s.fds, s);
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
		exit(s.exit_code / 256);
	exit(0);
}

int	main(int ac, char **av, char **envp)
{
	t_command	s;
	int			i;

	if (ac >= 5)
	{
		i = 0;
		s.av = av;
		s.envp = envp;
		s.exit_code = 0;
		s.pid = malloc(sizeof(int) * (ac - 3));
		if (!s.pid)
			return (0);
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
			create_heredoc(&s, &i, ac);
		else
		{
			s.out = check_outfile(av[ac - 1], 0);
			s.num_ac = ac - 3;
			s.num_cmd = ac - 4;
			s.in = check_infile(av[1]);
			s.fd_in = s.in;
		}
		pipex(s, i, ac);
	}
	return (0);
}
