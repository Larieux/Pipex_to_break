/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:25:38 by jlarieux          #+#    #+#             */
/*   Updated: 2024/02/23 09:11:18 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child(t_struct *data, int *fd_pipe)
{
	char	**cmd;
	int		fd;

	if (data->here_doc == 1)
		fd = ft_open(data->args[data->arg_c + 1], 0);
	else
		fd = ft_open(data->args[data->arg_c + 1], 1);
	if (fd == -1)
		ft_fd_error(data->args[data->arg_c + 1]);
	cmd = ft_split(data->args[data->arg_c], ' ');
	if (!cmd || cmd == NULL || cmd[0] == NULL)
		ft_exit_malloc(cmd);
	ft_dup_and_close(fd, fd_pipe, 0, 0);
	ft_find_cmd(data, cmd);
}

void	ft_inter_child(t_struct *data, int *fd_pipe, int prev_fd)
{
	char	**cmd;

	cmd = ft_split(data->args[data->arg_c], ' ');
	if (!cmd || cmd == NULL || cmd[0] == NULL)
		ft_exit_malloc(cmd);
	ft_dup_and_close(-1, fd_pipe, prev_fd, 1);
	ft_find_cmd(data, cmd);
}

void	ft_child2(t_struct *data, int *fd_pipe, int prev_fd)
{
	char	**cmd;
	int		fd;

	if (data->here_doc == 1)
		fd = open(data->args[2], O_RDONLY, 0644);
	else
		fd = open(data->args[1], O_RDONLY, 0644);
	if (fd == -1)
	{
		if (data->here_doc == 1)
			ft_fd_error(data->args[2]);
		else
			ft_fd_error(data->args[1]);
	}
	cmd = ft_split(data->args[data->first_cmd], ' ');
	if (!cmd || cmd == NULL || cmd[0] == NULL)
		ft_exit_malloc(cmd);
	ft_dup_and_close(fd, fd_pipe, prev_fd, 2);
	ft_find_cmd(data, cmd);
}
