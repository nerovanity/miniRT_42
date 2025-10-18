/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessoufi <oessoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:33:30 by oessoufi          #+#    #+#             */
/*   Updated: 2025/10/14 14:12:53 by oessoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	obj_intersect(t_ray *camera_ray, t_objects *object, double *current)
{
	if (object->type == SPHERE)
		return (sphere(camera_ray, object, current));
	else if (object->type == PLANE)
		return (plane_inter(camera_ray, object, current));
	else if (object->type == CYLINDER)
		return (cylinder_intersect(camera_ray, object, current));
	return (0);
}

int	trace(t_data *data, t_ray *camera_ray, double *closest, int *object_index)
{
	int		intersect;
	double	current;
	int		i;

	intersect = 0;
	i = 0;
	while (i < data->num_objects)
	{
		if (obj_intersect(camera_ray, data->objects[i], &current)
			&& current < *closest)
		{
			*object_index = i;
			*closest = current;
			intersect = 1;
		}
		i++;
	}
	return (intersect);
}

t_vec	ray_direction(t_data *data, int x, int y)
{
	t_cord	pixel;
	t_vec	point_on_plane;

	pixel.x = 2 * (x + 0.5) / data->img.width - 1;
	pixel.y = 2 * (y + 0.5) / data->img.height - 1;
	pixel.x = pixel.x * (data->camera.vpw / 2);
	pixel.y = pixel.y * (data->camera.vph / 2);
	point_on_plane = vec_add(data->camera.cord, data->camera.forward);
	point_on_plane = vec_add(point_on_plane, vec_scalar(data->camera.right,
				pixel.x));
	point_on_plane = vec_add(point_on_plane, vec_scalar(data->camera.up,
				pixel.y));
	return (vec_norm(vec_sub(point_on_plane, data->camera.cord)));
}

t_ray	build_camera_ray(t_data *data, int x, int y)
{
	t_ray	ray;

	ray.orig = data->camera.cord;
	ray.dir = ray_direction(data, x, y);
	return (ray);
}

void	ray_tracing(t_data *data)
{
	t_ray	camera_ray;
	int		object_index;
	double	closest;
	int		x;
	int		y;

	y = 0;
	while (y < data->img.height)
	{
		x = 0;
		while (x < data->img.width)
		{
			camera_ray = build_camera_ray(data, x, y);
			object_index = -1;
			closest = INFINITY;
			if (trace(data, &camera_ray, &closest, &object_index))
				my_mlx_pixel_put(&data->img, x, y, get_rgb(light_object(data,
							&camera_ray, object_index, closest)));
			x++;
		}
		y++;
	}
}
