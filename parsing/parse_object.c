/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessoufi <oessoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:53:29 by oessoufi          #+#    #+#             */
/*   Updated: 2025/10/13 14:28:52 by oessoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_objects	*allocate_object(t_data *data)
{
	t_objects	*object;

	object = malloc(sizeof(t_objects));
	if (object == NULL)
		return (NULL);
	object->diameter = 0;
	object->height = 0;
	object->next = data->parse_obj;
	data->parse_obj = object;
	return (object);
}

int	valid_diameter(char *str, double *diameter)
{
	int	error;

	error = 0;
	*diameter = ft_atof(str, &error);
	if (error == 1)
		return (0);
	return (1);
}

void	parse_cylinder(char *line, t_data *data)
{
	char	**elements;
	double	cords[3];

	if (allocate_object(data) == NULL)
		free_data_andexit(data, line, "Error\nMalloc error\n");
	data->parse_obj->type = CYLINDER;
	elements = ft_split(line, ' ');
	if (elements == NULL)
		free_data_andexit(data, line, "Error\nMalloc error\n");
	if (count_elements(elements) != 6 || !valid_cords(elements[1], cords,
			&data->parse_obj->cord) || !valid_ncords(elements[2], cords,
			&data->parse_obj->n_cord) || !valid_diameter(elements[3],
			&data->parse_obj->diameter) || !valid_diameter(elements[4],
			&data->parse_obj->height) || !valid_rgb(elements[5],
			&data->parse_obj->rgbs))
	{
		free_split(elements);
		free_data_andexit(data, line, "Error\nWrong params for cylinder\n");
	}
	data->num_objects++;
	free_split(elements);
}

void	parse_plane(char *line, t_data *data)
{
	char	**elements;
	double	cords[3];

	if (allocate_object(data) == NULL)
		free_data_andexit(data, line, "Error\nMalloc error\n");
	data->parse_obj->type = PLANE;
	elements = ft_split(line, ' ');
	if (elements == NULL)
		free_data_andexit(data, line, "Error\nMalloc error\n");
	if (count_elements(elements) != 4 || !valid_cords(elements[1], cords,
			&data->parse_obj->cord) || !valid_ncords(elements[2], cords,
			&data->parse_obj->n_cord) || !valid_rgb(elements[3],
			&data->parse_obj->rgbs))
	{
		free_split(elements);
		free_data_andexit(data, line, "Error\nWrong params for plane\n");
	}
	data->num_objects++;
	free_split(elements);
}

void	parse_sphere(char *line, t_data *data)
{
	char	**elements;
	double	cords[3];

	if (allocate_object(data) == NULL)
		free_data_andexit(data, line, "Error\nMalloc error\n");
	data->parse_obj->type = SPHERE;
	elements = ft_split(line, ' ');
	if (elements == NULL)
		free_data_andexit(data, line, "Error\nMalloc error\n");
	if (count_elements(elements) != 4 || !valid_cords(elements[1], cords,
			&data->parse_obj->cord) || !valid_diameter(elements[2],
			&data->parse_obj->diameter) || !valid_rgb(elements[3],
			&data->parse_obj->rgbs))
	{
		free_split(elements);
		free_data_andexit(data, line, "Error\nWrong params for sphere\n");
	}
	data->num_objects++;
	free_split(elements);
}
