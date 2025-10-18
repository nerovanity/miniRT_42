/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:53:09 by oessoufi          #+#    #+#             */
/*   Updated: 2025/10/14 09:44:47 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	valid_fieldview(char *str, int *field_view)
{
	int	error;

	error = 0;
	*field_view = ft_atoi(str, &error);
	if (*field_view > 180 || error == 1)
		return (0);
	return (1);
}

void	parse_camera(char *line, t_data *data)
{
	char	**elements;
	double	cords[3];

	if (data->flags[CAMERA])
		free_data_andexit(data, line,
			"Error\nCamera provided more than one time\n");
	elements = ft_split(line, ' ');
	if (elements == NULL)
		free_data_andexit(data, line, "Error\nMalloc error\n");
	if (count_elements(elements) != 4 || !valid_cords(elements[1], cords,
			&data->camera.cord) || !valid_ncords(elements[2], cords,
			&data->camera.dir) || !valid_fieldview(elements[3],
			&data->camera.fov))
	{
		free_split(elements);
		free_data_andexit(data, line, "Error\nWrong params for camera\n");
	}
	return (data->flags[CAMERA] = 1, free_split(elements));
}
