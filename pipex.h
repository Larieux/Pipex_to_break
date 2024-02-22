/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:14:59 by jlarieux          #+#    #+#             */
/*   Updated: 2024/02/22 17:10:46 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"

typedef struct s_data
{
	char			**args;
	char			**env;
	int				arg_c;
	int				first_cmd;
	int				eof_len;
	int				here_doc;
	struct s_list	*pid_lst;
}					t_data;

typedef struct p_list
{
	int				pid;
	struct s_list	*next;
}					t_pid_lst;

/**
 * @brief 
 * 
 * @param str 
 * @param role 
 * @return int 
 */
int		ft_open(char *str, int role);

/**
 * @brief 
 * 
 * @param tab 
 */
void	free_dtab(char **tab);

/**
 * @brief 
 * 
 * @param dtab 
 */
void	ft_exit_malloc(char **dtab);

/**
 * @brief 
 * 
 * @param tab 
 */
void	ft_exit_dfree_malloc(char **tab);

/**
 * @brief Construct a new ft lst pid object
 * 
 * @param data 
 * @param pid 
 */
void	ft_lst_pid(t_data *data, pid_t pid);

/**
 * @brief 
 * 
 * @param fd 
 * @param fd_pipe 
 * @param childno 
 */
void	ft_dup_and_close(int fd, int *fd_pipe, int prev_fd, int childno);

/**
 * @brief 
 * 
 * @param data 
 * @param dtab 
 */
void	ft_free_node(t_data *data, char **dtab);

/**
 * @brief 
 * 
 * @param dtab 
 * @param dtab2 
 * @param tab 
 */
void	ft_execve_error(t_data *data, char **dtab, char **dtab2, char *tab);

/**
 * @brief 
 * 
 * @param limiter 
 */
void	ft_heredoc(t_data *data);

/**
 * @brief 
 * 
 * @param argc 
 * @param data 
 * @return int 
 */
int		ft_errors(int argc, t_data *data);

/**
 * @brief 
 * 
 */
void	ft_fd_error(char *str);

/**
 * @brief 
 * 
 * @param data 
 * @return char** 
 */
char	**ft_find_paths(t_data *data);

/**
 * @brief 
 * 
 * @param data 
 * @param cmd 
 */
void	ft_find_cmd(t_data *data, char **cmd);

/**
 * @brief 
 * 
 * @param data 
 */
int		wait_each_pid(t_data *data);

/**
 * @brief 
 * 
 * @param data 
 * @param fd_pipe 
 */
void	ft_child(t_data *data, int *fd_pipe);

/**
 * @brief 
 * 
 * @param data 
 * @param fd_pipe 
 */
void	ft_inter_child(t_data *data, int *fd_pipe, int prev_fd);

/**
 * @brief 
 * 
 * @param data 
 * @param fd_pipe 
 */
void	ft_child2(t_data *data, int *fd_pipe, int prev_fd);

/**
 * @brief 
 * 
 * @param fd_pipe 
 * @param pid 
 */
void	ft_parent(int *fd_pipe, pid_t pid);

/**
 * @brief 
 * 
 * @param data 
 * @param fd_pipe 
 */
void	do_fork(t_data *data, int *fd_pipe, int prev_fd, int role);

/**
 * @brief 
 * 
 * @param fd_pipe 
 */
void	do_pipe(int *fd_pipe);

/**
 * @brief 
 * 
 * @param data 
 * @param argc 
 */
void	pipex(t_data *data, int argc);

#endif
