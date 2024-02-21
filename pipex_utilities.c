/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:24:38 by jlarieux          #+#    #+#             */
/*   Updated: 2024/02/21 13:55:31 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_dtab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] == NULL)
		i++;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_exit_malloc(char **dtab)
{
	write(2, "malloc error or cmd '' not found\n", 34);
	free(dtab);
	exit(EXIT_FAILURE);
}

void	ft_exit_dfree_malloc(char **tab)
{
	write(2, "malloc error or cmd '' not found\n", 34);
	free_dtab(tab);
	exit(EXIT_FAILURE);
}

void	ft_fd_error(char *str)
{
	char	*error;
	char	*error2;
	char	*error3;
	int		errlen;

	error = ft_strjoin(str, " : ");
	error2 = ft_strjoin(error, strerror(errno));
	error3 = ft_strjoin(error2, "\n");
	errlen = ft_strlen(error2);
	write(2, error3, errlen);
	free(error);
	free(error2);
	free(error3);
	exit(EXIT_FAILURE);
}