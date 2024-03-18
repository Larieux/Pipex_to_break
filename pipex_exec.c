/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:59:01 by jlarieux          #+#    #+#             */
/*   Updated: 2024/03/18 16:50:16 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	wait_each_pid(t_struct *data)
{
	t_list	*lst;
	int		status;

	lst = data->pid_lst;
	lst = lst->next;
	waitpid(lst->content, &status, 0);
	lst = lst->next;
	while (lst)
	{
		waitpid(lst->content, NULL, 0);
		lst = lst->next;
	}
	return (status);
}

void	do_fork(t_struct *data, int *fd_pipe, int prev_fd, int role)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (role == 0)
			ft_child(data, fd_pipe);
		else if (role == 2)
			ft_child2(data, fd_pipe, prev_fd);
		else
			ft_inter_child(data, fd_pipe, prev_fd);
	}
	else
	{
		if (role == 0 || role == 1)
			close(fd_pipe[0]);
		if (role == 1 || role == 2)
			close(prev_fd);
		ft_lst_pid(data, pid);
	}
}

void	do_pipe(int *fd_pipe)
{
	if (pipe(fd_pipe) == -1)
	{
		write(2, "pipe error\n", 12);
		exit(EXIT_FAILURE);
	}
}

void	pipex(t_struct *data, int argc)
{
	int	fd_pipe[2];
	int	prev_fd;

	while (data->arg_c >= data->first_cmd)
	{
		if (data->arg_c == data->first_cmd)
			do_fork(data, fd_pipe, prev_fd, 2);
		else if (data->arg_c == argc - 2)
		{
			do_pipe(fd_pipe);
			do_fork(data, fd_pipe, -1, 0);
			prev_fd = fd_pipe[1];
		}
		else
		{
			do_pipe(fd_pipe);
			do_fork(data, fd_pipe, prev_fd, 1);
			prev_fd = fd_pipe[1];
		}
		data->arg_c--;
	}
}
