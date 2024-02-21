/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_children_managment.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:21:02 by jlarieux          #+#    #+#             */
/*   Updated: 2024/02/21 12:05:43 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_lst_pid(t_data *data, pid_t pid)
{
	t_list	*new_pid_lst;

	new_pid_lst = ft_lstnew(pid);
	if (new_pid_lst == NULL)
	{
		write(2, "list malloc error\n", 19);
		exit(EXIT_FAILURE);
	}
	ft_lstadd_back(&(data->pid_lst), new_pid_lst);
}

void	ft_dup_and_close(int fd, int *fd_pipe, int prev_fd, int childno)
{
	if (childno == 0)
	{
		dup2(fd_pipe[0], STDIN_FILENO);
		close(fd_pipe[0]);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		close(fd_pipe[1]);
	}
	else if (childno == 2)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		dup2(fd_pipe[1], STDOUT_FILENO);
		close(fd_pipe[1]);
		close(fd_pipe[0]);
	}
	else
	{
		dup2(fd_pipe[0], STDIN_FILENO);
		close(fd_pipe[0]);
		dup2(prev_fd, STDOUT_FILENO);
		close(prev_fd);
		close(fd_pipe[1]);
	}
}

void	ft_execve_error(t_data *data, char **dtab, char **dtab2, char *tab)
{
	int		errorlen;
	char	*build_error;
	char	*build_error2;
	char	*error;

	if (dtab[1])
	{
		build_error = ft_strjoin(dtab[0], " ");
		build_error2 = ft_strjoin(build_error, dtab[1]);
		error = ft_strjoin(build_error2, " not found\n");
		free(build_error);
		free(build_error2);
	}
	else
		error = ft_strjoin(dtab[0], " not found\n");
	errorlen = ft_strlen(error);
	write(2, error, errorlen);
	free(error);
	free_dtab(dtab);
	free(dtab2);
	free(tab);
	ft_lstclear(&(data->pid_lst));
	exit(EXIT_FAILURE);
}
