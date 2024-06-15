/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_debug_mode.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 03:14:10 by ggeorgie          #+#    #+#             */
/*   Updated: 2023/12/23 22:07:52 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	1. Check if inputs are valid:
		- 0 < fd < USHRT_MAX,
		- 0 <= BUFFER_SIZE < UINT_MAX,
		- 'read' is able to read from 'fd',
	- If any of these is not true:
		- if 'carry_over' static pointer exists:
			- 'free' 'carry_over',
			- carry_over = 0;
		- return (NULL).
	2. If 'carry_over' static pointer to string does not exist,
		initialize it with length of 1 ('\0');
	- If not successful: 'return' 'NULL'.
	3. Initialize 'buffer' pointer to str with length of BUFFER_SIZE + 1 ('\0');
	- If not successful: 'free' 'carry_over' and 'return' 'NULL'.
	4. Initialize buffer_counter with positive integer.
	5. While buffer_counter is positive:
		buffer_counter = read(fd, buffer, BUFFER_SIZE);
	5.1. If buffer_counter = -1: 'free' 'carry_over' and 'buffer',
		and return (NULL);
	5.2. Add '\0' to the end of 'buffer'.
	5.3. Join 'carry_over' and 'buffer' into 'temp'.
	- If not successful: 'free' 'carry_over' and 'buffer', and 'return' 'NULL'.
	5.4. 'free' 'carry_over'.
	5.5. 'carry_over' = 'temp'.
	5.6. If 'carry_over' contains '\n', make 'buffer_counter' = 0 to exit 5.
	6. 'free' 'buffer'.
	7. If 'carry_over' is NULL or carry_over[0] = '\0', 'return' 'NULL'.
	8. Discover '\n' on the 'i'-th position of 'carry_over'
		within the range 0 < i < ft_strlen(carry_over).
	9.1. If '\n' is not found in 'carry_over'
	- Initialize 'line' pointer to string with length of i + 1 ('\0');
		- If not successful, 'free' 'carry_over', 'return' 'NULL'.
	- Copy 'carry_over' to 'line'.
	- Set carry_over[0] to '\0'.
	9.2. If '\n' is found in 'carry_over':
	- Initialize 'line' pointer to string with length of i + 2 ('\n' + '\0');
		- If not successful, 'free' 'carry_over', 'return' 'NULL'.
	- Copy from 'carry_over' to 'line' everything up to and '\n' itself.
	- Copy 'carry_over' from '\n' onwards to (the beginning of) 'carry_over'.
	10. 'return' 'line'.
 *
 * Memory allocation for carry_over, buffer, temp, line.
 */

#include "get_next_line.h"

char	*fn_free(char *variable)
{
// printf("fn_free 1, variable: '%p'\n", variable);
	free(variable);
	variable = NULL;
// printf("fn_free 2, variable: '%s'\n", variable);
	return (variable);
}

char	*process_carry_over(char *carry_over)
{
	size_t		i;
	char		*line;

	if (carry_over == NULL || carry_over[0] == '\0')							// 7.
		return (NULL);
	i = 0;
	while (carry_over[i] && carry_over[i] != '\n')								// 8.
		i++;
	if (i == ft_strlen(carry_over))												// 9.1.
	{
		line = ft_calloc(i + 1, sizeof(char));
// printf("process_carry_over 1.1, carry_over: '%p', line: '%p'\n", carry_over, line);
		if (!line)
			return (carry_over = fn_free(carry_over), NULL);
// printf("process_carry_over 1.2, carry_over: '%s', line: '%s'\n", carry_over, line);
		ft_strlcpy(line, carry_over, i + 1);
//		free(carry_over);
//		carry_over = fn_free(carry_over);
		carry_over[0] = '\0';
	}
	else																		// 9.2.
	{
		line = ft_calloc(i + 2, sizeof(char));
// printf("process_carry_over 2.1, carry_over: '%s', line: '%s'\n", carry_over, line);
		if (!line)
			return (carry_over = fn_free(carry_over), NULL);
// printf("process_carry_over 2.2, carry_over: '%s', line: '%s'\n", carry_over, line);
		ft_strlcpy(line, carry_over, i + 2);
// printf("process_carry_over 3, carry_over: '%s', line: '%s'\n", carry_over, line);
		ft_strlcpy(carry_over, &carry_over[i + 1], ft_strlen(carry_over) - i);
// printf("process_carry_over 4, carry_over: '%s', line: '%s'\n", carry_over, line);
	}
	return (line);																// 10.
}

