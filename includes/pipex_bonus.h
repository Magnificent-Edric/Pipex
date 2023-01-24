/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:36:13 by medric            #+#    #+#             */
/*   Updated: 2022/04/12 16:42:16 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define  PIPEX_BONUS_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/wait.h>
# include <stdio.h>
# include "gnl.h"

# define ERR_OUT "Don't open oufile\n"
# define ERR_IN	"Don't open infile\n"
# define ERR_ARG "Invalid number of arguments\n"
# define ERR_PIPE "Failed pipe\n"
# define ERR_CMD "Command not found\n"
# define ERR_FORK "Fork error\n"
# define ERR_TUBE "Don't create tube fd\n"
# define ERR_HERE "Here_doc failed\n"
# define ERR_DIS "Error discriptor\n"
# define ERR_PROCESS "Process don't work\n"

typedef struct s_pipe
{
	pid_t	*pid;
	int		**tube;
	int		i;
	int		tab;
	int		here;
	int		out;
	int		t;
	int		l;
	int		in;
	char	*paths;
	char	**cmd_paths;
	char	*cmd;
	char	**cmd_args;
	char	*here_path;
	int		cmd_num;
	int		pipe_num;
	int		idx;
}			t_pipe;

void		pipex_dub(int curr, int next, t_pipe *pipex);
int			envp_l(char *envp[]);
static void	find_cmd(char *envp[], char *buff, t_pipe *pipex, int doc);
static char	*ft_path(char *envp[], char *buff, int doc, t_pipe *pipex);
static char	*ft_path_utils(char *envp[], char *buff, int t, t_pipe *pipex);
void		cmd_here_doc(char *av, t_pipe *pipex, int doc, char *envp[]);
void		start(t_pipe *pipex, int ac, char *av[], char *envp[]);
void		execve_child(t_pipe pipex, char *av, char *envp[]);
void		child(t_pipe pipex, char *av, char **envp);
void		create_pipes(t_pipe *pipex);
void		close_tube(t_pipe *pipex);
void		msg_error(char *err);
void		infile(int ac, char *av[], t_pipe *pipex, char *envp[]);
void		outfile(int ac, char *av[], t_pipe *pipex);
void		here_doc(char *av, t_pipe *pipex, char *envp[]);
char		*find(char **src);
char		*get_cmd(char **paths, char *cmd);
void		child_free(t_pipe *pipex);
void		parent_del(t_pipe *pipex);
int			valid_ac(char *av[], t_pipe *pipex);
char		**ft_split(char const *s, char c);
static int	check_s(char const *s, char c);
static void	free_all(char **words, size_t last_wrd_idx);
static char	*creator_str(char const *s, const char c);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
size_t		ft_strlen(char const *s);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
static int	lensize(int slen, int start, int len);
void		ft_strdel(char **as);
void		free_arr(char ***as);
int			ft_strncmp(const char *str1, const char *str2, size_t num);

#endif