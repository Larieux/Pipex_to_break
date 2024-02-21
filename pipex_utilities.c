/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:24:38 by jlarieux          #+#    #+#             */
/*   Updated: 2024/01/30 14:53:45 by jlarieux         ###   ########.fr       */
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
