/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:44:19 by ggeorgie          #+#    #+#             */
/*   Updated: 2023/12/23 03:42:44 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	char	*string;
	size_t	i;

	i = 0;
	total_size = count * size;
	string = malloc(total_size);
	if (string)
	{
		while (i < total_size)
		{
			string[i] = '\0';
			i++;
		}
	}
	return (string);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (str)
	{
		i = 0;
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
		i = 0;
		while (s2[i])
		{
			str[ft_strlen(s1) + i] = s2[i];
			i++;
		}
		str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	}
	return (str);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len_src;
	size_t	i;

	len_src = ft_strlen(src);
	if (dstsize < 1)
		return (len_src);
	i = 0;
	while (src[i] && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len_src);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len_str;
	char	*output;

	i = 0;
	len_str = ft_strlen(s);
	if (!s)
		return (NULL);
	while (i < len_str && s[i] != (unsigned char) c)
		i++;
	if (s[i] == (unsigned char) c)
		output = (char *)&s[i];
	else
		output = NULL;
	return (output);
}
