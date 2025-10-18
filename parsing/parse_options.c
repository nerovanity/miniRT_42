/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessoufi <oessoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:54:17 by oessoufi          #+#    #+#             */
/*   Updated: 2025/10/15 14:27:07 by oessoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	insert_rgb(t_vec *rgb, unsigned char *color, char **elements)
{
	free_split(elements);
	rgb->x = color[0] / 255.0f;
	rgb->y = color[1] / 255.0f;
	rgb->z = color[2] / 255.0f;
}

int	valid_rgb(char *str, t_vec *rgb)
{
	char			**elements;
	int				i;
	int				error;
	unsigned char	color[3];

	if (!correct_commas(str))
		return (0);
	elements = ft_split(str, ',');
	if (elements == NULL)
		return (0);
	i = 0;
	while (elements[i])
		i++;
	if (i != 3)
		return (free_split(elements), 0);
	i = 0;
	error = 0;
	while (elements[i])
	{
		color[i] = ft_atoi(elements[i], &error);
		if (error == 1)
			return (free_split(elements), 0);
		i++;
	}
	return (insert_rgb(rgb, color, elements), 1);
}

int	correct_commas(char *str)
{
	char	*tmp;
	int		i;

	if (str == NULL)
		return (0);
	i = 0;
	tmp = ft_strchr(str, ',');
	while (tmp)
	{
		i++;
		if (i > 2)
			break ;
		tmp = ft_strchr(tmp, ',');
	}
	if (i != 2)
		return (0);
	return (1);
}

int	valid_ncords(char *str, double *cords, t_vec *vec)
{
	char	**elements;
	int		i;
	int		error;

	if (!correct_commas(str))
		return (0);
	elements = ft_split(str, ',');
	if (elements == NULL)
		return (0);
	if (count_elements(elements) != 3)
		return (free_split(elements), 0);
	i = 0;
	error = 0;
	while (elements[i])
	{
		cords[i] = ft_atof(elements[i], &error);
		if (error == 1 || cords[i] < -1.0 || cords[i] > 1.0)
			return (free_split(elements), 0);
		i++;
	}
	*vec = new_vec(cords[0], cords[1], cords[2]);
	if (veclen(*vec) == 0 || !vec_equal(*vec, vec_norm(*vec)))
		return (free_split(elements), 0);
	return (free_split(elements), 1);
}

int	valid_cords(char *str, double *cords, t_vec *vec)
{
	char	**elements;
	int		error;
	int		i;

	if (!correct_commas(str))
		return (0);
	elements = ft_split(str, ',');
	if (elements == NULL)
		return (0);
	if (count_elements(elements) != 3)
		return (free_split(elements), 0);
	i = 0;
	error = 0;
	while (elements[i])
	{
		cords[i] = ft_atof(elements[i], &error);
		if (error == 1)
			return (free_split(elements), 0);
		i++;
	}
	*vec = new_vec(cords[0], cords[1], cords[2]);
	free_split(elements);
	return (1);
}
