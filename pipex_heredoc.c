/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:25:13 by jlarieux          #+#    #+#             */
/*   Updated: 2024/02/17 14:08:59 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_heredoc(t_data *data)
{
	char	*line;
	int		fd;
	int		errlen;
	int		line_len;

	fd = open("tmp_heredoc", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		errlen = ft_strlen(strerror(errno));
		write(2, strerror(errno), errlen);
		exit(EXIT_FAILURE);
	}
	line = get_next_line(1);
	line_len = ft_strlen(line);
	while (ft_strncmp(line, data->args[2], line_len - 1) != 0
		|| ft_strncmp(line, data->args[2], data->eof_len) != 0)
	{
		write(fd, line, line_len);
		free(line);
		line = get_next_line(1);
		line_len = ft_strlen(line);
	}
	free(line);
	data->args[2] = "tmp_heredoc";
}
