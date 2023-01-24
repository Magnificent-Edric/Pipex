/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffrent_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:00:10 by medric            #+#    #+#             */
/*   Updated: 2022/04/12 16:16:23 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error_proc(t_pipex pipex)
{
	pa_free(&pipex);
	ch_free(&pipex);
	ms_error(ERR_PROCESS);
}

void	call_second_child(t_pipex pipex, char **av, char **envp)
{
	if (dup2(pipex.tube[0], 0) < 0)
		error_proc(pipex);
	close(pipex.tube[1]);
	if (dup2(pipex.out, 1) < 0)
		error_proc(pipex);
	pipex.cmd_arg = ft_split(av[3], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_arg[0]);
	if (!pipex.cmd)
	{
		ch_free(&pipex);
		ms_error(ERR_CMD);
		exit(1);
	}
	if (execve(pipex.cmd, pipex.cmd_arg, envp) == -1)
		error_proc(pipex);
}

void	call_first_child(t_pipex pipex, char **av, char **envp)
{
	if (dup2(pipex.tube[1], 1) < 0)
		error_proc(pipex);
	close(pipex.tube[0]);
	if (dup2(pipex.in, 0) < 0)
		error_proc(pipex);
	pipex.cmd_arg = ft_split(av[2], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_arg[0]);
	if (!pipex.cmd)
	{
		ch_free(&pipex);
		ms_error(ERR_CMD);
		exit(1);
	}
	if (execve(pipex.cmd, pipex.cmd_arg, envp) == -1)
		error_proc(pipex);
}
