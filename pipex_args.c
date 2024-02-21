/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:16:38 by jlarieux          #+#    #+#             */
/*   Updated: 2024/02/21 11:44:04 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_errors(int argc, t_data *data)
{
	int		here_len;

	if (argc < 5)
	{
		write(2, "please use './pipex infile cmd1 ... cmdn outfile'.\n", 52);
		return (-1);
	}
	here_len = ft_strlen(data->args[1]);
	if (here_len == 8 && ft_strncmp(data->args[1], "here_doc", 8) == 0)
	{
		data->first_cmd = 3;
		data->eof_len = ft_strlen(data->args[2]);
		ft_heredoc(data);
	}
	else
		data->first_cmd = 2;
	return (0);
}

char	**ft_find_paths(t_data *data)
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	path = NULL;
	while (path == NULL)
	{
		path = ft_strnstr(data->env[i], "PATH", 4);
		i++;
	}
	path = ft_substr(path, 5, strlen(path) - 5);
	if (path == NULL)
		return (write(2, "malloc error\n", 14), NULL);
	paths = ft_split(path, ':');
	if (paths == NULL)
		return (free (path), write(2, "malloc error\n", 14), NULL);
	return (free (path), paths);
}

void	ft_find_cmd(t_data *data, char **cmd)
{
	int		i;
	int		test_exec;
	char	**paths;
	char	*slash_cmd;
	char	*path_cmd;

	paths = ft_find_paths(data);
	if (paths == NULL)
		exit(EXIT_FAILURE);
	slash_cmd = ft_strjoin("/", cmd[0]);
	if (slash_cmd == NULL || !slash_cmd)
		ft_exit_dfree_malloc(paths);
	test_exec = -1;
	i = 0;
	while (test_exec == -1 && paths[i] != NULL)
	{
		path_cmd = ft_strjoin(paths[i], slash_cmd);
		free(paths[i]);
		test_exec = execve(path_cmd, cmd, NULL);
		free(path_cmd);
		i++;
	}
	ft_execve_error(data, cmd, paths, slash_cmd);
}
