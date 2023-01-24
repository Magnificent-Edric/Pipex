/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 19:23:32 by medric            #+#    #+#             */
/*   Updated: 2022/04/10 20:56:28 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include "../includes/gnl.h"                                                    

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
		ft_strdel(&command);
		paths++;
	}
	return (NULL);
}

void	child_free(t_pipe *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_args[i])
	{
		free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
	free(pipex->cmd);
	free(pipex->pid);
}

int	valid_ac(char *av[], t_pipe *pipex)
{
	if (!ft_strncmp(av[1], "here_doc", 9))
	{
		pipex->here = 1;
		return (6);
	}
	else
	{
		pipex->here = 0;
		return (5);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	pipex;

	pipex.i = 0;
	if (ac < valid_ac(av, &pipex))
		msg_error(ERR_ARG);
	infile(ac, av, &pipex, envp);
	outfile(ac, av, &pipex);
	start(&pipex, ac, av, envp);
	create_pipes(&pipex);
	while (pipex.i < pipex.cmd_num)
	{
		pipex.pid[pipex.i] = fork();
		child(pipex, av[2 + pipex.i + pipex.here], envp);
		pipex.i++;
	}
	close_tube(&pipex);
	parent_del(&pipex);
	waitpid(-1, NULL, 0);
	return (0);
}
