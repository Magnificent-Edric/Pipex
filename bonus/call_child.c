/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:23:57 by medric            #+#    #+#             */
/*   Updated: 2022/04/12 18:14:00 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include "../includes/gnl.h"

void	pipex_dub(int curr, int next, t_pipe *pipex)
{
	if (dup2(curr, 0) < 0)
	{
		child_free(pipex);
		msg_error(ERR_DIS);
	}
	if (dup2(next, 1) < 0)
	{
		child_free(pipex);
		msg_error(ERR_DIS);
	}
}

void	error_process(t_pipe *pipex)
{
	parent_del(pipex);
	child_free(pipex);
	msg_error(ERR_PROCESS);
}

void	execve_child(t_pipe pipex, char *av, char **envp)
{
	if (pipex.i == 0 && pipex.i < pipex.cmd_num - 1)
		pipex_dub(pipex.in, pipex.tube[pipex.i + 1][1], &pipex);
	else if (pipex.i > 0 && pipex.i < pipex.cmd_num - 1)
		pipex_dub(pipex.tube[pipex.i][0], pipex.tube[pipex.i + 1][1], &pipex);
	else
		pipex_dub(pipex.tube[pipex.i][0], pipex.out, &pipex);
	close_tube(&pipex);
	pipex.cmd_args = ft_split(av, ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		parent_del(&pipex);
		msg_error(ERR_CMD);
		exit(1);
	}
	if (execve(pipex.cmd, pipex.cmd_args, envp) == -1)
		error_process(&pipex);
}

void	child(t_pipe pipex, char *av, char **envp)
{
	if (pipex.pid[pipex.i] == -1)
	{
		msg_error(ERR_FORK);
		child_free(&pipex);
	}
	if (pipex.pid[pipex.i] == 0)
		execve_child(pipex, av, envp);
}
