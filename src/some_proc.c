/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:03:59 by medric            #+#    #+#             */
/*   Updated: 2022/04/11 14:53:58 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ms_error(char *err)
{
	ft_putstr_fd("pipex:", 2);
	ft_putstr_fd(err, 2);
	exit(1);
}

void	close_pipe(t_pipex *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
}

void	start_proc(int ac, char *av[], char *envp[], t_pipex *pipex)
{
	pipex->in = open(av[1], O_RDONLY);
	if (pipex->in < 0)
		ms_error(ERR_OUT);
	pipex->out = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex->out < 0)
		ms_error(ERR_IN);
	if (pipe(pipex->tube) < 0)
		ms_error(ERR_PIPE);
	pipex->paths = find(envp);
	pipex->cmd_paths = ft_split(pipex->paths, ':');
}
