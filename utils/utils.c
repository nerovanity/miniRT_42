/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessoufi <oessoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:55:01 by oessoufi          #+#    #+#             */
/*   Updated: 2025/10/13 14:28:52 by oessoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s + 1);
		s++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*s2;

	i = ft_strlen(s1);
	s2 = malloc(sizeof(char) * (i + 1));
	if (s2 == NULL)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = 0;
	return (s2);
}

void	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (dstsize != 0)
	{
		while (i < (dstsize - 1) && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = 0;
	}
}

char	*ft_strtrim(char const *s1)
{
	size_t	start;
	size_t	end;
	char	*str;

	if (!s1)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	if (end == 0)
		return (ft_strdup(""));
	end--;
	while (s1[start] && s1[start] <= 32)
		start++;
	while (end > start && s1[end] <= 32)
		end--;
	str = malloc(sizeof(char) * end - start + 2);
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s1[start], end - start + 2);
	return (str);
}

void	free_data_andexit(t_data *data, char *line, char *msg)
{
	t_objects	*curr;
	t_objects	*next;

	close(data->fd);
	curr = data->parse_obj;
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	free(line);
	free(data->objects);
	get_next_line(-1);
	if (msg == NULL)
	{
		mlx_destroy_image(data->mlx.mlx, data->img.img);
		mlx_destroy_window(data->mlx.mlx, data->mlx.mlx_win);
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
		exit(0);
	}
	else
		error(msg);
}
