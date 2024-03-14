/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:25:13 by jlarieux          #+#    #+#             */
/*   Updated: 2024/03/14 14:18:50 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_r_w_heredoc(char **line, int *fd, int *line_len)
{
	if (*line != NULL)
		write(1, "> ", 2);
	write(*fd, *line, *line_len);
	free(*line);
	*line = get_next_line(0);
	if (*line != NULL)
		*line_len = ft_strlen(*line);
	else
		*line_len = 0;
}

void	ft_heredoc(t_struct *data)
{
	char	*line;
	int		fd;
	int		line_len;

	fd = open("tmp_heredoc", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_fd_error("tmp_heredoc");
	}
	write(1, "> ", 2);
	line = get_next_line(0);
	line_len = ft_strlen(line);
	while (line == NULL || ft_strncmp(line, data->args[2], line_len - 1) != 0
		|| ft_strncmp(line, data->args[2], data->eof_len) != 0)
		ft_r_w_heredoc(&line, &fd, &line_len);
	free(line);
	data->args[2] = "tmp_heredoc";
	close (fd);
}
