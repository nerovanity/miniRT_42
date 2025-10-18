/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessoufi <oessoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:54:55 by oessoufi          #+#    #+#             */
/*   Updated: 2025/10/13 14:28:52 by oessoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	reset_static(char **str, int *i)
{
	free(*str);
	*i = 0;
	*str = NULL;
}

char	*make_line(char *str, int *i)
{
	char	*line;
	char	*str_n;
	int		to_allocate;
	int		j;

	j = 0;
	str_n = ft_strchr((str + *i), '\n');
	if (str_n)
		to_allocate = str_n - (str + *i) + 1;
	else
		to_allocate = ft_strlen(str + *i);
	line = malloc(to_allocate + 1);
	if (line == NULL)
		return (NULL);
	while (str[*i] != '\n' && str[*i] != '\0')
		line[j++] = str[(*i)++];
	if (str[(*i)] == '\n')
		line[j++] = str[(*i)++];
	line[j] = '\0';
	return (line);
}

void	read_line(char *buffer, char **str, int fd, int *i)
{
	char	*previous_str;
	int		bytes_read;

	bytes_read = read(fd, buffer, 10);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = 0;
		previous_str = *str;
		*str = ft_strjoin(previous_str, buffer);
		free(previous_str);
		if (*str == NULL)
			return ;
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read(fd, buffer, 10);
	}
	if (bytes_read == -1)
		reset_static(str, i);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*str;
	static int	i;
	char		*line;

	if (fd == -1)
		return (reset_static(&str, &i), NULL);
	buffer = malloc((size_t)10 + 1);
	if (buffer == NULL)
	{
		reset_static(&str, &i);
		return (NULL);
	}
	read_line(buffer, &str, fd, &i);
	free(buffer);
	if (!str || str[i] == '\0')
	{
		reset_static(&str, &i);
		return (NULL);
	}
	line = make_line(str, &i);
	if (str[i] == '\0' || line == NULL)
		reset_static(&str, &i);
	return (line);
}
