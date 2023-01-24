/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 11:47:38 by medric            #+#    #+#             */
/*   Updated: 2022/04/08 18:58:17 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../includes/pipex_bonus.h"

void	free_arr(char ***as)
{
	int	i;

	i = 0;
	if (!as)
		return ;
	while ((*as)[i])
	{
		free((*as)[i]);
		(*as)[i] = NULL;
		i++;
	}
	free(*as);
	*as = NULL;
}
