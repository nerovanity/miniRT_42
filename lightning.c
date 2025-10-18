/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessoufi <oessoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:23:07 by oessoufi          #+#    #+#             */
/*   Updated: 2025/10/14 18:44:02 by oessoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	get_normal(t_objects *object, t_vec hit_point)
{
	float	t;
	t_vec	axis_point;
	t_vec	v;

	if (object->type == PLANE)
		return (object->n_cord);
	else if (object->type == SPHERE)
		return (vec_norm(vec_sub(hit_point, object->cord)));
	v = vec_sub(hit_point, object->cord);
	t = vec_dot(v, object->n_cord);
	if (t < -(object->height) / 2.0)
		return (vec_norm(vec_scalar(object->n_cord, -1)));
	else if (t > (object->height) / 2.0)
		return (object->n_cord);
	axis_point = vec_add(object->cord, vec_scalar(object->n_cord, t));
	return (vec_norm(vec_sub(hit_point, axis_point)));
}

t_vec	get_ambient_light(t_data *data)
{
	t_vec	ambient_color;

	ambient_color = vec_scalar(data->ambient_light.rgb,
			data->ambient_light.ratio);
	return (ambient_color);
}

bool	is_inshadow(t_data *data, t_objects *object, t_vec hit_point,
		t_vec to_light)
{
	t_ray	shadow;
	int		i;
	double	t;
	double	light_distance;

	light_distance = veclen(to_light);
	shadow.orig = hit_point;
	shadow.dir = vec_norm(to_light);
	i = 0;
	while (i < data->num_objects)
	{
		if (data->objects[i] != object)
		{
			t = INFINITY;
			if (obj_intersect(&shadow, data->objects[i], &t))
			{
				if (t > EPS && t < light_distance)
					return (true);
			}
		}
		i++;
	}
	return (false);
}

t_vec	get_diffuse_light(t_data *data, t_ray *camera_ray, t_objects *object,
		double closest)
{
	t_vec	hit_point;
	double	diffuse_factor;
	t_vec	light_dir;
	double	distance;
	double	attenuation;

	hit_point = vec_add(camera_ray->orig, vec_scalar(camera_ray->dir, closest));
	light_dir = vec_sub(data->light.cord, hit_point);
	diffuse_factor = vec_dot(get_normal(object, hit_point),
			vec_norm(light_dir));
	if (diffuse_factor < EPS)
		return ((t_vec){0.0, 0.0, 0.0});
	if (is_inshadow(data, object, hit_point, light_dir))
		return ((t_vec){0.0, 0.0, 0.0});
	distance = veclen(light_dir);
	attenuation = fmax(0.0, 1.0 - distance / 80.0);
	return (vec_scalar((t_vec){1.0, 1.0, 1.0}, data->light.brightness
		* diffuse_factor * attenuation));
}

t_vec	light_object(t_data *data, t_ray *camera_ray, int object_index,
		double closest)
{
	t_vec		color;
	t_vec		ambient_color;
	t_vec		diffuse_color;
	t_vec		total_light;
	t_objects	*object;

	object = data->objects[object_index];
	ambient_color = get_ambient_light(data);
	diffuse_color = get_diffuse_light(data, camera_ray, object, closest);
	total_light = vec_add(ambient_color, diffuse_color);
	total_light.x = fmin(1.0, total_light.x);
	total_light.y = fmin(1.0, total_light.y);
	total_light.z = fmin(1.0, total_light.z);
	color = vec_mul(object->rgbs, total_light);
	return (color);
}
