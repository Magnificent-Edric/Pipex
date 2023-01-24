/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:27:31 by medric            #+#    #+#             */
/*   Updated: 2022/04/12 18:13:51 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include "../includes/gnl.h"

void	msg_error(char *err)
{
	ft_putstr_fd("pipex:", 2);
	ft_putstr_fd(err, 2);
	exit(1);
}

void	parent_del(t_pipe *pipex)
{
	int	i;

	i = 0;
	close(pipex->in);
	close(pipex->out);
	if (pipex->here)
		unlink(".heredoc_tmp");
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
	i = 0;
	while (i < pipex->cmd_num)
	{
		free(pipex->tube[i]);
		i++;
	}
	free(pipex->tube);
	free(pipex->pid);
}
