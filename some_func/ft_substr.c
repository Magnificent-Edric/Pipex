/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 17:01:40 by medric            #+#    #+#             */
/*   Updated: 2022/04/05 20:48:21 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../includes/pipex_bonus.h"

static int	lensize(int slen, int start, int len)
{
	size_t		size;

	size = 0;
	if (start > slen)
		size = 0;
	else if (start + len > slen)
		size = slen - start;
	else
		size = len;
	return (size);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			i;
	size_t			slen;
	size_t			size;

	i = 0;
	if (s == 0)
		return (NULL);
	slen = ft_strlen(s);
	size = lensize(slen, start, len);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (str == 0)
		return (NULL);
	while (i < size)
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}
