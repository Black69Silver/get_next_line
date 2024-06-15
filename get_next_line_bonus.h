/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:45:24 by ggeorgie          #+#    #+#             */
/*   Updated: 2024/01/02 22:10:42 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <limits.h>	/* to limit the values of various variable types */
# include <stdlib.h>	/* to use 'malloc', 'free' */
# include <sys/types.h> /* to use 'ssize_t' */
# include <unistd.h>	/* to use 'read' */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);
char	*get_next_line(int fd);

#endif
