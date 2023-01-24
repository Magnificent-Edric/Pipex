/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 08:54:15 by medric            #+#    #+#             */
/*   Updated: 2022/04/08 18:58:50 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find(char **src)
{
	while (ft_strncmp("PATH", *src, 4))
		src++;
	return (*src + 5);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		ft_strdel(&tmp);
		if (access(command, 0) == 0)
			return (command);
		paths++;
		ft_strdel(&command);
	}
	return (NULL);
}

void	pa_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->in);
	close(pipex->out);
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
}

void	ch_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_arg[i])
	{
		free(pipex->cmd_arg[i]);
		i++;
	}
	free(pipex->cmd_arg);
	free(pipex->cmd);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
		ms_error(ERR_ARG);
	start_proc(ac, av, envp, &pipex);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		call_first_child(pipex, av, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		call_second_child(pipex, av, envp);
	close_pipe(&pipex);
	pa_free(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return (0);
}