char	*read_buffer(int fd, char *carry_over)
{
	char	*buffer;
	ssize_t	buffer_counter;
	char	*temp;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));							// 3.
// printf("read_buffer 1.1, carry_over: '%s', buffer: '%s'\n", carry_over, buffer);
	if (!buffer)
		return (carry_over = fn_free(carry_over), NULL);
// printf("read_buffer 1.2, carry_over: '%s', buffer: '%s'\n", carry_over, buffer);
	buffer_counter = 1;															// 4.
	while (buffer_counter > 0)
	{
		buffer_counter = read(fd, buffer, BUFFER_SIZE);							// 5.
// printf("read_buffer 2.1, carry_over: '%s', buffer: '%s'\n", carry_over, buffer);
		if (buffer_counter == -1)												// 5.1.
			return (carry_over = fn_free(carry_over), free(buffer), NULL);
// printf("read_buffer 2.2, carry_over: '%s', buffer: '%s'\n", carry_over, buffer);
		buffer[buffer_counter] = '\0';											// 5.2.
		temp = ft_strjoin(carry_over, buffer);									// 5.3.
// printf("\nread_buffer 3.1, carry_over: '%p', buffer: '%p', temp: '%p'\n", carry_over, buffer, temp);
// printf("read_buffer 3.1, carry_over: '%s', buffer: '%s', temp: '%s'\n", carry_over, buffer, temp);
		if (temp == NULL)
			return (carry_over = fn_free(carry_over), free(buffer), NULL);
// printf("read_buffer 3.2, carry_over: '%s', buffer: '%s', temp: '%s'\n", carry_over, buffer, temp);
		carry_over = fn_free(carry_over);										// 5.4.
// printf("read_buffer 4.1, carry_over: '%s', buffer: '%s', temp: '%s'\n", carry_over, buffer, temp);
		carry_over = temp;														// 5.5.
		// carry_over = calloc(ft_strlen(temp) + 1, sizeof(char));
		// if (!carry_over)
		// 	return (carry_over = fn_free(carry_over), buffer = fn_free(buffer), temp = fn_free(temp), NULL);
		// ft_strlcpy(carry_over, temp, ft_strlen(temp) + 1);
// printf("read_buffer 4.2, carry_over: '%s', buffer: '%s', temp: '%s'\n", carry_over, buffer, temp);
		// free(temp);
		if (ft_strchr(carry_over, '\n'))										// 5.6.
			buffer_counter = 0;
	}
// printf("read_buffer 5.1, carry_over: '%s', buffer: '%s', temp: '%s'\n", carry_over, buffer, temp);
	buffer = fn_free(buffer);																// 6.
// printf("read_buffer 5.2, carry_over: '%s', buffer: '%s', temp: '%s'\n", carry_over, buffer, temp);
	return (carry_over);
}

char	*get_next_line(int fd)
{
	static char	*carry_over;
	char		*line;

	if (fd < 0 || fd > USHRT_MAX || read(fd, 0, 0) < 0
		|| BUFFER_SIZE <= 0 || BUFFER_SIZE > UINT_MAX)							// 1.
	{
		if (carry_over)
// printf("get_next_line 2.1, carry_over: '%s'\n", carry_over);
			carry_over = fn_free(carry_over);
// printf("get_next_line 2.2, carry_over: '%s'\n", carry_over);
		return (NULL);
	}
	if (!carry_over)															// 2.
	{
// printf("get_next_line 1.1, carry_over: '%s'\n", carry_over);
		carry_over = ft_calloc(1, sizeof(char));
// printf("get_next_line 1.2, carry_over: '%s'\n", carry_over);
		if (!carry_over)
			return (NULL);
// printf("get_next_line 1.3, carry_over: '%s'\n", carry_over);
	}
	carry_over = read_buffer(fd, carry_over);
// printf("get_next_line 3, carry_over: '%s'\n", carry_over);
	if (!carry_over)
		return (NULL);
	line = process_carry_over(carry_over);
// printf("get_next_line 4, carry_over: '%s', line: '%s'\n", carry_over, line);
	// if (carry_over[0] == '\0')
	if (carry_over && carry_over[0] == '\0')
	// {
	// 	free(carry_over);
	// 	carry_over = NULL;
	// }
		carry_over = fn_free(carry_over);
// printf("get_next_line 5, carry_over: '%p', line: '%p'\n", carry_over, line);
	return (line);
}

int	main(void) 
{
	int fd;

	fd = 0;

	write(1, get_next_line(fd), ft_strlen(get_next_line(fd)));

	return (0);
}
