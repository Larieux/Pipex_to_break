/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:15:02 by jlarieux          #+#    #+#             */
/*   Updated: 2024/02/21 14:10:57 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		status;

	data.args = argv;
	if (ft_errors(argc, &data) == -1)
		return (0);
	data.env = envp;
	data.arg_c = argc - 1;
	data.pid_lst = ft_lstnew(-1);
	pipex(&data, argc);
	status = wait_each_pid(&data);
	unlink ("tmp_heredoc");
	ft_lstclear(&(data.pid_lst));
	return (status);
}
