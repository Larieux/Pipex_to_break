/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:16:38 by jlarieux          #+#    #+#             */
/*   Updated: 2024/03/15 14:41:30 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_errors(int argc, t_struct *data, char **envp)
{
	if (argc < 5)
	{
		write(2, "please use './pipex infile cmd1 ... cmdn outfile'.\n", 52);
		return (-1);
	}
	if (ft_strlen(data->args[1]) == 8
		&& ft_strncmp(data->args[1], "here_doc", 8) == 0)
	{
		data->here_doc = 1;
		data->first_cmd = 3;
		data->eof_len = ft_strlen(data->args[2]);
		ft_heredoc(data);
	}
	else
	{
		data->here_doc = 0;
		data->first_cmd = 2;
	}
	if (envp[0] == NULL)
		data->env[0] = NULL;
	else
		data->env = envp;
	return (0);
}

char	**ft_find_paths(t_struct *data)
{
	char	*path;
	char	**paths;
	size_t	i;

	i = 0;
	path = NULL;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
			path = data->env[i];
		i++;
	}
	if (path == NULL)
		return (NULL);
	path = ft_substr(path, 5, strlen(path) - 5);
	if (path == NULL)
		return (write(2, "malloc error\n", 14), NULL);
	paths = ft_split(path, ':');
	if (paths == NULL)
		return (free (path), write(2, "malloc error\n", 14), NULL);
	return (free (path), paths);
}

void	ft_exec_van_cmd(t_struct *data, char **cmd)
{
	char	**van_cmd;
	char	*van_cmd_args[2];
	int		i;

	van_cmd = ft_split(cmd[0], '/');
	i = 0;
	while (van_cmd[i + 1] != NULL)
		i++;
	van_cmd_args[0] = ft_strjoin(van_cmd[i], " ");
	free_dtab (van_cmd);
	i = 1;
	while (cmd[i] != NULL)
	{
		van_cmd_args[1] = ft_strjoin(van_cmd_args[0], cmd[i]);
		free (van_cmd_args[0]);
		van_cmd_args[0] = ft_strjoin(van_cmd_args[1], " ");
		free (van_cmd_args[1]);
		i++;
	}
	van_cmd = ft_split(van_cmd_args[0], ' ');
	free (van_cmd_args[0]);
	execve(cmd[0], van_cmd, data->env);
	free_dtab (van_cmd);
}

void	ft_find_cmd(t_struct *data, char **cmd)
{
	int		i;
	int		test_exec;
	char	**paths;
	char	*slash_cmd;
	char	*path_cmd;

	paths = ft_find_paths(data);
	slash_cmd = ft_strjoin("/", cmd[0]);
	if (slash_cmd == NULL || !slash_cmd)
		ft_exit_dfree_malloc(paths);
	test_exec = -1;
	i = 0;
	while (test_exec == -1 && paths != NULL && paths[i] != NULL)
	{
		path_cmd = ft_strjoin(paths[i], slash_cmd);
		free(paths[i]);
		test_exec = execve(path_cmd, cmd, data->env);
		free(path_cmd);
		i++;
	}
	ft_exec_van_cmd(data, cmd);
	ft_execve_error(data, cmd, paths, slash_cmd);
}
