/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:54:35 by medric            #+#    #+#             */
/*   Updated: 2022/04/05 20:47:06 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../includes/pipex_bonus.h"

static char	*creator_str(char const *s, const char c)
{
	size_t			start;
	size_t			end;
	char			*str;

	start = 0;
	end = 0;
	while (s[end] != '\0' && s[end] != c)
		end++;
	str = ft_substr(s, start, end);
	return (str);
}

static void	free_all(char **words, size_t last_wrd_idx)
{
	size_t	i;

	i = 0;
	while (i < last_wrd_idx)
		free(words[i++]);
	free(words);
}

static int	check_s(char const *s, char c)
{
	size_t		kol_s;
	size_t		i;

	i = 0;
	kol_s = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			kol_s++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (kol_s);
}

char	**ft_split(char const *s, char c)
{
	size_t			kol_s;
	char			**str;
	size_t			i;

	i = 0;
	if (s == 0)
		return (NULL);
	kol_s = check_s((char *)s, c);
	str = (char **)malloc(sizeof(char *) * (kol_s + 1));
	if (str == 0)
		return (NULL);
	while (i < kol_s)
	{
		while (*s && *s == c)
			s++;
		str[i] = creator_str(s, c);
		if (!str[i])
		{
			free_all(str, i);
			return (NULL);
		}
		s += ft_strlen(str[i++]);
	}
	str[kol_s] = NULL;
	return (str);
}
