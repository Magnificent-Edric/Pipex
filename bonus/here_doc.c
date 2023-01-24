/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:22:13 by medric            #+#    #+#             */
/*   Updated: 2022/04/12 18:13:42 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include "../includes/gnl.h"

static void	find_cmd(char *envp[], char *buff, t_pipe *pipex, int doc)
{
	char	*s;
	int		i;
	int		m;
	char	*tmp;

	i = 0;
	tmp = buff;
	s = (char *)malloc(sizeof(char) * (pipex->l + 1));
	while (i < pipex->l)
		s[i++] = tmp[pipex->t++];
	s[i++] = '\0';
	i = 0;
	m = envp_l(envp);
	while (ft_strncmp(s, *envp, pipex->l))
	{
		envp++;
		i++;
		if (i == m)
			break ;
	}
	ft_strdel(&s);
	if (i != m)
		write(doc, *envp + pipex->l + 1, ft_strlen(*envp + pipex->l + 1));
}

static int	lenght(char *buff, int t)
{
	int	len;
	int	i;
	int	start;

	i = t;
	start = t;
	while (buff[i] != '\0' && buff[i] != '\n' && buff[i] != '\t'
		&& buff[i] != '\r' && buff[i] != ' ' && buff[i] != '\v')
		i++;
	len = i - start;
	return (len);
}

static char	*ft_path(char *envp[], char *buff, int doc, t_pipe *pipex)
{
	char	*str;

	pipex->t = 0;
	pipex->l = 0;
	while (buff[pipex->t])
	{
		if (buff[pipex->t] == '$')
		{
			pipex->t++;
			pipex->l = lenght(buff, pipex->t);
			find_cmd(envp, buff, pipex, doc);
		}
		write(doc, &buff[pipex->t], 1);
		pipex->t++;
	}
	return (buff);
}

void	cmd_here_doc(char *av, t_pipe *pipex, int doc, char *envp[])
{
	char	*buff;

	while (1)
	{
		write(1, ">", 1);
		buff = get_next_line(0);
		if (!ft_strncmp(av, buff, ft_strlen(buff) - 1))
			break ;
		buff = ft_path(envp, buff, doc, pipex);
		free(buff);
	}
	free(buff);
}

void	here_doc(char *av, t_pipe *pipex, char *envp[])
{
	int		doc;

	pipex->here = 1;
	doc = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (doc < 0)
		msg_error(ERR_HERE);
	cmd_here_doc(av, pipex, doc, envp);
	close(doc);
	pipex->in = open(".heredoc_tmp", O_RDONLY);
	if (pipex->in < 0)
	{
		unlink(".heredoc_tmp");
		msg_error(ERR_IN);
	}
}
