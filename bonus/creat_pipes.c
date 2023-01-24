/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:25:21 by medric            #+#    #+#             */
/*   Updated: 2022/04/12 18:13:55 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include "../includes/gnl.h"

void	create_pipes(t_pipe *pipex)
{
	int	i;

	i = 0;
	pipex->tube = (int **)malloc(sizeof(int *) * (pipex->cmd_num));
	if (!pipex->tube)
		msg_error(ERR_TUBE);
	while (i < pipex->cmd_num)
	{
		pipex->tube[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipex->tube[i])
			msg_error(ERR_TUBE);
		i++;
	}
	i = 0;
	while (i < pipex->cmd_num)
	{
		if (pipe(pipex->tube[i]) < 0)
			parent_del(pipex);
		i++;
	}
}

void	close_tube(t_pipe *pipex)
{
	int	i;

	i = 0;
	while (i < (pipex->cmd_num))
	{
		close(pipex->tube[i][0]);
		close(pipex->tube[i][1]);
		i++;
	}
}
