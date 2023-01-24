/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 08:48:45 by medric            #+#    #+#             */
/*   Updated: 2022/04/08 19:15:55 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define  PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

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

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		tube[2];
	int		out;
	int		in;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_arg;
	char	*cmd;
}			t_pipex;

void		close_pipe(t_pipex *pipex);
void		ms_error(char *err);
void		pa_free(t_pipex *pipex);
void		error_proc(t_pipex pipex);
void		start_proc(int ac, char *av[], char *envp[], t_pipex *pipex);
void		ch_free(t_pipex *pipex);
char		*get_cmd(char **paths, char *cmd);
char		*search_path(char **paths, char *cmd);
int			ft_access(char *new_path);
char		*find(char **src);
char		*get_path(char **envp, char **cmd);
static int	open_file(char *fname, char **envp, int flg, int mode);
void		call_second_child(t_pipex pipex, char **av, char **envp);
void		call_first_child(t_pipex pipex, char **av, char **envp);
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