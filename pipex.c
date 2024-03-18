/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:15:02 by jlarieux          #+#    #+#             */
/*   Updated: 2024/03/18 16:16:19 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_struct	data;
	int			status;

	data.args = argv;
	if (ft_errors(argc, &data, envp) == -1)
		return (1);
	data.arg_c = argc - 2;
	data.pid_lst = ft_lstnew(-1);
	pipex(&data, argc);
	status = wait_each_pid(&data);
	unlink ("/tmp/tmp_heredoc");
	ft_lstclear(&(data.pid_lst));
	return (status);
}
