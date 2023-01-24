/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:53:25 by medric            #+#    #+#             */
/*   Updated: 2022/04/08 18:53:25 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include <limits.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef FOPEN_MAX
#  define FOPEN_MAX 1024
# endif

typedef struct s_list
{
	char			buffer[BUFFER_SIZE];
	size_t			lenght;
	struct s_list	*next;
}					t_list;

typedef struct s_result
{
	char	*r;
	size_t	size_buff;
}			t_result;

typedef struct s_buffer
{
	char				buffer[BUFFER_SIZE];
	size_t				next_chr;
	ssize_t				read_chr;
	struct s_buffer		*next;
}						t_buffer;

t_list	*ft_lstnew(void);
void	ft_lstdelone(t_list *list_el);
t_list	*ft_lstadd_back(t_list *new);
void	ft_lstclear(t_list **lst);
char	*get_next_line(int fd);
t_list	*line_list(t_buffer *buff, t_list *list, t_result *res, int fd);
char	*creat_str(t_list *list, t_result *res);
int		check(t_buffer *buff, t_list *list, t_result *res);

#endif
