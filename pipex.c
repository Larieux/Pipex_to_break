/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:15:02 by jlarieux          #+#    #+#             */
/*   Updated: 2024/02/27 14:29:27 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_struct	data;
	char		**test;
	int			status;

	data.args = argv;
	if (ft_errors(argc, &data, envp) == -1)
		return (0);
	data.env = envp;
	test = ft_find_paths(&data);
	if (test == NULL)
		return (0);
	free_dtab (test);
	data.arg_c = argc - 2;
	data.pid_lst = ft_lstnew(-1);
	pipex(&data, argc);
	status = wait_each_pid(&data);
	unlink ("tmp_heredoc");
	ft_lstclear(&(data.pid_lst));
	return (status);
}
