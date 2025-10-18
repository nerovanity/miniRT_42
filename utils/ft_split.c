/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessoufi <oessoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:54:51 by oessoufi          #+#    #+#             */
/*   Updated: 2025/10/13 14:28:52 by oessoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static int	is_seperator(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

static size_t	word_count(char const *s, char sep)
{
	size_t	i;
	size_t	wc;

	i = 0;
	wc = 0;
	while (s[i])
	{
		while (s[i] && is_seperator(s[i], sep))
			i++;
		if (s[i] && !is_seperator(s[i], sep))
		{
			wc++;
			while (!is_seperator(s[i], sep) && s[i])
				i++;
		}
	}
	return (wc);
}

static char	*ft_allocate(char const *s, char sep)
{
	size_t	i;
	char	*ptr;
	size_t	len;

	len = 0;
	while (s[len] && !is_seperator(s[len], sep))
		len++;
	ptr = (char *)malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

static void	*ft_free(char **strs, size_t count)
{
	size_t	i;

	if (strs == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char sep)
{
	char	**arr;
	size_t	i;

	if (s == NULL)
		return (NULL);
	arr = malloc(sizeof(char *) * (word_count(s, sep) + 1));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && is_seperator(*s, sep))
			s++;
		if (*s && !is_seperator(*s, sep))
		{
			arr[i] = ft_allocate(s, sep);
			if (arr[i] == NULL)
				return (ft_free(arr, i));
			i++;
			while (*s && !is_seperator(*s, sep))
				s++;
		}
	}
	arr[i] = NULL;
	return (arr);
}
