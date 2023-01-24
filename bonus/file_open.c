/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:23:10 by medric            #+#    #+#             */
/*   Updated: 2022/04/12 18:13:39 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include "../includes/gnl.h"

void	infile(int ac, char *av[], t_pipe *pipex, char **envp)
{
	if (!ft_strncmp(av[1], "here_doc", 9))
		here_doc(av[2], pipex, envp);
	else
	{
		pipex->in = open(av[1], O_RDONLY);
		if (pipex->in < 0)
		{
			msg_error(ERR_IN);
		}
	}
}

void	outfile(int ac, char *av[], t_pipe *pipex)
{
	if (pipex->here == 1)
		pipex->out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		pipex->out = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0666);
	if (pipex->out < 0)
	{
		parent_del(pipex);
		msg_error(ERR_OUT);
	}
}

void	start(t_pipe *pipex, int ac, char *av[], char *envp[])
{
	pipex->cmd_num = ac - 3 - pipex->here;
	pipex->pid = malloc(sizeof(pid_t) * pipex->cmd_num);
	pipex->paths = find(envp);
	pipex->cmd_paths = ft_split(pipex->paths, ':');
}

int	envp_l(char *envp[])
{
	char	**s;
	int		i;

	i = 0;
	s = envp;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}
